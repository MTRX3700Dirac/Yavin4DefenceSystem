/*
 * File:   ultrasonic.c
 * Author: Grant
 *
 * Description: Contains all the functionality for the ultrasonic module
 *
 * Created on 15 September 2014, 11:27 AM
 */

#include "Common.h"
#include "Temp.h"

//(Approximate) speed of sound calculation macro
#define SPD_SND(T) (DIV_1024(T * (unsigned int)614) + 331)
#define IR_CONV(ad) ((unsigned long)237411 / (ad) - 65)

#define NUM_IR_READS 10 //The number of IR reads per measurement

//Hardware Related macros
#define INIT_PIN PORTBbits.RB0

//Static calibration offset
static signed int calibration_offset = 0;

//Flag for performing an ultrasonic measurment
volatile static char measuringUS = 0;

//Static variable to store the range
static unsigned int lastRange = 0;

//Calibration offsets
signed int calibration_offset_IR = 0;
signed int calibration_offset_US = 0;

//Private function prototypes:
void beginUS(void);
unsigned int rangeIR(void);
unsigned int rangeUS(unsigned char temp);
//unsigned int speed_sound(unsigned char temp);

unsigned int sampleIR(char numSamples);

/* **********************************************************************
 * Function: configureAD(void)
 *
 * Include: Range.h
 *
 * Description: Configures the ADC,
 * In ADCON1, we set right-justified mode, and select AN0 as the input channel.
 * In ADCON0, we set a sample rate of Fosc/64, select AN0, and enable the ADC.
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configureAD(void)
{
    int i = 0;
    TRISA = 0xFF;

    //Write the configuration values into the configuration registers
    ADCON1 = 0x8E;
    ADCON0 = 0x41;
    

    //Arbitrary wait period to allow the ADC to initialise
    for (i = 0; i < 1000; i++);
}

/* **********************************************************************
 * Function: beginUS(void)
 *
 * Include: ultrasonic.h
 *
 * Description: starts a scan on the ultrasonic sensor
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void beginUS(void)
{
    //Set the INIT_PIN high to begin ultrasonic 'read'
    INIT_PIN = 1;

    //Set the measuring flag
    measuringUS = 1;
}

/* **********************************************************************
 * Function: rangeUS(unsigned char temp)
 *
 * Include: ultrasonic.h
 *
 * Description: Returns the result of the ultrasonic read (zero if no target
 *              found). Will poll until measurement is complete.
 *
 * Arguments: tempx2 - 2x the temperature in deg Celsius
 *
 * Returns: Distance in mm (unsigned int)
 *************************************************************************/
unsigned int rangeUS(unsigned char temp)
{
    unsigned int range;
    //Continue to poll while measurement is still in progress
    while (measuringUS);

    //Perform calculation (ReadCapture in us, speed of sound in m/s->um)
    // um/1024 = ~mm
    range = DIV_1024(ReadCapture1() * SPD_SND(temp));
    //DIV_1024(ReadCapture1() * speed_sound(tempx2));
    
    return range;
}

/* **********************************************************************
 * Function: rangeISR(void)
 *
 * Include: ultrasonic.h
 *
 * Description: Called when an range related interrupt is fired, acts
 *              as the service routine for the rangefinding module.
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void rangeISR(void)
{
    if (CCP1_INT)
    {   //Checks if the CCP1 module fired the interrupt
        measuringUS = 0;
    }
    else if (CCP2_INT)
    {   //Checks if the CCP2 module fired the interrupt

    }
}

/* **********************************************************************
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
void calibrateRange(unsigned int reference)
{
    unsigned char temp;
    unsigned int range_US, range_IR, range;

    //Begin the Ultrasonic measurement
    beginUS();

    //Read the temperature
    temp = readTemp();

    //Measure the IR range
    range_IR = rangeIR();

    //Read the result from the Ultrasonc sensor
    range_US = rangeUS(temp);

    if (range_US)
    {
        calibration_offset_US = reference - range_US;
    }
    if (range_IR)
    {
        calibration_offset_IR = reference - range_IR;
    }
}

/* **********************************************************************
 * Function: speed_sound(unsigned char tempx2)
 *
 * Include:
 *
 * Description: Returns the calibration offset to calculate the raw data
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
unsigned int rawRange(void)
{
    return lastRange;
}

/* **********************************************************************
 * Function: range()
 *
 * Include:
 *
 * Description: Uses the IR and Ultrasonic sensors to find the range
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
unsigned int range(void)
{
    unsigned char temp;
    unsigned int range_US, range_IR, range;

    //Begin the Ultrasonic measurement
    beginUS();

    //Read the temperature
    temp = readTemp();

    //Measure the IR range
    range_IR = rangeIR();

    //Read the result from the Ultrasonc sensor
    range_US = rangeUS(temp);

    //Check which sensor(s) have observed a target
    if (range_US && range_IR)
    {
        //Calibrate the sensors
        range_US += calibration_offset_US;
        range_IR += calibration_offset_IR;

        //Average the ultrasonic and IR ranges
        range = DIV_2(range_US + range_IR);
    }
    else if (range_US)
    {
        //Calibrate the ultrasonic range
        range_US += calibration_offset_US;
        
        range = range_US;
    }
    else if (range_IR)
    {
        //Calibrate the IR range
        range_IR += calibration_offset_IR;
        
        range = range_IR;
    }
    else
    {
        range = 0;
    }

    lastRange = range;
    return range;
}

/* **********************************************************************
 * Function: rangeIR(void)
 *
 * Include: 
 *
 * Description: Reads the range from the IR Sensor
 *
 * Arguments: None
 *
 * Returns: Range (in mm) as an unsigned int.
 *
 * Remark: Returns 0 if there is no target found
 *************************************************************************/
unsigned int rangeIR(void)
{
    unsigned int ad_result;
    unsigned int range;

    ad_result = sampleIR(10);

    //Return 0 if there is no target detected
    if (ad_result < 100) return 0;

    //Convert voltage (0-5v) into range (mm)
    range = IR_CONV(ad_result);

    return range + calibration_offset_IR;
}

/* **********************************************************************
 * Function: rangeIR(void)
 *
 * Include:
 *
 * Description: Reads the range from the IR Sensor
 *
 * Arguments: None
 *
 * Returns: Range (in mm) as an unsigned int.
 *
 * Remark: Returns 0 if there is no target found
 *************************************************************************/
unsigned int sampleIR(char numSamples)
{
    unsigned long int sum = 0;
    unsigned int temp;
    char i = 0;
    
    //Multiplex onto the IR sensor
    SetChanADC(ADC_IR_READ);

    //Perform numSamples samples
    for (i = 0; i < numSamples; i++)
    {
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_NOT_DONE);
        temp = ADRES >> 6;
        sum += temp;
    }

    //Average all samples taken
    temp = sum / (unsigned int)numSamples;
    return temp;
}