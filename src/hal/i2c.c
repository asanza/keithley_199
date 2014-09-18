/**@file i2c.c
 * i2c driver */
#include <hal.h>
#include <HardwareProfile.h>
#include <assert.h>
#include <peripheral/i2c.h>

/** Sends an I2C start condition.
 * @param restart True if is a restart condition. false if it an start condition.
 * @return false if bus collision happens.
 */
static bool start_transfer( bool restart );
/** Try to transmit a byte through I2C and blocks until transmission has completed.
 *  @param data Data to transmit.
 *  @return true if transmission if Ok. False if a bus collision ocurred.
 */
static bool send_byte( uint8_t data );
/** Sends an I2C Stop condition.
 */
static void stop_transfer( void );


void hal_i2c_init(){
    /* HardwareProfile.h defines to which i2c port is the eeprom attached. */
    I2CConfigure(HAL_I2C_BUS,HAL_I2C_CONFIG);
    /* Set the i2c scl frequency */
    uint32_t actualClock = I2CSetFrequency(HAL_I2C_BUS, SYS_CLK, HAL_I2C_FREQ);
    if ( abs(actualClock-HAL_I2C_FREQ) > HAL_I2C_FREQ/10 ){
        /* if the requested clock is not possible. */
        assert(0);
    }
    /* Enable the I2C bus */
    I2CEnable(HAL_I2C_BUS, TRUE);
}

bool hal_i2c_write_byte_array(uint8_t device_address, uint8_t* data, uint8_t size){
    I2C_7_BIT_ADDRESS eeprom_address;
    I2C_FORMAT_7_BIT_ADDRESS(eeprom_address,device_address,I2C_WRITE);
    static uint8_t i2c_data[3];
    /* i2c data size */
    int dsize = data[0], i = 0;
    i2c_data[0] = eeprom_address.byte;
    i2c_data[2] = data[2];
    i2c_data[1] = data[1];
    /*wait while bus is bussy*/
    if(!start_transfer(false))
        return false; // bus collision.
    for(i = 0; i < dsize; i++){
        if(!send_byte(i2c_data[i]))
            return false; // bus collision.
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS))
            return false; // no acknoweledge
    }
    i = 0;
    while(size--){
        if(!send_byte(data[i++]))
            return false;
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS))
            return false;
    }
    stop_transfer();
    /*wait while writting eeprom*/
    bool ack = false;
    do{
        if(!start_transfer(false))
            return false; // bus collision
        if(!send_byte(eeprom_address.byte))
            return false; // bus collision
        ack = I2CByteWasAcknowledged(HAL_I2C_BUS);
        stop_transfer();
        //TODO: Potential for blocking state
    }while(!ack); /// block until ack. (while eeprom busy writting data.).
    return true;
}

#define MAX_TRIALS 5000

bool hal_eeprom_read_page(uint16_t page_address, void* _data, size_t size){
    assert(page_address < HAL_EEPROM_SIZE/HAL_EEPROM_PAGE_SIZE);
    assert(size <= HAL_EEPROM_PAGE_SIZE);
    assert(_data!=NULL);
    uint8_t* data = _data;
    uint8_t i2c_data[3];
    I2C_7_BIT_ADDRESS eeprom_address;
    int Index=0, dsize = 3;
    bool success = true;
    I2C_FORMAT_7_BIT_ADDRESS(eeprom_address, HAL_EEPROM_ADDRESS, I2C_WRITE);
    uint16_t address = page_address*HAL_EEPROM_PAGE_SIZE;
    i2c_data[0] = eeprom_address.byte;
    i2c_data[2] = address & 0x00FF;
    i2c_data[1] = (address>>8) & 0x00FF;
    /*wait while bus is bussy*/
    if(!start_transfer(false))
        return false; // bus collision
    while( success & (Index < dsize) ){
        // Transmit a byte
        if (send_byte(i2c_data[Index])){
            // Advance to the next byte
            Index++;
        }else{
            success = false;
        }
        // Verify that the byte was acknowledged
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS)){
            return false; // No ack.
        }
    }
    // Restart and send the EEPROM's internal address to switch to a read transfer
    // Send a Repeated Started condition
    if( !start_transfer(true) ){
        return false; // bus collision
    }
    // Transmit the address with the READ bit set
    I2C_FORMAT_7_BIT_ADDRESS(eeprom_address, HAL_EEPROM_ADDRESS, I2C_READ);
    if (send_byte(eeprom_address.byte)){
        // Verify that the byte was acknowledged
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS)){
            return false; // no ack
        }
    }else{
        return false; // bus collision
    }
    Index = 0;
    while(Index < HAL_EEPROM_PAGE_SIZE){
        if(I2CReceiverEnable(HAL_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW)
            return false; // overflow
        /* wait until eeprom sends some data */
        int retry_counter = 0;
        while(!I2CReceivedDataIsAvailable(HAL_I2C_BUS)){
            if(retry_counter > MAX_TRIALS)
                return false;
            retry_counter++;
        }
        /* read data */
        data[Index++] = I2CGetByte(HAL_I2C_BUS);
        /* write ack (because we want the next byte) */
        if(Index < HAL_EEPROM_PAGE_SIZE){
            I2CAcknowledgeByte(HAL_I2C_BUS,true);
            retry_counter = 0;
            while(!I2CAcknowledgeHasCompleted(HAL_I2C_BUS)){
                if(retry_counter > MAX_TRIALS){
                    return false;
                }else{
                    retry_counter ++;
                }
            }
        }
    }
    stop_transfer();
    return true;
}

