/**@brief stdio implementation for use with freertos and xc32 compiler
 * (c) Diego F. Asanza
 */

#include <peripheral/uart.h>
#include <peripheral/pps.h>

#include "HardwareProfile.h"
#include <FreeRTOS.h>
#include <queue.h>
#include <hal.h>

#if USB_UART == UART2
void __attribute__((interrupt(), vector(_UART_2_VECTOR)))
                                                 UARTUSBInterruptWrapper(void);
#else
#error "please define an interrupt vector for the usb uart"
#endif

#define RX_QUEUE_SIZE 50
static QueueHandle_t rx_queue;

void hal_usbuart_init()
{
    CONFIGURE_UART3_PPS();
    /* Initialize Uart Module */
    UARTConfigure(USB_UART, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(USB_UART, UART_INTERRUPT_ON_TX_BUFFER_EMPTY | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(USB_UART, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(USB_UART, SYS_CLK, USB_UART_BAUDRATE);
    /* set uart module interrupt priority */
    INTSetVectorPriority(INT_VECTOR_UART(USB_UART),USB_UART_PRIORITY);
    /* disable uart tx interrupt */
    INTEnable(INT_SOURCE_UART_RX(USB_UART),INT_ENABLED);
    UARTEnable(USB_UART, UART_ENABLE_FLAGS(UART_PERIPHERAL|UART_RX|UART_TX));
    rx_queue = xQueueCreate(RX_QUEUE_SIZE,sizeof(uint8_t));
}

void hal_usbuart_puts(char* string){
    if(!string) return;
    while(string++!='\0'){
        while(!UARTTransmitterIsReady(USB_UART));
        UARTSendDataByte(USB_UART,*string);
    }
}

void hal_usbuart_putc(char c){
    while(!UARTTransmitterIsReady(USB_UART));
    UARTSendDataByte(USB_UART, c);
}

void _mon_putc(char c){
    hal_usbuart_putc(c);
}

void UARTUSBInterruptHandler(){
    portBASE_TYPE xHigherPriorityTaskWoken;
    if(INTGetFlag(INT_SOURCE_UART_TX(USB_UART))){
        //Manage TX interrupt
        INTClearFlag(INT_SOURCE_UART_TX(USB_UART));
    }
    if(INTGetFlag(INT_SOURCE_UART(USB_UART))){
        /* get data from buffer and put in queue */
        while(UARTReceivedDataIsAvailable(USB_UART)){
            char t = UARTGetDataByte(USB_UART);
            xQueueSendFromISR(rx_queue,&t,&xHigherPriorityTaskWoken);
        }
        INTClearFlag(INT_SOURCE_UART_RX(USB_UART));
    }
    if(INTGetFlag(INT_SOURCE_UART_ERROR(USB_UART))){
        UART_LINE_STATUS line_status = UARTGetLineStatus(USB_UART);
        switch(line_status){
            case UART_OVERRUN_ERROR: break;
        }
    }
}

int hal_usbuart_receive(char* buffer, int size){
    int i = 0;
    while(size--){
        i++;
        xQueueReceive(rx_queue,buffer++,portMAX_DELAY);
    }
    return i;
}

void hal_usbuart_readline(char* buffer, int size){
    do{
        xQueueReceive(rx_queue, buffer++, portMAX_DELAY);
    }while(size--!=2 && !((*(buffer - 1)=='\r')||(*(buffer - 1)=='\n')));
    *buffer = 0; //null terminator
}