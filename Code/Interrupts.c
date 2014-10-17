/*
 * File:   Interrupts.c
 * Author: Grant
 *
 * Description: Contains the interrupt service routines for the system
 *
 * Created on 8 October 2014, 11:27 AM
 */

#include "Common.h"

//Any module that uses interrupts will need to be included heree:
#include "Tracking.h"
#include "Range.h"
#include "User_Interface.h"
#include "Serial.h"
#include "PanTilt.h"
#include "Temp.h"
#include "Menusystem.h"

//ISR prototypes
void lowISR(void);
void highISR(void);

/*! **********************************************************************
 * Function: highVector(void)
 *
 * Include:
 *
 * Description: Sends program control to the high priority ISR
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Remarks: This is an interrupt vector, placing a goto in the
 *          high priority interrupt table to call the high priority ISR
 *************************************************************************/
#pragma code highPriorityInterruptAddress=0x0008
void highVector(void)
{
    _asm GOTO highISR _endasm
}

/*! **********************************************************************
 * Function: lowVector(void)
 *
 * Include:
 *
 * Description: Sends program control to the low priority ISR
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Remarks: This is an interrupt vector, placing a goto in the
 *          low priority interrupt table to call the low priority ISR
 *************************************************************************/
#pragma code lowPriorityInterruptAddress=0x0018
void lowVector(void)
{
    _asm GOTO lowISR _endasm
}

/*! **********************************************************************
 * Function: lowISR(void)
 *
 * Include: Interrupt_head.h
 *
 * Description: Interrupt Service Routine to check what condition initiated
 *              a low priority interrupt call, and perform the nessicary action
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
#pragma interruptlow lowISR
void lowISR(void)
{
    if (SERIAL_INT)
    {
        serialISR();
    }
    if (PAN_TILT_ISR)
    {
        panTiltISR();
    }
    if (RANGE_INT)
    {
        rangeISR();
    }
    if (USER_INT)
    {
        userISR();
    }
}

/*! **********************************************************************
 * Function: highISR(void)
 *
 * Include:
 *
 * Description: Interrupt Service Routine to check what condition initiated
 *              a high priority interrupt call, and perform the nessicary action
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
#pragma interrupt highISR
void highISR(void)
{
    if (PAN_TILT_ISR)
    {
        panTiltISR();
    }
    if (SERIAL_INT)
    {
        serialISR();
    }
    if (RANGE_INT)
    {
        rangeISR();
    }
    if (USER_INT)
    {
        userISR();
    }
}