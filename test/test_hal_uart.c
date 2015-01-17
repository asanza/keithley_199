#include "unity.h"
#include "hal_uart.h"
#include <peripheral/uart.h>
#include "mock_util_ringbuff.h"
#include "mock_os_test.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_hal_uart_open(void)
{
  hal_uart_error err = hal_uart_open(0,9600,HAL_UART_PARITY_NONE,
				     HAL_UART_STOP_BITS_1);
  TEST_ASSERT_EQUAL_MESSAGE(HAL_UART_ERR_PORT_NOT_AVAIL,err, 
			    "Try to initialize not available port");
  /* try to open port 3 */
  QueueHandle_t t;
  xQueueCreate_ExpectAndReturn(TX_BUFFER_SIZE,sizeof(uint8_t),t);
  xQueueCreate_ExpectAndReturn(RX_BUFFER_SIZE,sizeof(uint8_t),t);
  err = hal_uart_open(3,9600,HAL_UART_PARITY_NONE, HAL_UART_STOP_BITS_1);
  TEST_ASSERT_EQUAL_MESSAGE(HAL_UART_ERR_NONE, err,"Initialize PORT");
  /* look if baudrate was properly set. PBClk 20MHz */
  TEST_ASSERT_EQUAL(520, U3BRG);
  /* look if parity and stop bits where properly set */
  TEST_ASSERT_EQUAL(0x00, U3MODEbits.PDSEL);
  TEST_ASSERT_EQUAL(0x00, U2MODEbits.STSEL);
}

void test_hal_uart_send_byte(){
  QueueHandle_t tx_queue = NULL;
  QueueHandle_t rx_queue = NULL;
  xQueueCreate_ExpectAndReturn(TX_BUFFER_SIZE,sizeof(uint8_t),tx_queue);
  xQueueCreate_ExpectAndReturn(RX_BUFFER_SIZE,sizeof(uint8_t),rx_queue);
  hal_uart_error err = hal_uart_open(3,9600,HAL_UART_PARITY_NONE,
				     HAL_UART_STOP_BITS_1);
//  uint8_t data = 0x34;
//  //xQueueSend_ExpectAndReturn(tx_queue,data,portMAX_DELAY,pdTRUE);
//  //hal_uart_send_byte(3,data);
//  TEST_ASSERT_EQUAL(data,U3TXREG);
}

