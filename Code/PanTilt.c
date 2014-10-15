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

#ifdef MNML     //Using minimal board, or piddem - Clock speeds differ by x4
#define DUTY_CYCLE_TIME 2500
#define PWM_PERIOD 50000 //The period for 50Hz at 2.5MHz
#define PWM_HALF_PERIOD 25000 //Half the period for 50Hz at 1MHz
#else
#define DUTY_CYCLE_TIME 1000
#define PWM_PERIOD 20000 //The period for 50Hz at 2.5MHz
#define PWM_HALF_PERIOD 10000 //Half the period for 50Hz at 1MHz
#endif

//Interrupt Latency
#define LATENCY 340

//#define ARC_RANGE 94 //Max arc of servos
//#define HALF_RANGE 47   //Half the range of the servos

#define SERVO_INIT() TRISCbits.RC0 = 0; TRISCbits.RC1 = 0; PORTCbits.RC0 = 0; PORTCbits.RC1 = 0

void validate(unsigned int *delay);
Direction delay2Direction(Delay dly);
Delay direction2Delay(Direction dir);

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
static volatile char changed = 0;

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
    Direction zero = { 0, 0 };
    global_delay = direction2Delay(zero);
    
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

    RCONbits.IPEN = 1;
    
    SERVO_INIT();

    config = T3_16BIT_RW & T3_PS_1_1& T3_SYNC_EXT_OFF & T3_SOURCE_INT;

    OpenTimer3(config);

    //Timer1 source for CCP1, and timer3 source for CCP2
    SetTmrCCPSrc(T1_CCP1_T3_CCP2);

    config = COM_INT_ON & COM_UNCHG_MATCH;

    OpenCompare2(config, PWM_PERIOD);

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

    //Update the current_direction
    current_direction = delay2Direction(global_delay);
}

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
void increment(Direction difference)
{
//    global_delay.AzimuthDelay += difference.azimuth * DUTY_CYCLE_TIME / arcRange.azimuth;
//    global_delay.InclinationDelay += difference.inclination * DUTY_CYCLE_TIME / arcRange.inclination;
//
//    //Ensure that the delays are still within the max and min duty cycles
//    validate(&(global_delay.AzimuthDelay));
//    validate(&(global_delay.InclinationDelay));
//
//    //Update the current_direction
//    current_direction = delay2Direction(global_delay);
    current_direction.azimuth += difference.azimuth;
    current_direction.inclination += difference.inclination;

    move(current_direction);
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
void incrementFine(Direction difference)
{
    unsigned int az, inc;
    az = global_delay.AzimuthDelay + difference.azimuth - PWM_HALF_PERIOD;
    inc = global_delay.InclinationDelay + difference.inclination + LATENCY;

    //Ensure that the delays are still within the max and min duty cycles
    validate(&az);
    validate(&inc);

    global_delay.AzimuthDelay = az + PWM_HALF_PERIOD;
    global_delay.InclinationDelay = inc - LATENCY;

    //Update the current_direction
    current_direction = delay2Direction(global_delay);
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

    if (CCP2_INT)
    {
        timer_value = ReadTimer3();

        if (timer_value > PWM_PERIOD)
        {
            IN_PWM_PIN = 1;
            WriteTimer3(0);     //Clear timer2
            current_delay = global_delay;   //update the static delay
            changed = 1;        //Indicate the change has been loaded
            OpenCompare2(COM_INT_ON & COM_UNCHG_MATCH, current_delay.InclinationDelay);
        }
        else if (timer_value > current_delay.AzimuthDelay)
        {
            AZ_PWM_PIN = 0;
            OpenCompare2(COM_INT_ON & COM_UNCHG_MATCH, PWM_PERIOD);
        }
        else if (timer_value > PWM_HALF_PERIOD)
        {
            AZ_PWM_PIN = 1;
            OpenCompare2(COM_INT_ON & COM_UNCHG_MATCH, current_delay.AzimuthDelay);
        }
        else if (timer_value > current_delay.InclinationDelay)
        {
            IN_PWM_PIN = 0;
            OpenCompare2(COM_INT_ON & COM_UNCHG_MATCH, PWM_HALF_PERIOD);
        }

        PIR2bits.CCP2IF = 0;
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
Direction delay2Direction(Delay dly)
{
    Direction ret;

    ret.azimuth = ((dly.AzimuthDelay - DUTY_CYCLE_TIME - PWM_HALF_PERIOD) * (long int)arcRange.azimuth + DIV_2(DUTY_CYCLE_TIME)) / DUTY_CYCLE_TIME;
    ret.inclination = ((dly.InclinationDelay - DUTY_CYCLE_TIME + LATENCY) * (long int)arcRange.inclination + DIV_2(DUTY_CYCLE_TIME))/ DUTY_CYCLE_TIME;

    ret.azimuth = ret.azimuth - DIV_2(arcRange.azimuth) - calibration_offset.azimuth;
    ret.inclination = -(ret.inclination - DIV_2(arcRange.inclination) - calibration_offset.inclination);

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
Delay direction2Delay(Direction dir)
{
    Delay result;
    unsigned int az, inc;

    az = DUTY_CYCLE_TIME + (dir.azimuth + DIV_2(arcRange.azimuth) + calibration_offset.azimuth) * (long int)DUTY_CYCLE_TIME / arcRange.azimuth;
    inc = DUTY_CYCLE_TIME + (-dir.inclination + DIV_2(arcRange.inclination) + calibration_offset.inclination) * (long int)DUTY_CYCLE_TIME / arcRange.inclination;

    validate(&az);
    validate(&inc);

    result.AzimuthDelay = az + PWM_HALF_PERIOD;
    result.InclinationDelay = inc - LATENCY;

    return result;
}


/*! **********************************************************************
 * Function: validate(unsigned int *delay)
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
    if (*delay < DUTY_CYCLE_TIME)
    {
        *delay = DUTY_CYCLE_TIME;
    }
    if (*delay > 2*DUTY_CYCLE_TIME)
    {
        *delay = 2 * DUTY_CYCLE_TIME;
    }
}

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
char updated(void)
{
    return changed;
}