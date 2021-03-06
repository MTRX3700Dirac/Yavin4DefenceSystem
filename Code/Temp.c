/*! ****************************************************************************
 * File:   Temp.c
 * Author: Grant
 *
 * Description:
 * Contains all the functionality for the Temp module.
 *
 * Duties:
 *      -Samples the temperature sensor
 *      -Stores the last temperature value
 *      -Calibrates the temperature sensor
 *
 * Functions:
 * 
 *
 * Created on 7 September 2014, 4:12 PM
 ******************************************************************************/

#include "Common.h"
#include "Range.h" //Access to the configureAD() function

//Static variables
static signed char calibration_offset = 0;
static unsigned char lastTempx2;

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
void configureTemp(void)
{
    configureAD();
}

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
unsigned char readTempx2(void)
{
    unsigned char tempx2;

    char mod;
    int tempRaw;
    int tempmV;
    char offset = -20; //0mV at 2 degrees??

    //Sets the ADC channel to read the temperature to channel 1
    ADCON0 = ADC_TEMP_READ;

    ADCON0bits.GO = 1;
    while (ADCON0bits.GO_NOT_DONE == 1);
    tempRaw = ADRES;
    tempmV = tempRaw * 4.88 + offset; //each incrememnt of ADRES is 4.88mV

    // Store double to keep accuracy
    tempmV = 2*tempmV;
    // Round last digit
    mod = tempmV % 10;
    if (mod >= 5) tempmV = tempmV + (10 - mod);
    lastTempx2 = tempx2 =tempmV/10;
    
    return tempx2 + calibration_offset;
}

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
unsigned char readTemp(void)
{
    unsigned char temp;

    //Read the temperature from the x2 function
    temp = readTempx2();

    //Divide the temp by two and return the result
    return DIV_2(temp);
}

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
unsigned char rawTemp(void)
{
    return DIV_2(lastTempx2);
}

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
void calibrateTemp(unsigned char reference)
{
    calibration_offset = 2 * (reference - DIV_2(lastTempx2));
}

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
unsigned char getTemp(void)
{
    return DIV_2(lastTempx2);
}