#include "unity.h"
#include "hal_adc.h"
#include "mock_os_test.h"

extern unsigned int integration_period;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_hal_adc_set_integration_period(void)
{
  hal_adc_set_integration_period(16667);
  TEST_ASSERT_EQUAL(41667, integration_period);
  hal_adc_set_integration_period(20000);
  TEST_ASSERT_EQUAL(50000, integration_period);
}

void test_hal_adc_init(void){
  xQueueCreate_IgnoreAndReturn(0);
  hal_adc_init(16667);
  TEST_ASSERT_EQUAL_UINT(41667, integration_period);
  xQueueCreate_IgnoreAndReturn(0);
  hal_adc_init(20000);
  TEST_ASSERT_EQUAL(50000, integration_period);
}
