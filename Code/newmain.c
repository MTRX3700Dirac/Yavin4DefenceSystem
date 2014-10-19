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

#include "Menusystem.h"

//Function Prototypes:
void initialization(systemState *state);
void check_target(systemState *state);
void change_direction(systemState *state);
void measure_distance(systemState *state, TrackingData *target);
void find_edge(systemState *state, TrackingData *target);
void post_edge(TrackingData *target);



extern unsigned int rangeIR(void);

void transRange(void)
{
    int j;
    char stringUS[] = "US Range:";
    char stringIR[] = "IR Range:";
    char newLine[] = "\n\r";
    char num[5];

    sprintf(num, "%u", rangeUltrasonic());

        transmit(num);
        transmit(newLine);
        for (j=0; j<60000;j++);
        for (j=0; j<60000;j++);

    transmit(stringIR);
        sprintf(num, "%u", rangeIR());
        transmit(num);
        transmit(newLine);
        transmit(newLine);
}

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

    for (;;)
    {
        //if (TMR1H > 10000) serviceMenu();
        switch (state.current)
        {
            case INIT:
                initialization(&state);
                break;
            case CHANGE:
                change_direction(&state);
                break;
            case SRCH:
                search2(&state);
                break;
            case TRCK:
                target = track(&state);
                break;
            case EDGE:
                find_edge(&state, &target);
                break;
            case MEAS:
                measure_distance(&state, &target);
                break;
            default:     //Any other undefined state
                NEXT_STATE(INIT, state);       //Set the next state to be Initialize
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
    configureSerial();
    configureTracking();

    NEXT_STATE_PTR(SRCH, state);   //Go to the searching state
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
    NEXT_STATE_PTR(MEAS, state);
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
        NEXT_STATE_PTR(EDGE, state);
    }
    else
    {
        NEXT_STATE_PTR(CHANGE, state);
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
    //*target = edge();

    //Select next state
    NEXT_STATE_PTR(MEAS, state);
}




