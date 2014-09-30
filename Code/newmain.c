/* 
 * File:   newmain.c
 * Author: Grant
 *
 * Description: Controls the main system state of the product based on a state
 *              transition type template
 *
 * Created on 7 September 2014, 4:12 PM
 */

#pragma config WDT = OFF	//Turns watchdog Timer off
#pragma config OSC = HS		//The crystal oscillator set to "High Speed"
#pragma config LVP = OFF	//
#pragma config DEBUG = ON

#include "Common.h"

#include "Tracking.h"
#include "Range.h"
#include "User_Interface.h"
#include "Serial.h"

#include "PanTilt.h"
#include "Temp.h"

//Define Macros to change the state of the system
#define NEXT_STATE(s) state.previous = state.current; state.current = s
#define NEXT_STATE_PTR(s) state->previous = state->current; state->current = s

//Define the enum and struct to store the current system state
typedef enum{UNDEF, INIT, CHANGE, MEAS, EDGE} possible_states;
typedef struct {
    possible_states current;
    possible_states previous;
} systemState;

//Function Prototypes:
void initialization(systemState *state);
void check_target(systemState *state);
void change_direction(systemState *state);
void measure_distance(systemState *state, TrackingData *target);
void find_edge(systemState *state, TrackingData *target);
void post_edge(TrackingData *target);

void lowISR(void);
void highISR(void);

extern unsigned int rangeIR(void);


/*! **********************************************************************
 * Function: main(void)
 *
 * \brief Program entry point
 *
 * Include: 
 *
 * Description: stores the current system state and manages all transitions
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void main() {
    systemState state = {INIT, UNDEF};
    TrackingData target;
    unsigned int i, j;
    unsigned int range = 0;

    Direction dir;

    configureBase();

    dir.azimuth = 180;
    dir.inclination = 180;
    move(dir);

    configureRange();
    for (;;)
    {
        range = rangeIR();
        range += 0;
    }
/*
    for (;;)
    {
    for (i = 0; i < 240; i++)
    {
        for (j = 0; j < 100; j++);
        dir.azimuth = i;
        dir.inclination = i;
        move(dir);
    }
    for (i = 240; i > 0; i--)
    {
        for (j = 0; j < 100; j++);
        dir.azimuth = i;
        dir.inclination = i;
        move(dir);
    }
    }*/
    
    for (;;)
    {
        switch (state.current)
        {
            case INIT:
                initialization(&state);
                break;
            case CHANGE:
                change_direction(&state);
                break;
            case EDGE:
                find_edge(&state, &target);
                break;
            case MEAS:
                measure_distance(&state, &target);
                break;
            default:     //Any other undefined state
                NEXT_STATE(INIT);       //Set the next state to be Initialize
                break;
        }
    }

}

/*! **********************************************************************
 * Function: initialization(systemState *state)
 *
 * Include: 
 *
 * Description: Initializes the system, turns on the sensors and checks if
 * they are ready to begin working
 *
 * Arguments: state - The current state of the system
 *
 * Returns: The next system state - At the moment always just transitions to CHECK
 *************************************************************************/
void initialization(systemState *state)
{
    //Initialise the Interrupts
    PIR1 = 0x00;            //Clear all interrupt flags
    PIR2 = 0x00;
    INTCONbits.GIEH = 1;    //Unmask global high interrupts
    INTCONbits.GIEL = 1;    //Unmask global low interrupts
    RCONbits.IPEN = 1;      //Enable interrupt priority

    //Open ADC. Set A/D conversion Clock to Fosc/2, Acuisition time is 20TAD (10 microseconds)
    //Read from channel 0, and disable A/D interrupts
    //OpenADC(ADC_FOSC_2 & ADC_RIGHT_JUST & ADC_20_TAD, ADC_CH0 & ADC_INT_OFF);
    OpenADC(ADC_FOSC_2 & ADC_0_TAD & ADC_INT_OFF, ADC_RIGHT_JUST & ADC_1ANA, ADC_CH0);
    TRISAbits.TRISA0 = 1;   //Set channel 0 on port A input
    TRISAbits.TRISA1 = 1;   //Set channel 1 on port A input
    TRISAbits.TRISA2 = 1;   //Set channel 2 on port A input

    NEXT_STATE_PTR(MEAS);
}

