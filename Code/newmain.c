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

//#pragma config WDT = OFF	//Turns watchdog Timer off
//#pragma config OSC = HS		//The crystal oscillator set to "High Speed"
//#pragma config LVP = OFF	//
//#pragma config DEBUG = ON

#include "Common.h"

#include "Tracking.h"
#include "Range.h"
#include "User_Interface.h"
#include "Serial.h"
#include "PanTilt.h"
#include "Menusystem.h"
#include "ConfigRegs18f4520.h"
#include "LCD.h"
#include "jEEP.h"

//Local Function Prototypes:
static void initialization(systemState *state);
//static void transRange(void);

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
    int counter = 0;
    systemState state = {INIT, UNDEF};
    TrackingData target;
    //Direction dir = {20, 20};


//    configureSerial();
//    initializeRange()
    //configureAD();
    initialiseMenu(&state);
    //    configUSER();

//    for (;;)
//    {
//        range();
//    }


    for (;;)
{
       	serviceMenu();

        switch (state.current)
        {
            case INIT:
                initialization(&state);
                break;
            case SRCH:
                search(&state);
                dispSearching();
                break;
            case TRCK:
                target = track(&state);
                dispTrack(target);
                break;
            case MENU:
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
    Direction dir = {0,-45};
    unsigned int i = 0;
    
    configureSerial();
    configureTracking();
    configUSER();
    initializeRange();

    transmitROM(welcome);
    transmitROM(newLine);

    move(dir);

    for (i = 0; i < 10000; i++);

    NEXT_STATE_PTR(MENU, state);   //Go to the searching state
}

