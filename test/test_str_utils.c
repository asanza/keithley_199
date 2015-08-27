#include "unity.h"
#include "strutils.h"
#include "dtoa.h"

void setUp(void){
}

void tearDown(void){
}

void test_strutils(void){
  double x = 1.1;
  double y = 212.23;
  x = x/y;
  TEST_ASSERT_EQUAL_DOUBLE(x, 5.18305611836e-3);
  char* num = " 5.18305611836e-3";
  x = utils_strtod(num);
  TEST_ASSERT_EQUAL_DOUBLE(5.18305611836e-3, x);
  char buffer[10];
  utils_dtostr(buffer, 9, x);
  TEST_ASSERT_EQUAL_STRING(" 0.00518306", buffer);
  utils_dtostr(buffer, 5, 2.342345e2);
  TEST_ASSERT_EQUAL_STRING(" 234.23", buffer);
  utils_dtostr(buffer, 5, -2.342345e2);
  TEST_ASSERT_EQUAL_STRING("-234.23", buffer);
}
