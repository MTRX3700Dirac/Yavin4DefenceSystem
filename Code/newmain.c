/* 
 * File:   newmain.c
 * Author: Grant
 *
 * Description: Controls the main system state of the product based on a state
 *              transition type template
 *
 * Created on 7 September 2014, 4:12 PM
 */
//
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
#include "Temp.h"

#include "Menusystem.h"
#include "HardUItest.h"

<<<<<<< HEAD
#include "LCD.h"
#include "LCD_defs.h"

//Local Function Prototypes:
static void initialization(systemState *state);
static void transRange(void);
=======
// THIS NEEDS TO BE HERE
#include "ConfigRegs18f4520.h"

//Function Prototypes:
void initialization(systemState *state);

extern unsigned int rangeIR(void);
>>>>>>> e358b3317df55eb457e72a70e5c25165911b2fae

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
 *
 * @todo test and debug the Watch Dog Timer functionality
 *************************************************************************/
void main(void) {
<<<<<<< HEAD

    char table1[]="QRSTUVWXYZ123456 ";
    char table2[]="ABCDEFGHIJKLMNOP ";

    lcdInit();//initialize
    delay(10);//delay for the clear display finishes
    lcdWrite(DISPCLR, LCD_INS);

    while(1){
        lcdWriteString(table1, 2);
        delay(500);
        lcdWriteString(table2, 1);
        delay(500);
    }

=======
    unsigned int i;
>>>>>>> e358b3317df55eb457e72a70e5c25165911b2fae
    systemState state = {INIT, UNDEF};
    TrackingData target;
    Direction dir;
    char str[80] = {0};


<<<<<<< HEAD

=======
//    initialiseMenu();
    // strlenpgm(welcome)
//    for(;;)
//    {
//        sendROM(welcome);
//        for (i=0;i<10000;i++);
//    }
//    configureBase();
//    initialiseMenu();
//    menu();

    
//    configureBase();
//
//    dir.azimuth = 0;
//    dir.inclination = 0;
//    move(dir);
//
//    for(;;)
//    {
//        rangeUltrasonic();
//        //transmit(string);
//        for(i=0;i<30000;i++);
//    }
    
>>>>>>> e358b3317df55eb457e72a70e5c25165911b2fae
    for (;;)
    {
        switch (state.current)
        {
            case INIT:
                initialization(&state);
                break;
            case SRCH:
                search(&state);
                break;
            case TRCK:
                track(&state);
                break;
            default:     //Any other undefined state
                NEXT_STATE(INIT, state);       //Set the next state to be Initialize
                break;
        }
#ifdef WDTMR
        WDT_CLR;            //Clear the Watch Dog Timer each iteration
#endif
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
    configureTracking();
    configureSerial();
    configureTemp();

    NEXT_STATE_PTR(SRCH, state);
}
