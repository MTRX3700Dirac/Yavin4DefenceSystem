/*
 * File:   User_Interface.c
 * Author: Grant
 *
 * Description: Contains all the functionality for the User_Interface module
 *
 * Created on 15 September 2014, 1:21 PM
 */

#include "Common.h"

struct user_state
{
    enum { ROOT, MODULE, FUNCTION } level;
    enum { AZIMUTH, ELEVATION, RANGE, TEMP, RAW, TRACK } module;
    enum { MIN, MAX, GOTO } function;
} InterfaceState;


/* **********************************************************************
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

/* **********************************************************************
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

/* **********************************************************************
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
    InterfaceState.module = InterfaceState.ROOT;
    InterfaceState.module = InterfaceState.TRACK;
}

/* **********************************************************************
 * Function: readDial(void)
 *
 * Include: ADC.h
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
