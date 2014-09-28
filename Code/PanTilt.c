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

//Stores the current system configuration
typedef struct
{
    unsigned int azimuth;           //The current system azimuth
    unsigned int inclination;       //The current system inclination
} DirectionState;

typedef struct
{
    struct
    {
        unsigned int delay_time;
        unsigned char toggle_bits;
    } short_delay;
    struct
    {
        unsigned int delay_time;
        unsigned char toggle_bits;
    } long_delay;

    struct
    {
        unsigned char iterations;
        unsigned char toggle_bits;
    } micro_delay;
} Delay;

//Define the PWM output pins
#define AZ_PWM_PIN 0b00000001
#define IN_PWM_PIN 0b00000010
#define PWM_PINS 0b00000011

//Interrupt Latency
#define LATENCY 340
#define PWM_PERIOD 20000 //The period for 50Hz at 1MHz
#define ARC_RANGE 240 //Max arc of servos

#define min_sep 19
#define min_inc 13

#define SERVO_INIT() TRISCbits.RC0 = 0; TRISCbits.RC1 = 0; PORTCbits.RC0 = 1; PORTCbits.RC1 = 1
#define SERVO_TOGGLE(tog) (PORTC = (PORTC & ~PWM_PINS) | ((PORTC & PWM_PINS) ^ (tog)))

void validate(unsigned int *delay);
Delay direction2Delay(DirectionState dir);

//Static calibration offset
static Direction calibration_offset = { 0, 0 };
static Delay global_delay;

/* **********************************************************************
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
    DirectionState zero = { 14, 0 };
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
}

/* **********************************************************************
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
}

/* **********************************************************************
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
    
}

/* **********************************************************************
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

/* **********************************************************************
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

/* **********************************************************************
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

        if (timer_value > PWM_PERIOD - LATENCY)
        {
            SERVO_INIT();       //Clear PWM pins
            WriteTimer1(0);     //Clear timer2
            current_delay = global_delay;   //update the static delay
            OpenCompare1(COM_INT_ON & COM_UNCHG_MATCH, current_delay.short_delay.delay_time);
        }
        else if (timer_value > current_delay.long_delay.delay_time)
        {
            SERVO_TOGGLE(current_delay.long_delay.toggle_bits);
            OpenCompare1(COM_INT_ON & COM_UNCHG_MATCH, PWM_PERIOD);
        }
        else if (timer_value > current_delay.short_delay.delay_time)
        {
            SERVO_TOGGLE(current_delay.short_delay.toggle_bits);
            //_asm nop _endasm
            for (; i < current_delay.micro_delay.iterations; i++);
            SERVO_TOGGLE(current_delay.micro_delay.toggle_bits);
            OpenCompare1(COM_INT_ON & COM_UNCHG_MATCH, current_delay.long_delay.delay_time);
            //OpenCompare1(COM_INT_ON & COM_UNCHG_MATCH, PWM_PERIOD - LATENCY);
        }

        PIR1bits.CCP1IF = 0;
    }
}

/* **********************************************************************
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
    unsigned int az_delay;
    unsigned int in_delay;
    unsigned int micro_delay;

    //Note: This uses integer division, so the multiplication MUST be performed first
    az_delay = dir.azimuth * (unsigned long int)1000 / ARC_RANGE + 1000;
    in_delay = dir.inclination * (unsigned long int)1000 / ARC_RANGE + 1000;

    validate(&az_delay);
    validate(&in_delay);

    if (az_delay < in_delay)
    {
        result.short_delay.delay_time = az_delay - LATENCY;
        result.long_delay.delay_time = in_delay - LATENCY;
        result.short_delay.toggle_bits = AZ_PWM_PIN;
        result.long_delay.toggle_bits = IN_PWM_PIN;
    }
    else
    {
        result.long_delay.delay_time = az_delay - LATENCY;
        result.short_delay.delay_time = in_delay - LATENCY;
        result.long_delay.toggle_bits = AZ_PWM_PIN;
        result.short_delay.toggle_bits = IN_PWM_PIN;
    }

    micro_delay = result.long_delay.delay_time - result.short_delay.delay_time;
    if (micro_delay < min_sep)
    {
        result.short_delay.toggle_bits = AZ_PWM_PIN | IN_PWM_PIN;
        result.micro_delay.iterations = 0;
        result.micro_delay.toggle_bits = 0;
        result.long_delay.delay_time = PWM_PERIOD;
    }
    else if (micro_delay < LATENCY)
    {
        //result.micro_delay.iterations = 3;
        result.micro_delay.iterations = (micro_delay - min_sep) / min_inc;
        result.micro_delay.toggle_bits = az_delay > in_delay ? AZ_PWM_PIN : IN_PWM_PIN;
        //result.short_delay.toggle_bits = AZ_PWM_PIN | IN_PWM_PIN;
        result.long_delay.delay_time = PWM_PERIOD;
    }
    else
    {
        result.micro_delay.iterations = 0;
        result.micro_delay.toggle_bits = 0;
    }

    return result;
}

/* **********************************************************************
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