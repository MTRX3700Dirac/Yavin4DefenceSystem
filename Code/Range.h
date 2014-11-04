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

/*============================================================================*/
//External declarations of the public access functions
/*============================================================================*/

/*! **********************************************************************
 * Function: configureRange(void)
 *
 * Include: Range.h
 *
 * Description: Configures the Range module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void configureRange(void);

/*! **********************************************************************
 * Function: configureAD(void)
 *
 * Include: Range.h
 *
 * Description: Configures the ADC,
 * In ADCON1, we set right-justified mode, and select AN0 as the input channel.
 * In ADCON0, we set a sample rate of Fosc/8, select AN0, and enable the ADC.
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void configureAD(void);

/*! **********************************************************************
 * Function: range(void)
 *
 * Include: Range.h
 *
 * @brief Samples the range
 *
 * Description: Takes a number of samples of the ultrasonic sensor at a specified
 *              rate. Continues to sample the IR sensor at a different rate while
 *              sampling the ultrasonic. Then combines the ranges and sets the
 *              target state
 *
 * Arguments: None
 *
 * Returns: the range to the target in mm
 *************************************************************************/
extern unsigned int range(void);

/*! **********************************************************************
 * Function: getLastRange(void)
 *
 * Include: Range.h
 *
 * @brief Samples the range
 *
 * Description: Returns the last range sample, so the data can be used without
 *              re-sampling the range finding sensors
 *
 * Arguments: None
 *
 * Returns: the last Range sample data
 *************************************************************************/
extern unsigned int lastRange(void);

/*! **********************************************************************
 * Function: rangeISR(void)
 *
 * Include: range.h
 *
 * Description: Called when an range related interrupt is fired, acts
 *              as the service routine for the rangefinding module.
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void rangeISR(void);

/*! **********************************************************************
 * Function: calibrateRange(unsigned int reference)
 *
 * Include:
 *
 * Description: Calibrates the range of both the IR and ultrasonic sensors
 *              based on a given range.
 *
 * Arguments: reference - The distance in mm to calibrate the current
 *                        measurements from
 *
 * Returns: None
 *************************************************************************/
extern void calibrateRange(signed int distance);

/*! **********************************************************************
 * Function: rawRangeIR(void)
 *
 * Include: Range.h
 *
 * Description: Returns the last IR range reading
 *
 * Arguments: None
 *
 * Returns: the range in mm
 *************************************************************************/
extern unsigned int rawRangeIR(void);

/*! **********************************************************************
 * Function: rawRangeUS(void)
 *
 * Include: Range.h
 *
 * Description: Returns the last US range reading
 *
 * Arguments: None
 *
 * Returns: the range in mm
 *************************************************************************/
extern unsigned int rawRangeUS(void);


/*! **********************************************************************
 * Function: getTargetState(void)
 *
 * Include: Range.h
 *
 * Description: Returns the target state from the last range reading. E.g.
 *              Good track, or direction not quite correct as US returned,
 *              but IR didn't and was within IR range etc.
 *
 * Arguments: None
 *
 * Returns: the target state
 *************************************************************************/
extern TargetState getTargetState(void);

/*! **********************************************************************
 * Function: readTargetState(void)
 *
 * Include: Range.h
 *
 * Description: Does the same thing as getTargetState, but actually performs
 *              a range() read
 *
 * Arguments: None
 *
 * Returns: the target state
 *************************************************************************/
extern TargetState readTargetState(void);

/*! **********************************************************************
 * Function: setMaxRange()
 *
 * Include: Range.h
 *
 * Description: Sets the maximum range of the device
 *
 * Arguments: range - The max range to set in mm
 *
 * Returns: N/A
 *************************************************************************/
extern void setMaxRange(int range);

/*! **********************************************************************
 * Function: setMinRange()
 *
 * Include: Range.h
 *
 * Description: Sets the minimum range of the device
 *
 * Arguments: range - The max range to set in mm
 *
 * Returns: N/A
 *************************************************************************/
extern void setMinRange(int range);

/*! **********************************************************************
 * Function: getMaxRange()
 *
 * Include: Range.h
 *
 * Description: Gets the maximum range of the device
 *
 * Arguments:
 *
 * Returns: The max range in mm
 *************************************************************************/
extern int getMaxRange(void);

/*! **********************************************************************
 * Function: getMinRange()
 *
 * Include: Range.h
 *
 * Description: Gets the minimum range of the device
 *
 * Arguments:
 *
 * Returns: The min range in mm
 *************************************************************************/
extern int getMinRange(void);

/*! **********************************************************************
 * Function: getUsSampleRate()
 *
 * Include: Range.h
 *
 * Description: Gets the sampling rate of the ultrasonic sensor
 *
 * Arguments:
 *
 * Returns: The sampling rate (In Hz)
 *************************************************************************/
extern char getUsSampleRate();

/*! **********************************************************************
 * Function: setUsSampleRate(char sampleRate)
 *
 * Include: Range.h
 *
 * Description: Sets the ultrasonic sampling rate
 *
 * Arguments: the sampling rate in Hz
 *
 * Returns: None
 *************************************************************************/
extern void setUsSampleRate(char samples);

/*! **********************************************************************
 * Function: getNumSamples()
 *
 * Include: Range.h
 *
 * Description: Gets the number of samples per range estimate
 *
 * Arguments: None
 *
 * Returns: The number of samples
 *************************************************************************/
extern char getNumSamples();

/*! **********************************************************************
 * Function: setNumSamples()
 *
 * Include: Range.h
 *
 * Description: sets the number of samples per range estimage
 *
 * Arguments: the number of samples
 *
 * Returns: None
 *************************************************************************/
extern void setNumSamples(char sampleRate);

#define RANGE_H
#endif