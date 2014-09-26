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
#define SPD_SND(T) (DIV_128(332 * (unsigned int)sqrt(16384 + T * (unsigned int)60)))

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
unsigned int speed_sound(unsigned char temp);

/* **********************************************************************
 * Function: configureRange(void)
 *
 * Include: ultrasonic.h
 *
 * Description: Configures the ultrasonic and IR sensors and everything required to
 *              Use them
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configureRange(void)
{
    //Configure Stuff



    //Open Capture 1 set for every rising edge with interrupts on the rising edge
    OpenCapture1(CAP_EVERY_RISE_EDGE & CAPTURE_INT_ON);
    CP1_TRIS = 1;         //Set TRISC<2> input
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
 * Function: speed_sound(unsigned char tempx2)
 *
 * Include: 
 *
 * Description: Calculates the speed of sound from the given temperature
 *              and the following equation: V = 331.6(1+T/273.15)^0.5
 *              where V is in m/s and T is in deg C
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Remark: The calculation is performed in an unusual way for efficiency.
 *         The argument in the sqrt is multiplied by 256 to avoid loss of
 *         Resolution when dividing without the need for floating point
 *         operations. 256 was chosen as it is 16^2, so a simple bit-shift
 *         outside the sqrt will return the correct value. An even faster
 *         (Yet less accurate version is also included). If this version is
 *         used, then changing the argument from tempx2 to temp will remove
 *         the necessity for the DIV_2(). (There is also a macro for the latter
 *         Implementation, SPD_SND() which would be advisable to use).
 *************************************************************************/
unsigned int speed_sound(unsigned char tempx2)
{
    unsigned int velocity;

    velocity = 332 * DIV_16((unsigned int)sqrt(256 + 256 * tempx2 / 546));
    //velocity = 332 * DIV_16(sqrt(256 + DIV_2(tempx2)));

    return velocity;
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
    int ad_result;
    unsigned int range;

    //Sets the ADC channel to IR read
    SetChanADC(ADC_IR_READ);

    //Perform convertion
    ConvertADC();
    while(BusyADC());
    ad_result = ReadADC();

    //Presumably convert to range in mm

    return range;
}