/*! **********************************************************************
 * Function: change_direction(systemState *state)
 *
 * Include: Tracking.h
 *
 * Description: alters the sensors' direction
 *
 * Arguments: state - The current state of the system
 *
 * Returns: The next system state
 *************************************************************************/
void change_direction(systemState *state)
{
    //Call the search function in the tracking module
    search();

    //Set the next state to target check
    NEXT_STATE_PTR(MEAS);
}

/*! **********************************************************************
 * Function: measure_distance(systemState *state, TrackingData *target)
 *
 * Include: range.h
 *
 * Description: Measures the distance to the target via IR and Sonar sensors
 *
 * Arguments: state  - The current system state
 *            target - Pointer to the current target information (azimuth,
 *                     inclination and distance)
 *
 * Returns: The next system state, and target distance through the target pointer
 *
 * Remarks: The measure state also doubles as the check for target state as
 *          the range function will simply return 0 if no target is detected
 *************************************************************************/
void measure_distance(systemState *state, TrackingData *target)
{
    //Measure range, and write to target distance
    target->distance = range();

    if (target->distance)
    {
        NEXT_STATE_PTR(EDGE);
    }
    else
    {
        NEXT_STATE_PTR(CHANGE);
    }

}

/*! **********************************************************************
 * Function: find_edge(TrackingData &target, DirectionState &direction)
 *
 * Include: main_head.h
 *
 * Description: Finds the edge of the target by moving until the target is
 *              no longer detected
 *
 * Arguments: target - Pointer to the current target information (azimuth,
 *                     inclination and distance)
 *            direction - Pointer to the current system direction (aximuth,
 *                     inclination and movement directives)
 *
 * Returns: The next system state, and target edge through the direction pointer
 *
 * Remarks:
 *************************************************************************/
void find_edge(systemState *state, TrackingData *target)
{
    //Call the edge function in the targeting module
    *target = edge();

    //Select next state
    NEXT_STATE_PTR(MEAS);
}


/*! **********************************************************************
 * Function: highVector(void)
 *
 * Include:
 *
 * Description: Sends program control to the high priority ISR
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Remarks: This is an interrupt vector, placing a goto in the
 *          high priority interrupt table to call the high priority ISR
 *************************************************************************/
#pragma code highPriorityInterruptAddress=0x0008
void highVector(void)
{
    _asm GOTO highISR _endasm
}

/*! **********************************************************************
 * Function: lowVector(void)
 *
 * Include:
 *
 * Description: Sends program control to the low priority ISR
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Remarks: This is an interrupt vector, placing a goto in the
 *          low priority interrupt table to call the low priority ISR
 *************************************************************************/
#pragma code lowPriorityInterruptAddress=0x0018
void lowVector(void)
{
    _asm GOTO lowISR _endasm
}

/*! **********************************************************************
 * Function: lowISR(void)
 *
 * Include: Interrupt_head.h
 *
 * Description: Interrupt Service Routine to check what condition initiated
 *              a low priority interrupt call, and perform the nessicary action
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
#pragma interruptlow lowISR
void lowISR(void)
{
    if (SERIAL_INT)
    {
        serialISR();
    }
    else if (PAN_TILT_ISR)
    {
        panTiltISR();
    }
    else if (RANGE_INT)
    {
        rangeISR();
    }
    else if (USER_INT)
    {
        userISR();
    }
}

/*! **********************************************************************
 * Function: highISR(void)
 *
 * Include:
 *
 * Description: Interrupt Service Routine to check what condition initiated
 *              a high priority interrupt call, and perform the nessicary action
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
#pragma interrupt highISR
void highISR(void)
{
    if (PAN_TILT_ISR)
    {
        panTiltISR();
    }
    else if (SERIAL_INT)
    {
        serialISR();
    }
    else if (RANGE_INT)
    {
        rangeISR();
    }
    else if (USER_INT)
    {
        userISR();
    }
}

