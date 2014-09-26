/*
 * File:   Tracking.c
 * Author: Grant
 *
 * Description: Contains all the functionality for the Tracking Module
 *
 * Created on 15 September 2014, 1:42 PM
 */

#include "Common.h"

//Stores the current system configuration
typedef struct
{
    unsigned char azimuth;           //The current system azimuth
    unsigned char inclination;       //The current system inclination
} DirectionState;

typedef struct
{
    unsigned int az_delay;
    unsigned int in_delay;
} Delay;

//Define the PWM output pins
#define AZ_PWM_PIN PORTBbits.RB0
#define IN_PWM_PIN PORTBbits.RB1
#define AZ_TRIS    TRISBbits.RB0
#define IN_TRIS    TRISBbits.RB1

//The period for 50Hz
#define PWM_PERIOD 20000

//Servo movement macros
#define ARC_RANGE  180  //The maximum range of the servos (in degrees)
#define H_AZ_H_IN() AZ_PWM_PIN = 1; IN_PWM_PIN = 1
#define H_AZ_L_IN() AZ_PWM_PIN = 1; IN_PWM_PIN = 0
#define L_AZ_H_IN() AZ_PWM_PIN = 0; IN_PWM_PIN = 1
#define L_AZ_L_IN() AZ_PWM_PIN = 0; IN_PWM_PIN = 0
#define PWM_CYCLE(tmr) tmr > 20000
#define AZ_CYCLE(tmr) tmr > pwm_delay.az_delay && tmr < pwm_delay.in_delay
#define IN_CYCLE(tmr) tmr > pwm_delay.in_delay && tmr < pwm_delay.az_delay

//(Private) Function prototypes:
void moveBase(DirectionState destination);  //Moves the base to the given Azimuth and Inclination
//void setDelay(DirectionState destination);  //Updates the pwm_delays to match the destination
void validate(unsigned int *delay);

//Variable to store where the sensors are currently pointing
DirectionState current_direction;

//Stores the pwm delays
volatile Delay pwm_delay;

/* **********************************************************************
 * Function: configBase(void)
 *
 * Include: Tracking.h
 *
 * Description: Configures the Base for initial use
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configureBase(void)
{
    unsigned char config, period;
    DirectionState zero_pos = { 0, 0 };
    
    //Set the PWM pins to output
    AZ_TRIS = 0;
    IN_TRIS = 0;

    //Set the PWM pins low
    L_AZ_L_IN();

    //Sets the pwm delays to the zero position
    //setDelay(zero_pos);

    //Prescalar 1:1 on Instruction cycle clock. Oscillator off, external synch off
    config = T1_16BIT_RW & T1_PS_1_1 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF & T1_SOURCE_INT;

    //Configure TMR1
    OpenTimer1(config);

    //Set both CCP modules to run off TMR1
    SetTmrCCPSrc(T1_SOURCE_CCP);
    //T1_CCP1_T3_CCP2 will set TMR1 as source for CCP1 and TMR3 source for CCP2

    config = COM_INT_ON & COM_UNCHG_MATCH;
    period = 20000;  //Equivelent to 50Hz at 1MHz with 1:1 prescalar

    //Configures the CCP2 as output compare
    OpenCompare2(config, period);
}

/* **********************************************************************
 * Function: search(void)
 *
 * Include: Tracking.h
 *
 * Description: Performs an incrimental change in position. Local variables
 *              store previous movements to create a search pattern
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void search(void)
{
    
}

/* **********************************************************************
 * Function: trackingISR(void)
 *
 * Include: Tracking.h
 *
 * Description: Acts as the Interrupt Service Routine for the Tracking module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void trackingISR(void)
{
    unsigned int timer_value;
    
    if (CCP2_INT)
    {
        timer_value = ReadTimer1();
        
        if (PWM_CYCLE(timer_value))
        {
            L_AZ_L_IN();
        }
    }
}

/* **********************************************************************
 * Function: edge(void)
 *
 * Include: Tracking.h
 *
 * Description: Finds the Edge of the target in both the azimuth and inclination
 *              and uses this to find (and move to) the center of the target.
 *
 * Arguments: None
 *
 * Returns: TargetData - The current target information (Azimuth, inclination
 *                       and range to the target). This information is then used
 *                       for the Display in the User interface module.
 *************************************************************************/
TrackingData edge(void)
{
    
}

/* **********************************************************************
 * Function: moveBase(DirectionState destination)
 *
 * Include: 
 *
 * Description: Moves the base to the given destination Azimuth and inclination
 *
 * Arguments: destination - Locally defined struct containing the desired Azimuth
 *                          and Inclination
 *
 * Returns: None
 *
 * Remark: This function uses a polling method to check if the base is at the 
 *         correct position, but it may be better to use interrupts in the future
 *************************************************************************/
void moveBase(DirectionState destination)
{
    pwm_delay.az_delay = destination.azimuth;
    pwm_delay.in_delay = destination.inclination;

    //Validate the calculated delays
    validate(&(pwm_delay.az_delay));
    validate(&(pwm_delay.in_delay));
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

    //Note: This uses integer division, so the multiplication MUST be performed first
    result.az_delay = dir.azimuth * 1000 / ARC_RANGE + 1000;
    result.in_delay = dir.inclination * 1000 / ARC_RANGE + 1000;

    return result;
}