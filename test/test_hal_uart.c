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
  /* try to open port 3 */
  hal_uart_port port = hal_uart_open(HAL_UART_PORT_3,HAL_UART_BAUD_9600,
    HAL_UART_PARITY_NONE, HAL_UART_1_STOP_BITS, NULL);
  TEST_ASSERT_EQUAL_MESSAGE(HAL_UART_PORT_3, port,"Initialize PORT");
  /* look if baudrate was properly set. PBClk 80MHz */
  TEST_ASSERT_EQUAL(520, U3BRG);
  /* look if parity and stop bits where properly set */
  TEST_ASSERT_EQUAL(0x00, U3MODEbits.PDSEL);
  TEST_ASSERT_EQUAL(0x00, U2MODEbits.STSEL);
}
