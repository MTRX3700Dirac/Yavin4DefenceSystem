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
#include "jEEP.h"
//#include "ConfigRegs18f4520.h"

//Local Function Prototypes:
static void initialization(systemState *state);
//static void transRange(void);
static void dispTrack(TrackingData target);

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

//
    configureSerial();
    configureRange();
//    configUSER();

    for (;;)
    {
        range();
    }

    initialiseMenu();

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
                break;
            case TRCK:
                target = track(&state);
                dispTrack(target);
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
    char temp[80];
    
    configureSerial();
    configureTracking();
    configUSER();

    strcpypgm2ram(temp, welcome);
    transmit(temp);

    NEXT_STATE_PTR(SRCH, state);   //Go to the searching state
}

static void dispTrack(TrackingData target)
{
    unsigned int j;
    char rng_string[] = "Range: ";
    char inc_string[] = "Inclination: ";
    char az_string[] = "Azimuth: ";
    char newLine[] = "\n\r";
    char neg = '-';
    char num[5];

    transmit(rng_string);
    if (target.distance < 0)
    {
        target.distance = - target.distance;
        transChar(neg);
    }
    sprintf(num, "%u", target.distance);
        transmit(num);
        transmit(newLine);

    transmit(inc_string);
    if (target.inclination < 0)
    {
        target.inclination = - target.inclination;
        transChar(neg);
    }
    sprintf(num, "%u", target.inclination);
        transmit(num);
        transmit(newLine);

    transmit(az_string);

    if (target.azimuth < 0)
    {
        target.azimuth = - target.azimuth;
        transChar(neg);
    }
    sprintf(num, "%u", target.azimuth);
        transmit(num);
        transmit(newLine);
}
