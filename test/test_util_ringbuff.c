#include "unity.h"
#include "util_ringbuff.c"

#define BUFFSIZE 20

void setUp(void){
  /* clear buffer pool before reusing */
  used_buffers = 0;
}

void tearDown(void){
}

void test_ringbuff_new(void){
  util_ringbuffer* buff;
  unsigned char data[BUFFSIZE];
  buff = util_ringbuffer_new(data, BUFFSIZE); 
  TEST_ASSERT_NOT_EQUAL(NULL,buff);
  buff = util_ringbuffer_new(data, BUFFSIZE);
  TEST_ASSERT_NOT_EQUAL(NULL,buff);
  buff = util_ringbuffer_new(data, BUFFSIZE);
  TEST_ASSERT_EQUAL(NULL,buff);
}

void test_ringbuff_put_get(void){
  util_ringbuffer* buff;
  unsigned char data[BUFFSIZE];
  buff = util_ringbuffer_new(data, BUFFSIZE);
  TEST_ASSERT_NOT_EQUAL(NULL,buff);
  /* put data into buffer */
  unsigned char i = 0;
  while(util_ringbuffer_is_full(buff)!=UTIL_RINGBUFFER_IS_FULL){
    util_ringbuffer_put(buff,i);
    TEST_ASSERT_EQUAL(i,data[i]);
    i++;
  }
  /* check if buffer full */
  int t;
  t = util_ringbuffer_is_full(buff);
  TEST_ASSERT_EQUAL(t,UTIL_RINGBUFFER_IS_FULL);
  /* get data from buffer */
  t = util_ringbuffer_is_empty(buff);
  TEST_ASSERT_NOT_EQUAL(t,UTIL_RINGBUFFER_IS_EMPTY);
  /* get data from buffer */
  i = 0;
  while(util_ringbuffer_is_empty(buff)!=UTIL_RINGBUFFER_IS_EMPTY){
    unsigned char c;
    c = util_ringbuffer_get(buff);
    TEST_ASSERT_EQUAL(i,c);
    i++;
  }
  i = 0;
  while(util_ringbuffer_is_full(buff)!=UTIL_RINGBUFFER_IS_FULL){
    util_ringbuffer_put(buff,i++);
  }
  int j = 0, k = 8;
  while(k-- >= 0){
    unsigned char c;
    c = util_ringbuffer_get(buff);
    TEST_ASSERT_EQUAL(j++,c);
  }
  while(util_ringbuffer_is_full(buff)!=UTIL_RINGBUFFER_IS_FULL){
    util_ringbuffer_put(buff,i++);
  }
  k = 12;
  while(k-- >= 0){
    unsigned char c;
    c = util_ringbuffer_get(buff);
    TEST_ASSERT_EQUAL(j++,c);
  }
}
