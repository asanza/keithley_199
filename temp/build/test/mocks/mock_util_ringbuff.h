/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_UTIL_RINGBUFF_H
#define _MOCK_UTIL_RINGBUFF_H

#include "util_ringbuff.h"

/* Ignore the following warnings, since we are copying code */
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"

void mock_util_ringbuff_Init(void);
void mock_util_ringbuff_Destroy(void);
void mock_util_ringbuff_Verify(void);




#define util_ringbuffer_new_IgnoreAndReturn(cmock_retval) util_ringbuffer_new_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void util_ringbuffer_new_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, util_ringbuffer* cmock_to_return);
#define util_ringbuffer_new_ExpectAndReturn(data_buffer, buffer_size, cmock_retval) util_ringbuffer_new_CMockExpectAndReturn(__LINE__, data_buffer, buffer_size, cmock_retval)
void util_ringbuffer_new_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, unsigned char* data_buffer, int buffer_size, util_ringbuffer* cmock_to_return);
typedef util_ringbuffer* (* CMOCK_util_ringbuffer_new_CALLBACK)(unsigned char* data_buffer, int buffer_size, int cmock_num_calls);
void util_ringbuffer_new_StubWithCallback(CMOCK_util_ringbuffer_new_CALLBACK Callback);
#define util_ringbuffer_put_IgnoreAndReturn(cmock_retval) util_ringbuffer_put_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void util_ringbuffer_put_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, int cmock_to_return);
#define util_ringbuffer_put_ExpectAndReturn(buffer, data, cmock_retval) util_ringbuffer_put_CMockExpectAndReturn(__LINE__, buffer, data, cmock_retval)
void util_ringbuffer_put_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, util_ringbuffer* buffer, unsigned char data, int cmock_to_return);
typedef int (* CMOCK_util_ringbuffer_put_CALLBACK)(util_ringbuffer* buffer, unsigned char data, int cmock_num_calls);
void util_ringbuffer_put_StubWithCallback(CMOCK_util_ringbuffer_put_CALLBACK Callback);
#define util_ringbuffer_get_IgnoreAndReturn(cmock_retval) util_ringbuffer_get_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void util_ringbuffer_get_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, int cmock_to_return);
#define util_ringbuffer_get_ExpectAndReturn(buffer, data, cmock_retval) util_ringbuffer_get_CMockExpectAndReturn(__LINE__, buffer, data, cmock_retval)
void util_ringbuffer_get_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, util_ringbuffer* buffer, unsigned char* data, int cmock_to_return);
typedef int (* CMOCK_util_ringbuffer_get_CALLBACK)(util_ringbuffer* buffer, unsigned char* data, int cmock_num_calls);
void util_ringbuffer_get_StubWithCallback(CMOCK_util_ringbuffer_get_CALLBACK Callback);
#define utils_blocking_delay_ms_Ignore() utils_blocking_delay_ms_CMockIgnore()
void utils_blocking_delay_ms_CMockIgnore(void);
#define utils_blocking_delay_ms_Expect(ms) utils_blocking_delay_ms_CMockExpect(__LINE__, ms)
void utils_blocking_delay_ms_CMockExpect(UNITY_LINE_TYPE cmock_line, unsigned int ms);
typedef void (* CMOCK_utils_blocking_delay_ms_CALLBACK)(unsigned int ms, int cmock_num_calls);
void utils_blocking_delay_ms_StubWithCallback(CMOCK_utils_blocking_delay_ms_CALLBACK Callback);

#endif