/* 
 * File:   CircularBuffers.h
 * Author: Grant
 *
 * Description: Contains Circular Buffer functionality and structure definitions
 *
 * Created on 8 October 2014, 10:30 AM
 */

//Ensure there is only 1 inclusion of this file in the preprocessor execution
#ifndef BUFFERS_H

//Buffer related macro functionality
#define incMod(ptr) if(ptr==BUFFERLENGTH-1) ptr = 0; else ptr++;
#define empty(buf) (buf.tail == buf.head)
#define full(buf) (buf.head == (buf.tail + 1) % BUFFERLENGTH)
#define peek(buf) buf.data[buf.head]

#define push(byte, buf) buf.data[buf.tail] = byte; if(full(buf)) incMod(buf.head); incMod(buf.tail)
#define pop(buf) buf.data[buf.head]; if (!empty(buf)) incMod(buf.head)
#define init(buf) buf.tail = 0; buf.head = 0

//NOTE: The BUFFERLENGTH can be redefined at the top of any module if a different length is desired
#define BUFFERLENGTH 30

//Cicular Buffer data type
typedef struct
{
    unsigned char head;
    unsigned char tail;
    unsigned char data[BUFFERLENGTH];
} circularBuffer;

#define BUFFERS_H 0
#endif