/* 
 * File:   CircularBuffers.h
 * Author: Grant
 *
 * Description: Contains Circular Buffer functionality and structure definitions
 *
 * Created on 8 October 2014, 10:30 AM
 */

//Buffer related macro functionality
#define incMod(ptr) (ptr = ++ptr % BUFFERLENGTH)
#define empty(buf) (buf.head == buf.tail)
#define full(buf) (buf.tail == (buf.head + 1) % BUFFERLENGTH)
#define peek(buf) buf.data[buf.tail]

#define push(byte, buf) buf.data[buf.head] = byte; if(full(buf)) incMod(buf.tail); incMod(buf.head)
#define pop(buf) buf.data[buf.tail]; if (!empty(buf)) incMod(buf.tail)
#define init(buf) buf.head = 0; buf.tail = 0

//NOTE: The BUFFERLENGTH can be redefined at the top of any module if a different length is desired
#define BUFFERLENGTH 30

//Cicular Buffer data type
typedef struct
{
    unsigned char head;
    unsigned char tail;
    unsigned char data[BUFFERLENGTH];
} circularBuffer;

//Don't ask, this just stops MPLAB X flipping out about the circularBuffer typedef
#define thing 0