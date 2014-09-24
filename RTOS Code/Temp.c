/*
 * File:   Temp.c
 * Author: Grant
 *
 * Description: Contains all the functionality for the Temp module
 *
 * Created on 7 September 2014, 4:12 PM
 */

#include "Common.h"

//Static variables
static signed char calibration_offset = 0;
static unsigned char lastTempx2;

/* **********************************************************************
 * Function: readTempx2(void)
 *
 * Include: ADC.h
 *
 * Description: Reads the temperature from the Temp sensor
 *
 * Arguments: None
 *
 * Returns: temp x 2 (in deg celsius) as an unsigned char
 *************************************************************************/
unsigned char readTempx2(void)
{
    int ad_result;
    unsigned char tempx2;

    //Sets the ADC channel to read the temperature
    SetChanADC(ADC_TEMP_READ);

    //Performs the conversion
    ConvertADC();
    while(BusyADC());
    ad_result = ReadADC();

    //10mV per deg C, which 0V at 0deg, with the ADC res ~5mV
    tempx2 = ad_result;

    lastTempx2 = tempx2;
    
    return tempx2 + calibration_offset;
}

/* **********************************************************************
 * Function: readTemp(void)
 *
 * Include: ADC.h
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

/* **********************************************************************
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

/* **********************************************************************
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
void calibrateTemp(unsigned char reference)
{
    calibration_offset = reference - DIV_2(lastTempx2);
}