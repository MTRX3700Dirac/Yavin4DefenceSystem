/*
 * File:   ADC.c
 * Author: Grant
 *
 * Description: Contains all the functionality for the Pan Tilt module
 *
 * Created on 16 September 2014, 6:47 PM
 */

#include "Common.h"
#include <pwm.h>
#include <timers.h>

typedef struct
{
    signed int AzimuthDelay;
    signed int InclinationDelay;
} Delay;

//Define the PWM output pins
#define AZ_PWM_PIN PORTCbits.RC0
#define IN_PWM_PIN PORTCbits.RC1

//Interrupt Latency
#define LATENCY 340
#define PWM_PERIOD 20000 //The period for 50Hz at 1MHz
#define PWM_HALF_PERIOD 10000 //Half the period for 50Hz at 1MHz
//#define ARC_RANGE 94 //Max arc of servos
//#define HALF_RANGE 47   //Half the range of the servos

#define SERVO_INIT() TRISCbits.RC0 = 0; TRISCbits.RC1 = 0; PORTCbits.RC0 = 0; PORTCbits.RC1 = 0

void validate(unsigned int *delay);
Delay direction2Delay(DirectionState dir);
Delay direction2Delay(DirectionState dir);

//Static calibration offset
static Direction calibration_offset = { 0, 3 };
static Direction arcRange = { 94, 103 };
static Delay global_delay;

//Static Max/Min
static signed char azimuth_angle_max;
static signed char azimuth_angle_min;
static signed char elevation_angle_max;
static signed char elevation_angle_min;

//Static Current direction
static Direction current_direction;

/*! **********************************************************************
 * Function: config(void)
 *
 * Include: PanTilt.h
 *
 * Description: Configures the Pan Tilt mechanism for operation
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configureBase(void)
{
    unsigned char config;

    //Set the initial servo PWM's to zeros
    DirectionState zero = { 0, 0 };
    global_delay = direction2Delay(zero);
    
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

    RCONbits.IPEN = 1;
    
    SERVO_INIT();

    config = T1_16BIT_RW & T1_PS_1_1 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF & T1_SOURCE_INT;

    OpenTimer1(config);

    //Timer1 source for CCP1, and timer3 source for CCP2
    SetTmrCCPSrc(T1_CCP1_T3_CCP2);

    config = COM_INT_ON & COM_UNCHG_MATCH;

    OpenCompare1(config, PWM_PERIOD);

    azimuth_angle_max = 45;
    azimuth_angle_min = -45;
    elevation_angle_max = 45;
    elevation_angle_min = -45;
}

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
void move(Direction destination)
{
    global_delay = direction2Delay(destination);
    current_direction = destination;
}

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
Direction getDir(void)
{
    return current_direction;
}

/*! **********************************************************************
 * Function: getMaxAzimuthAngle
 *
 * Include: PanTilt.h
 *
 * Description: returns the maximum angle of the azimuth servo
 *
 * Arguments: None
 *
 * Returns: A char with the maximum azimuth angle.
 *************************************************************************/
char getMaxAzimuthAngle(void)
{
    return azimuth_angle_max;
}

/*! **********************************************************************
 * Function: getMinAzimuthAngle
 *
 * Include: PanTilt.h
 *
 * Description: returns the minimum angle of the azimuth servo
 *
 * Arguments: None
 *
 * Returns: A char with the minimum azimuth angle.
 *************************************************************************/
char getMinAzimuthAngle(void)
{
    return azimuth_angle_min;
}

/*! **********************************************************************
 * Function: getMaxElevationAngle
 *
 * Include: PanTilt.h
 *
 * Description: returns the maximum angle of the elevation servo
 *
 * Arguments: None
 *
 * Returns: A char with the maximum elevation angle.
 *************************************************************************/
char getMaxElevationAngle(void)
{
    return elevation_angle_max;
}

/*! **********************************************************************
 * Function: getMinElevationAngle
 *
 * Include: PanTilt.h
 *
 * Description: returns the minimum angle of the elevation servo
 *
 * Arguments: None
 *
 * Returns: A char with the minimum elevation angle.
 *************************************************************************/
char getMinElevationAngle(void)
{
    return elevation_angle_min;
}

/*! **********************************************************************
 * Function: setMaxAzimuthAngle
 *
 * Include: PanTilt.h
 *
 * Description: sets the maximum angle of the azimuth servo
 *
 * Arguments: The maximum angle (as char) to set for the azimuth servo
 *
 * Returns: None.
 *************************************************************************/
void setMaxAzimuthAngle(char p_angle)
{
    azimuth_angle_max = p_angle;
}
/*! **********************************************************************
 * Function: setMinAzimuthAngle
 *
 * Include: PanTilt.h
 *
 * Description: sets the minimum angle of the azimuth servo
 *
 * Arguments: The minimum angle (as char) to set for the azimuth servo
 *
 * Returns: None.
 *************************************************************************/
