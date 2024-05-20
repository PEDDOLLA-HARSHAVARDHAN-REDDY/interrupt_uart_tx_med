#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_
#include<inttypes.h>
#include<stdbool.h>

struct ring_buffer
{
    uint8_t *buffer;
    uint8_t size;
    volatile uint8_t head;
    volatile uint8_t tail;
    volatile bool full;
};

uint8_t ring_buffer_peek(struct ring_buffer *rb);
bool ring_buffer_empty(struct ring_buffer *rb);
bool ring_buffer_full(struct ring_buffer *rb);
uint8_t ring_buffer_get(struct ring_buffer *rb);
void ring_buffer_put(struct ring_buffer *rb,uint8_t data);


#endif // _RING_BUFFER_H_