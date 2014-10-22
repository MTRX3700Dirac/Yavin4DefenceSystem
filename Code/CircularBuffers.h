/*! ****************************************************************************
 * File:   CircularBuffers.h
 * Author: Grant
 *
 * Description:
 * Contains Circular Buffer functionality and structure definitions. This allows
 * Circular Buffers to be used in any file by simply including this header.
 * Furthermore, circular buffer functionality can be altered on a program level.
 *
 * Contains:
 *      -Definition of CircularBuffer type
 *      -Peek, pop, push and init functionality
 *      -Empty, full, queries
 *
 * Created on 8 October 2014, 10:30 AM
 ******************************************************************************/

//Ensure there is only 1 inclusion of this file in the preprocessor execution
#ifndef BUFFERS_H

///Buffer related macro functionality
#define incMod(ptr) if(ptr==BUFFERLENGTH-1) ptr = 0; else ptr++;
#define empty(buf) (buf.tail == buf.head)
#define full(buf) (buf.head == (buf.tail + 1) % BUFFERLENGTH)
#define peek(buf) buf.data[buf.head]

#define push(byte, buf) buf.data[buf.tail] = byte; if(full(buf)) incMod(buf.head); incMod(buf.tail)
#define pop(buf) buf.data[buf.head]; if (!empty(buf)) incMod(buf.head)
#define init(buf) buf.tail = 0; buf.head = 0

//NOTE: The BUFFERLENGTH can be redefined at the top of any module if a different length is desired
#define BUFFERLENGTH 80

/*! ****************************************************************************
 * typedef of circularBuffer struct
 *
 * @brief Stores bytes of data in a circular buffer
 *
 * Length: BUFFERLENGTH
 *
 * Description:
 * Defines a circular buffer in which bytes of data can be placed, or removed at
 * any time in the correct order that they were pushed. The accompanying functionality
 * facilitates all necessary circular buffer related operations.
 * This implementation reduces the buffer length by 1 to differentiate between
 * full and empty states.
 * BUFFERLENGTH can be redefined in individual files to get different buffer lengths
 ******************************************************************************/
typedef struct
{
    unsigned char head;
    unsigned char tail;
    unsigned char data[BUFFERLENGTH];
} circularBuffer;

#define BUFFERS_H 0
#endif