bool hal_eeprom_write_page(uint16_t address, void* _data, size_t size){
    uint8_t* data = _data;
    assert(address < HAL_EEPROM_SIZE/HAL_EEPROM_PAGE_SIZE);
    assert(size <= HAL_EEPROM_PAGE_SIZE);
    I2C_7_BIT_ADDRESS eeprom_address;
    I2C_FORMAT_7_BIT_ADDRESS(eeprom_address,HAL_EEPROM_ADDRESS,I2C_WRITE);
    static uint8_t i2c_data[3];
    /* i2c data size */
    int dsize = 3, i = 0;
    uint16_t new_address = address*HAL_EEPROM_PAGE_SIZE;
    i2c_data[0] = eeprom_address.byte;
    i2c_data[2] = new_address & 0x00FF;
    i2c_data[1] = (new_address >> 8) & 0xFF;
    /*wait while bus is bussy*/
    if(!start_transfer(false))
        return false; // bus collision.
    for(i = 0; i < dsize; i++){
        if(!send_byte(i2c_data[i]))
            return false; // bus collision.
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS))
            return false; // no acknoweledge
    }
    i = 0;
    while(size--){
        if(!send_byte(data[i++]))
            return false;
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS))
            return false;
    }
    stop_transfer();
    /*wait while writting eeprom*/
    bool ack = false;
    int retry_counter = 0;
    do{
        if(!start_transfer(false))
            return false; // bus collision
        if(!send_byte(eeprom_address.byte))
            return false; // bus collision
        ack = I2CByteWasAcknowledged(HAL_I2C_BUS);
        stop_transfer();
        if(retry_counter > MAX_TRIALS)
            return false; // Max trials expired. Return with error.
        retry_counter++;
    }while(!ack); /// block until ack. (while eeprom busy writting data.).
    return true;
}

bool hal_eeprom_read_byte(uint16_t address, uint8_t* data){
    assert(address < HAL_EEPROM_SIZE);
    assert(data != NULL);
    uint8_t i2c_data[3];
    I2C_7_BIT_ADDRESS eeprom_address;
    int Index=0, dsize = 3;
    bool success = true;
    I2C_FORMAT_7_BIT_ADDRESS(eeprom_address, HAL_EEPROM_ADDRESS, I2C_WRITE);
    i2c_data[0] = eeprom_address.byte;
    i2c_data[2] = address & 0x00FF;
    i2c_data[1] = (address>>8) & 0x00FF;
    /*wait while bus is bussy*/
    if(!start_transfer(false))
        return false; // bus collision
    while( success & (Index < dsize) ){
        // Transmit a byte
        if (send_byte(i2c_data[Index])){
            // Advance to the next byte
            Index++;
        }else{
            success = false;
        }
        // Verify that the byte was acknowledged
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS)){
            return false; // No ack.
        }
    }
    // Restart and send the EEPROM's internal address to switch to a read transfer
    // Send a Repeated Started condition
    if( !start_transfer(TRUE) ){
        return false; // bus collision
    }
    // Transmit the address with the READ bit set
    I2C_FORMAT_7_BIT_ADDRESS(eeprom_address, HAL_EEPROM_ADDRESS, I2C_READ);
    if (send_byte(eeprom_address.byte)){
        // Verify that the byte was acknowledged
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS)){
            return false; // no ack
        }
    }else{
        return false; // bus collision
    }
    // Read the data from the desired address
    if(I2CReceiverEnable(HAL_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW){
        return false; // overflow
    }else{
        while(!I2CReceivedDataIsAvailable(HAL_I2C_BUS));
        *data = I2CGetByte(HAL_I2C_BUS);
    }
    //I2CAcknowledgeByte(EEPROM_I2C_BUS,false);
    stop_transfer();
    return true;
}

