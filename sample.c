#include <stdint.h>
#include <stdio.h>
#include "ringBuffer.h"

int main() {
	RingBuffer_t *aBuffer;
	int ringSize = 100;
        aBuffer = ringInit(ringSize);
	char data[12] = {'R', 'i', 'n', 'g', ' ', 'B', 'u', 'f', 'f', 'e', 'r', '\0'};
        ringPush(aBuffer, data, sizeof(data));
	int i;
	for(i = 0 ; i < sizeof(data) ; i++)
		if (!ringIsEmpty(aBuffer)) 
	    		printf("%c", ringRead(aBuffer));
	return 0;
}
