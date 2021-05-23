#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

typedef struct {
    char *data;
    int head;
    int tail;
    int byteCount;
    int ringSize;
} RingBuffer_t;

typedef enum {
    E_DONE,
    E_OOPS,
    E_OK,
} Error_t;

RingBuffer_t *ringInit(int ringSize);
char ringRead(RingBuffer_t *buffer);
unsigned char ringIsEmpty(RingBuffer_t *buffer);
unsigned char ringIsFull(RingBuffer_t *buffer);
Error_t ringPush(RingBuffer_t *buffer, char *data, int dataLen);
static unsigned char haveCapacity(RingBuffer_t *buffer, int len);

#endif /* RINGBUFFER_H_ */

