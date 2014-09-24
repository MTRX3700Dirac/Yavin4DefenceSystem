/*
 * File:   newmain.c
 * Author: Grant
 *
 * Description: Contains the functionality for the Serial module
 *
 * Created on 7 September 2014, 4:12 PM
 */
//#include <p18f4520.h>
#include "Common.h"
#include <usart.h>

//Buffer related macro functionality
#define incMod(ptr) (ptr = ++ptr % BUFFERLENGTH)
#define empty(buf) (buf.head == buf.tail)
#define full(buf) (buf.tail == (buf.head + 1) % BUFFERLENGTH)
#define peek(buf) buf.data[buf.tail]

#define push(byte, buf) buf.data[buf.head] = byte; if(full(buf)) incMod(buf.tail); incMod(buf.head)
#define pop(buf) buf.data[buf.tail]; if (!empty(buf)) incMod(buf.tail)
#define init(buf) buf.head = 0; buf.tail = 0

//Interrupt macros
#define TX_INT_CLEAR() PIR1bits.TXIF = 0
#define RC_INT_CLEAR() PIR1bits.RCIF = 0
#define TX_INT_ENABLE() TX_INT_CLEAR(); PIE1bits.TXIE = 1
#define RC_INT_ENABLE() RC_INT_CLEAR(); PIE1bits.RCIE = 1
#define TX_INT_DISABLE() PIE1bits.TXIE = 0
#define RC_INT_DISABLE() PIE1bits.RCIE = 0


#define BUFFERLENGTH 30

//Cicular Buffer data type
typedef struct
{
    unsigned char head;
    unsigned char tail;
    unsigned char data[BUFFERLENGTH];
} circularBuffer;

circularBuffer receive_buffer;
circularBuffer transmit_buffer;

/* **********************************************************************
 * Function: configureSerial(void)
 *
 * Include:
 *
 * Description: Configures the serial ready for communication
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configureSerial(void)
{
    //Initialise the serial buffers
    init(transmit_buffer);
    init(receive_buffer);

    //Open the USART module
    OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON & USART_BRGH_HIGH & USART_EIGHT_BIT & USART_ASYNCH_MODE, 25);
}

/* **********************************************************************
 * Function: transmit(char *string)
 *
 * Include:
 *
 * Description: Begins transmitting the string over serial (interrupt driven)
 *
 * Arguments: string - pointer to the beginning of the string to transmit
 *
 * Returns: None
 *************************************************************************/
void transmit(char *string)
{
    //Push the string onto the transmit buffer
    for (; *string; string++)
    {
        push(*string, transmit_buffer);
    }

    //Return if there is nothing to transmit
    if (empty(transmit_buffer)) return;

    //Enable TX interrupts
    TX_INT_ENABLE();
}

/* **********************************************************************
 * Function: receiveEmpty(void)
 *
 * Include:
 *
 * Description: Indicates if the receive buffer is empty
 *
 * Arguments: None
 *
 * Returns: returns true if the recieve buffer is empty
 *************************************************************************/
char receiveEmpty(void)
{
    return empty(receive_buffer);
}

/* **********************************************************************
 * Function: receivePeek(void)
 *
 * Include:
 *
 * Description: Returns the next character in the receive buffer without
 *              removing it from the buffer
 *
 * Arguments: None
 *
 * Returns: The next received character
 *************************************************************************/
char receivePeek(void)
{
    return peek(receive_buffer);
}

/* **********************************************************************
 * Function: receivePop(void)
 *
 * Include:
 *
 * Description: Pops the next received character from the received buffer
 *
 * Arguments: None
 *
 * Returns: The next character from the receive buffer
 *************************************************************************/
char receivePop(void)
{
    return pop(receive_buffer);
}

/* **********************************************************************
 * Function: serialISR(void)
 *
 * Include:
 *
 * Description: Acts as the interrupt service routine for the serial module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void serialISR(void)
{
    unsigned char data;
    
    //Check which serial interrupt instance was thrown
    if (TX_INT)
    {
        //Return if there is nothing in the transmit buffer
        if (empty(transmit_buffer))
        {
            TX_INT_DISABLE();
            return;
        }
        
        data = pop(transmit_buffer);
        WriteUSART(data);

        //Clear interrupt flag
        TX_INT_CLEAR();
    }
    else if (RC_INT)
    {
        data = ReadUSART();

        //push the received data onto the received buffer
        push(data, receive_buffer);

        //Clear interrupt flag
        RC_INT_CLEAR();
    }
}