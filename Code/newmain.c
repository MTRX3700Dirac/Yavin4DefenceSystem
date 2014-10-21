/*! ****************************************************************************
 * File:   newmain.c
 * 
 * Author: Grant
 *
 * Description: 
 * Controls the main system state of the product based on a state transition
 * type template.
 *
 * Created on 7 September 2014, 4:12 PM
 ****************************************************************************/

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
#include "Menusystem.h"

//Local Function Prototypes:
static void initialization(systemState *state);
static void transRange(void);

/*! **********************************************************************
 * Function: main(void)
 *
 * \brief Program entry point
 *
 * Include: Local to newmain.c
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
            case SRCH:
                search(&state);
                break;
            case TRCK:
                target = track(&state);
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
 * Include: Local to newmain.c
 *
 * Description: Initializes the system, turns on the sensors and checks if
 * they are ready to begin working
 *
 * Arguments: state - The current state of the system
 *
 * Returns: The next system state - At the moment always just transitions to CHECK
 *************************************************************************/
static void initialization(systemState *state)
{
    configureSerial();
    configureTracking();

    NEXT_STATE_PTR(SRCH, state);   //Go to the searching state
}

/*! **********************************************************************
 * Function: transRange(void)
 *
 * Include: Local to newmain.c
 *
 * Description: Measures and Transmits the range -> for testing purposes only
 *
 * Arguments: None
 *
 * Returns: None; Prints range to the screen
 *************************************************************************/
static void transRange(void)
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


