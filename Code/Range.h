/*! ****************************************************************************
 * File:   Range.h
 * Author: Grant
 *
 * Description: 
 * Contains the public interface for the ultrasonic module. This file contains
 * all the external declarations, macros and global variables for using and
 * Interfacing with the Range module.
 *
 * Created on 15 September 2014, 11:24 AM
 ******************************************************************************/

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef RANGE_H

//Ultrasonic module interrupt macro
#define RANGE_INT CCP1_INT | TMR1_INT

//External declarations of the public access functions
extern void configureRange(void);
extern void configureAD(void);
extern unsigned int range(void);
extern void rangeISR(void);
extern void calibrateRange(signed int distance);
extern signed int rawRange(void);

extern TargetState getTargetState(void);
extern TargetState readTargetState(void);

extern unsigned int rangeIR(void);
extern unsigned int rangeUltrasonic(void);

#define RANGE_H
#endif