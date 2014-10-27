/*! ****************************************************************************
 * File:   newmain.c
 * Author: Grant
 *
 * Description:
 * Contains the functionality for the Serial module. All variables and settings
 * concerning the serial module, such as the receive and transmit circular buffers
 * are private to this module. The interface functions allow all valid access to the module.
 *
 * Duties:
 *      -Stores an received characters in the received buffer
 *      -Stores any characters to be transmitted
 *      -Transmits anything in transmit buffer via interrupts
 *      -Accessor functions for using and querying buffers
 *
 * Functions:
 *
 *
 * Created on 7 September 2014, 4:12 PM
 ******************************************************************************/

#include "Common.h"
#include <usart.h>
#include "CircularBuffers.h"

//Interrupt macros
#define TX_INT_CLEAR() PIR1bits.TXIF = 0
#define RC_INT_CLEAR() PIR1bits.RCIF = 0
#define TX_INT_ENABLE() TX_INT_CLEAR(); PIE1bits.TXIE = 1
#define RC_INT_ENABLE() RC_INT_CLEAR(); PIE1bits.RCIE = 1
#define TX_INT_DISABLE() PIE1bits.TXIE = 0
#define RC_INT_DISABLE() PIE1bits.RCIE = 0

//ASCII definitions
#define CR 0x0D
#define NL 0x0A
#define ESC 0x1B
#define TAB 0x09
#define BS 0x07

//Local Function Prototypes
static volatile circularBuffer receive_buffer;
static volatile circularBuffer transmit_buffer;
static volatile char carriageReturn = 0;
static volatile char escPressed = 0;

/*! **********************************************************************
 * Function: configureSerial(void)
 *
 * Include: Serial.h
 *
 * Description: Configures the serial ready for communication
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configureSerial(void)
{
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    RCONbits.IPEN = 1;

    //Initialise the serial buffers
    init(transmit_buffer);
    init(receive_buffer);
    carriageReturn = 0;
    escPressed = 0;

    //Open the USART module
#ifdef MNML
    OpenUSART(USART_TX_INT_ON & USART_RX_INT_ON & USART_BRGH_HIGH & USART_EIGHT_BIT & USART_ASYNCH_MODE, 64);
#else
    OpenUSART(USART_TX_INT_ON & USART_RX_INT_ON & USART_BRGH_HIGH & USART_EIGHT_BIT & USART_ASYNCH_MODE, 25);
#endif

}

/*! **********************************************************************
 * Function: transmit(char *string)
 *
 * Include: Serial.h
 *
 * Description: Begins transmitting the string over serial (interrupt driven)
 *
 * Arguments: string - pointer to the beginning of the string to transmit
 *
 * Returns: None
 *
 * NOTE: Must be Null Terminated! Cannot receive a literal.
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

/*! **********************************************************************
 * Function: transmit(char *string)
 *
 * Include: Serial.h
 *
 * Description: Begins transmitting the string over serial (interrupt driven)
 *
 * Arguments: string - pointer to the beginning of the string to transmit
 *
 * Returns: None
 *
 * NOTE: Must be Null Terminated! Cannot receive a literal.
 *************************************************************************/
void transmitROM(const rom char *string)
{
    char temp_buf[BUFFERLENGTH];
    char *temp_point = temp_buf;

    strcpypgm2ram(temp_buf, string);

    //Push the string onto the transmit buffer
    for (; *temp_point; temp_point++)
    {
        push(*temp_point, transmit_buffer);
    }

    //Return if there is nothing to transmit
    if (empty(transmit_buffer)) return;

    //Enable TX interrupts
    TX_INT_ENABLE();
}

/*! **********************************************************************
 * Function: transChar(char c)
 *
 * Include: Serial.h
 *
 * Description: Transmits a single character
 *
 * Arguments: c - character to transmit
 *
 * Returns: None
 *************************************************************************/
void transChar(char c)
{
    //Push character onto the transmit buffer
    push(c, transmit_buffer);

    //Enable TX interrupts
    TX_INT_ENABLE();
}

/*! **********************************************************************
 * Function: receiveEmpty(void)
 *
 * Include: Serial.h
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

/*! **********************************************************************
 * Function: receivePeek(void)
 *
 * Include: Serial.h
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

/*! **********************************************************************
 * Function: receivePop(void)
 *
 * Include: Serial.h
 *
 * Description: Pops the next received character from the received buffer
 *
 * Arguments: None
 *
 * Returns: The next character from the receive buffer
 *************************************************************************/
char receivePop(void)
{
    char c = pop(receive_buffer);
    return c;
}

/*! **********************************************************************
 * Function: receiveCR(void)
 *
 * Include: Serial.h
 *
 * Description: Indicates whether a Carriage Return has been received
 *
 * Arguments: None
 *
 * Returns: non-zero if CR has been received, zero otherwise
 *************************************************************************/
char receiveCR(void)
{
    return carriageReturn;
}

/*! **********************************************************************
 * Function: receiveEsc(void)
 *
 * Include:
 *
 * Description: Indicates whether an Escape character has been received
 *
 * Arguments: None
 *
 * Returns: non-zero if the Esc has been received, zero otherwise
 *************************************************************************/
char receiveEsc(void)
{
    return escPressed;
}

/*! **********************************************************************
 * Function: popEsc(void)
 *
 * Include:
 *
 * Description: Processes the Esc command and removes any input before the
 *              Esc command.
 *
 * Arguments: None
 *
 * Returns:
 *************************************************************************/
void popEsc(void)
{
    while (!empty(receive_buffer))
    {
        pop(receive_buffer);
    }
    escPressed--;
    return;
}

/*! **********************************************************************
 * Function: readString(char *string)
 *
 * Include: Serial.h
 *
 * Description: Writes all received data up to a carriage return into given
 *              location.
 *
 * Arguments: string - Pointer to location to store received data
 *
 * Returns: Received data including the carriage return
 *
 * Remarks: Make sure that you reserve at least BUFFERLENGTH elements at the
 *          location pointed to by string before calling this function.
 *************************************************************************/
void readString(char *string)
{
    char c, e;
    e = empty(receive_buffer);
    c = pop(receive_buffer);
    while (c != CR && !e)
    {
        *(string++) = c;
        e = empty(receive_buffer);
        c = pop(receive_buffer);
    }
    *string = c;
    carriageReturn--;
}

/*! **********************************************************************
 * Function: transmitted(void)
 *
 * Include: Serial.h
 *
 * Description: returns non-zero if the message has been completely transmited
 *              e.g. if the transmit buffer is empty
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
char transmitComplete(void)
{
    return empty(transmit_buffer);
}

/*! **********************************************************************
 * Function: serialISR(void)
 *
 * Include: Serial.h
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
    char last;

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
        last = peek(receive_buffer);

        if (data == ESC) escPressed++;
        else
        {
            //Allows the user to remove/change transmitted data
            if (data == BS && last != CR && last != ESC && last != NL )
            {
                pop(receive_buffer);
            }
            else
            {
                //push the received data onto the received buffer
                push(data, receive_buffer);
                if (data == CR) carriageReturn++;

                //Clear interrupt flag
                RC_INT_CLEAR();
            }
        }
    }
}

void escANSI()
{
}