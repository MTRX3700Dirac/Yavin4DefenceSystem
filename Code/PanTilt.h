/*! ****************************************************************************
 * File:   PanTilt.h
 * Author: Grant
 *
 * Description:
 * This file contains the public interface for the PanTile module
 *
 * Created on 16 September 2014, 6:33 PM
 ******************************************************************************/

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef PANTILT_H

//True if Pan ISR concerns pan tilt module
#define PAN_TILT_ISR    CCP2_INT

/*============================================================================*/
//External declarations of public access functions
/*============================================================================*/

/*! **********************************************************************
 * Function: configureBase(void)
 *
 * Include: PanTilt.h
 *
 * Description: Configures the Pan Tilt mechanism for operation
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void configureBase(void);

/*! **********************************************************************
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
extern void move(Direction destination);

/*! **********************************************************************
 * Function: increment(Direction difference)
 *
 * Include: PanTilt.h
 *
 * Description: Moves the pan tilt actuator to the specified destination
 *
 * Arguments: destionation - A struct containing the desired azimuth and inclination
 *
 * Returns: None
 *************************************************************************/
extern void increment(Direction difference);

/*! **********************************************************************
 * Function: incrementFine(Direction difference)
 *
 * Include: PanTilt.h
 *
 * Description: Moves the pan tilt actuator to the specified (Relative) destination
 *
 * Arguments: destionation - A struct containing the desired azimuth and inclination
 *
 * Returns: None
 *************************************************************************/
extern void incrementFine(Direction difference);

/*! **********************************************************************
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
extern Direction getDir(void);

/*! **********************************************************************
 * Function: calibratePanTilt(Direction reference)
 *
 * Include: PanTilt.h
 *
 * Description: Calibrates the pan tile mechanism offset so that any future reference
 *              to move to the reference value specified in the function call
 *              will move the pan tilt back to the current position.
 *
 * Arguments: reference - A struct containing the azimuth and inclinaion you
 *                        wish to define as this position.
 *
 * Returns: None
 *************************************************************************/
extern void calibratePanTilt(Direction reference);

/*! **********************************************************************
 * Function: calibratePanTiltRange(Direction reference)
 *
 * Include: PanTilt.h
 *
 * Description: Calibrates the pan tile mechanism's range so that any future reference
 *              to move to the reference value specified in the function call
 *              will move the pan tilt back to the current position.
 *
 * Arguments: reference - A struct containing the azimuth and inclinaion you
 *                        wish to define as this position.
 *
 * Returns: None
 *************************************************************************/
extern void calibratePanTiltRange(Direction reference);

/*! **********************************************************************
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
extern Direction rawDir(void);

/*! **********************************************************************
 * Function: updated(void)
 *
 * Include: PanTilt.h
 *
 * Description: returns true if the last move or increment or incrementFine
 *              function has taken effect. The new direction is only loaded
 *              in at the end of the PDM, so it could take up to 0.02 seconds
 *              for the change to take effect.
 *
 * Arguments: delay - a pointer to the delay variable
 *
 * Returns: None
 *************************************************************************/
extern char updated(void);

/*! **********************************************************************
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
extern void panTiltISR(void);

/*! **********************************************************************
 * Function: getMaxAzimuthAngle(void)
 *
 * Include: PanTilt.h
 *
 * Description: returns the maximum angle of the azimuth servo
 *
 * Arguments: None
 *
 * Returns: A char with the maximum azimuth angle.
 *************************************************************************/
extern char getMaxAzimuthAngle(void);

/*! **********************************************************************
 * Function: getMinAzimuthAngle(void)
 *
 * Include: PanTilt.h
 *
 * Description: returns the minimum angle of the azimuth servo
 *
 * Arguments: None
 *
 * Returns: A char with the minimum azimuth angle.
 *************************************************************************/
extern char getMinAzimuthAngle(void);

/*! **********************************************************************
 * Function: getMaxElevationAngle(void)
 *
 * Include: PanTilt.h
 *
 * Description: returns the maximum angle of the elevation servo
 *
 * Arguments: None
 *
 * Returns: A char with the maximum elevation angle.
 *************************************************************************/
extern char getMaxElevationAngle(void);

/*! **********************************************************************
 * Function: getMinElevationAngle(void)
 *
 * Include: PanTilt.h
 *
 * Description: returns the minimum angle of the elevation servo
 *
 * Arguments: None
 *
 * Returns: A char with the minimum elevation angle.
 *************************************************************************/
extern char getMinElevationAngle(void);


/*! **********************************************************************
 * Function: setMaxAzimuthAngle(void)
 *
 * Include: PanTilt.h
 *
 * Description: sets the maximum angle of the azimuth servo
 *
 * Arguments: The maximum angle (as char) to set for the azimuth servo
 *
 * Returns: None.
 *************************************************************************/
extern void setMaxAzimuthAngle(char p_angle);

/*! **********************************************************************
 * Function: setMinAzimuthAngle(void)
 *
 * Include: PanTilt.h
 *
 * Description: sets the minimum angle of the azimuth servo
 *
 * Arguments: The minimum angle (as char) to set for the azimuth servo
 *
 * Returns: None.
 *************************************************************************/
extern void setMinAzimuthAngle(char p_angle);

/*! **********************************************************************
 * Function: setMaxElevationAngle(void)
 *
 * Include: PanTilt.h
 *
 * Description: sets the maximum angle of the elevation servo
 *
 * Arguments: The maximum angle (as char) to set for the elevation servo
 *
 * Returns: None.
 *************************************************************************/
extern void setMaxElevationAngle(char p_angle);

/*! **********************************************************************
 * Function: setMinElevationAngle(void)
 *
 * Include: PanTilt.h
 *
 * Description: sets the minimum angle of the elevation servo
 *
 * Arguments: The minimum angle (as char) to set for the elevation servo
 *
 * Returns: None.
 *************************************************************************/
extern void setMinElevationAngle(char p_angle);

#define PANTILT_H
#endif