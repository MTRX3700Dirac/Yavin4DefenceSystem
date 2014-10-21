/*! ****************************************************************************
 * File:   User_Interface.c
 * Author: Grant
 *
 * Description:
 * Contains all the functionality for the User_Interface module.
 * Works the same way as the serial module, but for the user interface.
 *
 * Duties:
 *      -Stores any local user input in a receive buffer
 *      -Sends display data to the LCD
 *
 * Created on 15 September 2014, 1:21 PM
 ******************************************************************************/

#include "Common.h"
#include "CircularBuffers.h"

//Store anything entered by the user
circularBuffer receive;

/*! **********************************************************************
 * Function: display(TrackingData data)
 *
 * Include: User_Interface.h
 *
 * Description: displays the current tracking information
 *
 * Arguments: data - Struct which contains all known data concerning the
 *                   The position of the target. A Range of 0 indicates
 *                   that no target was observed.
 *
 * Returns: None
 *************************************************************************/
void display(TrackingData data)
{
    
}

/*! **********************************************************************
 * Function: userISR(void)
 *
 * Include: User_Interface.h
 *
 * Description: Acts as the ISR for the User_interface module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void userISR(void)
{
    
}

/*! **********************************************************************
 * Function: configUSER(void)
 *
 * Include: User_Interface.h
 *
 * Description: Configures the user interface for use
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configUSER(void)
{
    //Initialises the receive buffer
    init(receive);
}

/*! **********************************************************************
 * Function: readDial(void)
 *
 * Include:
 *
 * Description: Read the position of the dial
 *
 * Arguments: None
 *
 * Returns: The dial position scaled by
 *************************************************************************/
unsigned int readDial(unsigned int max)
{
    unsigned int value;

    //Sets the AD channel for the DIAL
    SetChanADC(ADC_DIAL_READ);

    //Begin convertion
    ConvertADC();
    while(BusyADC());
    value = ReadADC();

    //Scale the value to the maximum (by multiplying and then dividing by 1024)
    //The 1024 division creates a value from 0-1 from the ADC
    value = DIV_1024(value * max);

    return value;
}

/*! **********************************************************************
 * Function: userEmpty(void)
 *
 * Include: User_Interface.h
 *
 * Description: returns non-zero if the user interface buffer is empty (i.e.
 *              no user input has been detected)
 *
 * Arguments: None
 *
 * Returns: if the user input buffer is empty
 *************************************************************************/
char userEmpty(void)
{
    return empty(receive);
}

/*! **********************************************************************
 * Function: userPop(void)
 *
 * Include: User_Interface.h
 *
 * Description: pops a character from the user interface receive buffer
 *
 * Arguments: None
 *
 * Returns: a character poped from the user Interface buffer
 *************************************************************************/
extern char userPop(void)
{
    char c;
    c = pop(receive);
    return c;
}

/*! **********************************************************************
 * Function: userPeek(void)
 *
 * Include: User_Interface.h
 *
 * Description: returns a character in the user_Interface buffer without
 *              removing it from the buffer
 *
 * Arguments: None
 *
 * Returns: a character in the user interface buffer
 *************************************************************************/
extern char userPeek(void)
{
    return peek(receive);
}