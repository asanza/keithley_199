#include "unity.h"
#include "utils_math.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_utils_roundd_should_behavior(void)
{
  double ref = 0.23256433;
  double test = utils_roundd(ref, 4);
  TEST_ASSERT_EQUAL_DOUBLE(0.2326, test);

  ref = 0.2332242;
  test = utils_roundd(ref, 6);
  TEST_ASSERT_EQUAL_DOUBLE(0.233224, test);

}
