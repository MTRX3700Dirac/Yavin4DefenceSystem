/*! ****************************************************************************
 * File:   newmain.c
 * 
 * Author: Grant, Bas, Ayush, Zhenning, Jacob, Alvaro
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

//Local Function Prototypes:
static void initialization(systemState *state);

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


//    configureSerial();
//    configureRange();
    //configureAD();
    initialiseMenu(&state);

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
            case RAW_RANGE_STATE:
                range();
                dispRawRange();
                Delay10KTCYx(255);
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

    move(dir);

    for (i = 0; i < 10000; i++);

    NEXT_STATE_PTR(MENU, state);   //Go to the searching state
}
