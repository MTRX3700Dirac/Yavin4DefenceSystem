/*! **************************************************************************** 
 * File:   Temp.h
 * Author: Grant
 *
 * Description:
 * Contains all the functionality and variables for the temp module. All unnecessary
 * functions and variables should be shielded from the external program, and interfaced
 * with accessor and mutator functions
 *
 * Contains:
 *      -Configure function
 *      -Read temperature functions
 *      -Get (last) temperature (read) function
 *      -Calibrate Temperature function
 *
 * Created on 17 September 2014, 2:16 PM
 ******************************************************************************/

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef TEMP_H

/*============================================================================*/
//External public access function prototypes
/*============================================================================*/

/*! **********************************************************************
 * Function: configureTemp(void)
 *
 * Include: Temp
 *
 * Description: Configures the temperature module for use
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void configureTemp(void);

/*! **********************************************************************
 * Function: rawTemp(void)
 *
 * Include: Temp.h
 *
 * Description: Returns the raw (uncalibrated temperature)
 *
 * Arguments: None
 *
 * Returns: Temp (in deg celsius) as an unsigned char
 *************************************************************************/
extern unsigned char rawTemp(void);

/*! **********************************************************************
 * Function: readTemp(void)
 *
 * Include: Temp.h
 *
 * Description: Reads the temperature from the TEMP sensor
 *
 * Arguments: None
 *
 * Returns: Temp (in deg celsius) as an unsigned char
 *************************************************************************/
extern unsigned char readTemp(void);

/*! **********************************************************************
 * Function: readTempx2(void)
 *
 * Include: Temp.h
 *
 * Description: Reads the temperature from the Temp sensor
 *
 * Arguments: None
 *
 * Returns: temp x 2 (in deg celsius) as an unsigned char
 *
 * @todo Test and debug this function
 *************************************************************************/
extern unsigned char readTempx2(void);

/*! **********************************************************************
 * Function: calibrateTemp(unsigned char reference)
 *
 * Include: Temp.h
 *
 * Description: calibrates the temperature sensor by updating the calibration
 *              offset variable
 *
 * Arguments: reference - Reference temperature in deg C
 *
 * Returns: None
 *
 * Note: This function does not perform a temperature read, but uses the last
 *       value. This is because the readTemp function automatically calibrate.
 *************************************************************************/
extern void calibrateTemp(unsigned char reference);

/*! **********************************************************************
 * Function: calibrationTemp(unsigned char reference)
 *
 * Include: Temp.h
 *
 * Description: calibrates the temperature sensor by updating the calibration
 *              offset variable
 *
 * Arguments: reference - Reference temperature in deg C
 *
 * Returns: None
 *************************************************************************/
extern unsigned char getTemp(void);

#define TEMP_H
#endif