bool hal_i2c_read_byte(uint8_t device_address, uint16_t address, uint8_t *data){
    uint8_t i2c_data[3];
    I2C_7_BIT_ADDRESS dev_address;
    int Index=0, dsize = 2;
    bool success = true;
    I2C_FORMAT_7_BIT_ADDRESS(dev_address, device_address, I2C_WRITE);
    i2c_data[0] = dev_address.byte;
    i2c_data[2] = 0x01;//address & 0x00FF;
    i2c_data[1] = 0x00;//(address>>8) & 0x00FF;
    /*wait while bus is bussy*/
    if(!start_transfer(false))
        return false; // bus collision
    while( success & (Index < dsize) ){
        // Transmit a byte
        if (send_byte(i2c_data[Index])){
            // Advance to the next byte
            Index++;
        }else{
            success = false;
        }
        // Verify that the byte was acknowledged
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS)){
            return false; // No ack.
        }
    }
    // Restart and send the EEPROM's internal address to switch to a read transfer
    // Send a Repeated Started condition
    if( !start_transfer(TRUE) ){
        return false; // bus collision
    }
    // Transmit the address with the READ bit set
    I2C_FORMAT_7_BIT_ADDRESS(dev_address, device_address, I2C_READ);
    if (send_byte(dev_address.byte)){
        // Verify that the byte was acknowledged
        if(!I2CByteWasAcknowledged(HAL_I2C_BUS)){
            return false; // no ack
        }
    }else{
        return false; // bus collision
    }
    // Read the data from the desired address
    if(I2CReceiverEnable(HAL_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW){
        return false; // overflow
    }else{
        while(!I2CReceivedDataIsAvailable(HAL_I2C_BUS));
        *data = I2CGetByte(HAL_I2C_BUS);
    }
    //I2CAcknowledgeByte(EEPROM_I2C_BUS,false);
    stop_transfer();
    return true;
}

bool start_transfer(bool restart){
    I2C_STATUS  status;
    /* Send the Start (or Restart) signal */
    if(restart){
        I2CRepeatStart(HAL_I2C_BUS);
    }else{
        /* Wait for the bus to be idle, then start the transfer */
        while( !I2CBusIsIdle(HAL_I2C_BUS) );
        if(I2CStart(HAL_I2C_BUS) != I2C_SUCCESS){
            return false;
        }
    }
    /* Wait for the signal to complete */
    do{
        status = I2CGetStatus(HAL_I2C_BUS);
    } while ( !(status & I2C_START) );
    return true;
}

bool send_byte( uint8_t data )
{
    /* Wait for the transmitter to be ready */
    while(!I2CTransmitterIsReady(HAL_I2C_BUS));
    /* Transmit the byte */
    if(I2CSendByte(HAL_I2C_BUS, data) == I2C_MASTER_BUS_COLLISION){
        return false;
    }
    /* Wait for the transmission to finish */
    while(!I2CTransmissionHasCompleted(HAL_I2C_BUS));
    return true;
}

void stop_transfer( void )
{
    I2C_STATUS  status;
    /* Send the Stop signal */
    I2CStop(HAL_I2C_BUS);
    /* Wait for the signal to complete */
    do{
        status = I2CGetStatus(HAL_I2C_BUS);
    } while ( !(status & I2C_STOP) );
}
