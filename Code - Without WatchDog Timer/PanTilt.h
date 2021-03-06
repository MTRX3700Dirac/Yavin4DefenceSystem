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

//External declarations of public access functions
extern void configureBase(void);
extern void move(Direction destination);
extern void increment(Direction difference);
extern void incrementFine(Direction difference);
extern Direction getDir(void);
extern void calibratePanTilt(Direction reference);
extern void calibratePanTiltRange(Direction reference);
extern Direction rawDir(void);
extern char updated(void);
extern void panTiltISR(void);

extern char getMaxAzimuthAngle(void);
extern char getMinAzimuthAngle(void);
extern char getMaxElevationAngle(void);
extern char getMinElevationAngle(void);

extern void setMaxAzimuthAngle(char p_angle);
extern void setMinAzimuthAngle(char p_angle);
extern void setMaxElevationAngle(char p_angle);
extern void setMinElevationAngle(char p_angle);

#define PANTILT_H
#endif