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
  TEST_ASSERT_EQUAL_STRING("0.00518306", buffer);
  utils_dtostr(buffer, 5, 2.342345e2);
  TEST_ASSERT_EQUAL_STRING("234.24", buffer);
  utils_dtostr(buffer, 5, -2.342345e2);
  TEST_ASSERT_EQUAL_STRING("-234.24", buffer);
  utils_dtostr(buffer, 4, 2.44445);
  TEST_ASSERT_EQUAL_STRING("2.445", buffer);
  utils_dtofixstr(buffer, 6, 3, 8.23455);
  TEST_ASSERT_EQUAL_STRING(" 008.235", buffer);
  utils_dtofixstr(buffer, 6, 4, 8.23455);
  TEST_ASSERT_EQUAL_STRING(" 08.2346", buffer);
  utils_dtofixstr(buffer, 7, 6, -8.2345544);
  TEST_ASSERT_EQUAL_STRING("-8.234554", buffer);
  utils_dtostr(buffer, 6, -0.14805821886151949);
  TEST_ASSERT_EQUAL_STRING("-0.14806", buffer);
  utils_dtofixstr(buffer, 6, 3, -0.14805821886151949);
  TEST_ASSERT_EQUAL_STRING("-000.148", buffer);

  utils_dtostr(buffer, 6, -0.0014805821886151949);
  TEST_ASSERT_EQUAL_STRING("-0.00148", buffer);
  utils_dtofixstr(buffer, 6, 3, -0.0014805821886151949);
  TEST_ASSERT_EQUAL_STRING("-000.001", buffer);

}
