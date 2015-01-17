#ifndef OS_TEST_H
#define OS_TEST_H

#include <stdint.h>

typedef void* QueueHandle_t;

typedef long BaseType_t;

#define portBASE_TYPE long

typedef uint32_t TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffffffffUL
#define pdTRUE 1

#define errQUEUE_FULL 0

QueueHandle_t xQueueCreate(int size, int elem_size);

BaseType_t xQueueSend(QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait);

BaseType_t xQueuePeek(QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait);

BaseType_t xQueueReceiveFromISR( QueueHandle_t xQueue, void * const pvBuffer, BaseType_t * const pxHigherPriorityTaskWoken );

BaseType_t xQueueIsQueueEmptyFromISR( const QueueHandle_t xQueue );

BaseType_t xQueueSendFromISR( QueueHandle_t xQueue, const void * const pvItemToQueue, BaseType_t * const pxHigherPriorityTaskWoken);

void uart3_int_wrapper(void);

#endif