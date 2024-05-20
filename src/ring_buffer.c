#include "ring_buffer.h"

void ring_buffer_put(struct ring_buffer *rb,uint8_t data){
    rb->buffer[rb->head] = data;
    (rb->head)++;
    if(rb->head==rb->size){
        rb->head=0U;
    }
    if(rb->head==rb->tail){
            rb->full=true;
    }
}

uint8_t ring_buffer_get(struct ring_buffer *rb){
    uint8_t data = rb->buffer[rb->tail];
    (rb->tail)++;
    if(rb->tail==rb->size){
        rb->tail=0U;
    }
    if(rb->full){
    rb->full=false;
    }
    
    return data;
}

uint8_t ring_buffer_peek(struct ring_buffer *rb){
    return rb->buffer[rb->tail];
}

bool ring_buffer_empty(struct ring_buffer *rb){
    return (rb->head == rb->tail)&&(!rb->full);
}
bool ring_buffer_full(struct ring_buffer *rb){
    if(rb->head!=rb->tail){
        return false;
    }
    return rb->full;
}