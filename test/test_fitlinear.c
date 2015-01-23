#include "unity.h"
#include "fitlinear.h"

void setUp(void){
}

void tearDown(void){
}

void test_fitlinear(void){

  double x[3] = {3.32,6.64,9.96};
  double y[3] = {3.31,6.65,9.99};
  
  double c0, c1;

  int t = fit_linear(x,y,3,&c0,&c1);

  TEST_ASSERT_EQUAL_DOUBLE( 1.0060240963855418,c1);
  TEST_ASSERT_EQUAL_DOUBLE(-0.0299999999999962,c0);
}
