#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ringBuffer.h"

RingBuffer_t *ringInit(int ringSize)
{
    RingBuffer_t *buffer = malloc(sizeof(RingBuffer_t));
    buffer->ringSize = ringSize;
    if((buffer->data = malloc(sizeof(char) * ringSize)) == NULL)
        return NULL;
    buffer->head = 0;
    buffer->tail = 0;
    buffer->byteCount = 0;
    return buffer;
}

Error_t ringPush(RingBuffer_t* buffer, char* data, int dataLen)
{
    if (!haveCapacity(buffer, dataLen))
        return E_OOPS;
//    DINT; Disable interrupts or a mutex for preventing race condition if is necessary
    int i;
    for (i = 0 ; i < dataLen ; i++) {
        *(buffer->data + buffer->head) = *(data + i);
        buffer->head++;
        buffer->head = buffer->head < buffer->ringSize ? buffer->head : 0;
        buffer->byteCount++;
    }
//    EINT;
    return E_DONE;
}

char ringRead(RingBuffer_t* buffer)
{
//    DINT; Disable interrupts or a mutex for preventing race condition if is necessary
    char data = *(buffer->data + buffer->tail);
    buffer->tail++;
    buffer->tail = buffer->tail < buffer->ringSize ? buffer->tail : 0;
    buffer->byteCount--;
//    EINT;
    return data;
}

unsigned char ringIsEmpty(RingBuffer_t *buffer)
{
    return (buffer->byteCount == 0);
}

unsigned char ringIsFull(RingBuffer_t *buffer)
{
    return (buffer->byteCount >= buffer->ringSize);
}

static unsigned char haveCapacity(RingBuffer_t *buffer, int len)
{
    return (buffer->byteCount + len < buffer->ringSize);
}