void setMinAzimuthAngle(char p_angle)
{
    azimuth_angle_min = p_angle;
}
/*! **********************************************************************
 * Function: setMaxElevationAngle
 *
 * Include: PanTilt.h
 *
 * Description: sets the maximum angle of the elevation servo
 *
 * Arguments: The maximum angle (as char) to set for the elevation servo
 *
 * Returns: None.
 *************************************************************************/
void setMaxElevationAngle(char p_angle)
{
    elevation_angle_max = p_angle;
}

/*! **********************************************************************
 * Function: setMinElevationAngle
 *
 * Include: PanTilt.h
 *
 * Description: sets the minimum angle of the elevation servo
 *
 * Arguments: The minimum angle (as char) to set for the elevation servo
 *
 * Returns: None.
 *************************************************************************/
void setMinElevationAngle(char p_angle)
{
    elevation_angle_min = p_angle;
}

/*! **********************************************************************
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
Direction rawDir(void)
{
    
}

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
void panTiltISR(void)
{
    unsigned int timer_value;
    static Delay current_delay;
    unsigned char i = 0;

    if (CCP1_INT)
    {
        timer_value = ReadTimer1();

        if (timer_value > PWM_PERIOD)
        {
            IN_PWM_PIN = 1;
            WriteTimer1(0);     //Clear timer2
            current_delay = global_delay;   //update the static delay
            OpenCompare1(COM_INT_ON & COM_UNCHG_MATCH, current_delay.InclinationDelay);
        }
        else if (timer_value > current_delay.AzimuthDelay)
        {
            AZ_PWM_PIN = 0;
            OpenCompare1(COM_INT_ON & COM_UNCHG_MATCH, PWM_PERIOD);
        }
        else if (timer_value > PWM_HALF_PERIOD)
        {
            AZ_PWM_PIN = 1;
            OpenCompare1(COM_INT_ON & COM_UNCHG_MATCH, current_delay.AzimuthDelay);
        }
        else if (timer_value > current_delay.InclinationDelay)
        {
            IN_PWM_PIN = 0;
            OpenCompare1(COM_INT_ON & COM_UNCHG_MATCH, PWM_HALF_PERIOD);
        }

        PIR1bits.CCP1IF = 0;
    }
}

/*! **********************************************************************
 * Function: direction2Delay(DirectionState dir)
 *
 * Include:
 *
 * Description: Converts an azimuth and inclination direction into a pwm period
 *
 * Arguments: dir - Locally defined struct containing the desired Azimuth
 *                          and Inclination
 *
 * Returns: Delay - The required PDM delay to move the servos to the given direction
 *
 * Remark: This function relies on the ARC_RANGE macro being set correctly. This
 *         should hold the value of the maximum angle that the servos can be commanded
 *************************************************************************/
DirectionState delay2Direction(Delay dly)
{
    DirectionState ret;

    //ret.azimuth = ((dly.AzimuthDelay - PWM_HALF_PERIOD - 1000) * (long int)arcRange.azimuth + 500) / 1000 - DIV_2(arcRange.azimuth) - calibration_offset.azimuth;
    //ret.inclination = ((dly.InclinationDelay + LATENCY - 1000) * (long int)arcRange.inclination + 500) / 1000 - DIV_2(arcRange.inclination) - calibration_offset.inclination;

    return ret;
}

/*! **********************************************************************
 * Function: direction2Delay(DirectionState dir)
 *
 * Include:
 *
 * Description: Converts an azimuth and inclination direction into a pwm period
 *
 * Arguments: dir - Locally defined struct containing the desired Azimuth
 *                          and Inclination
 *
 * Returns: Delay - The required PDM delay to move the servos to the given direction
 *
 * Remark: This function relies on the ARC_RANGE macro being set correctly. This
 *         should hold the value of the maximum angle that the servos can be commanded
 *************************************************************************/
Delay direction2Delay(DirectionState dir)
{
    Delay result;
    unsigned int az, inc;

    az = 1000 + (dir.azimuth + DIV_2(arcRange.azimuth) + calibration_offset.azimuth) * (long int)1000 / arcRange.azimuth;
    inc = 1000 + (-dir.inclination + DIV_2(arcRange.inclination) + calibration_offset.inclination) * (long int)1000 / arcRange.inclination;

    validate(&az);
    validate(&inc);

    result.AzimuthDelay = az + PWM_HALF_PERIOD;
    result.InclinationDelay = inc - LATENCY;

    return result;
}


/*! **********************************************************************
 * Function: validate(unsigned int *delaay)
 *
 * Include:
 *
 * Description: Limits the duration of the PDM to between 1000us and 2000us
 *
 * Arguments: delay - a pointer to the delay variable
 *
 * Returns: None
 *************************************************************************/
void validate(unsigned int *delay)
{
    if (*delay < 1000)
    {
        *delay = 1000;
    }
    if (*delay > 2000)
    {
        *delay = 2000;
    }
}