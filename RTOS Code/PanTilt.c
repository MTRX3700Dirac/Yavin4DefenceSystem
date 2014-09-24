/*
 * File:   ADC.c
 * Author: Grant
 *
 * Description: Contains all the functionality for the Pan Tilt module
 *
 * Created on 16 September 2014, 6:47 PM
 */
//#include <p18f4520.h>
#include "Common.h"

//Static calibration offset
static Direction calibration_offset = { 0, 0 };



/* **********************************************************************
 * Function: move(Direction destination)
 *
 * Include: PanTilt.h
 *
 * Description: Moves the pan tilt actuator to the specified destination
 *
 * Arguments: destionation - A struct containing the desired azimuth and inclination
 *
 * Returns: None
 *************************************************************************/
void move(Direction destination)
{
    
}

/* **********************************************************************
 * Function: getDir(void)
 *
 * Include: PanTilt.h
 *
 * Description: returns the current position of the pan tilt mechanism
 *
 * Arguments: None
 *
 * Returns: A struct containing the azimuth and inclination
 *************************************************************************/
Direction getDir(void)
{
    
}

/* **********************************************************************
 * Function: calibratePanTilt(Direction reference)
 *
 * Include: PanTilt.h
 *
 * Description: Calibrates the pan tile mechanism so that any future reference
 *              to move to the reference value specified in the function call
 *              will move the pan tilt back to the current position.
 *
 * Arguments: reference - A struct containing the azimuth and inclinaion you
 *                        wish to define as this position.
 *
 * Returns: None
 *************************************************************************/
void calibratePanTilt(Direction reference)
{
    
}

/* **********************************************************************
 * Function: rawDir(void)
 *
 * Include: PanTilt.h
 *
 * Description: returns the current PanTile position without calibrating
 *
 * Arguments: None
 *
 * Returns: The position of the pan tilt without any calibration
 *************************************************************************/
Direction rawDir(void)
{
    
}

/* **********************************************************************
 * Function: panTiltISR(void)
 *
 * Include: PanTilt.h
 *
 * Description: Acts as the ISR for the PanTilt module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void panTiltISR(void)
{
    
}
