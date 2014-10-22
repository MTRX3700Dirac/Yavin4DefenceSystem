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

// THIS NEEDS TO BE HERE
#include "ConfigRegs18f4520.h"

//Function Prototypes:
void initialization(systemState *state);

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
 *
 * @todo test and debug the Watch Dog Timer functionality
 *************************************************************************/
void main(void) {
    unsigned int i;
    systemState state = {INIT, UNDEF};
    TrackingData target;
    Direction dir;
    char str[80] = {0};


//    initialiseMenu();
    // strlenpgm(welcome)
//    for(;;)
//    {
//        sendROM(welcome);
//        for (i=0;i<10000;i++);
//    }
    configureBase();
    initialiseMenu();
    menu();

    
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
    //Initialise the Interrupts
    PIR1 = 0x00;            //Clear all interrupt flags
    PIR2 = 0x00;
    INTCONbits.GIEH = 1;    //Unmask global high interrupts
    INTCONbits.GIEL = 1;    //Unmask global low interrupts
    RCONbits.IPEN = 1;      //Enable interrupt priority

    //Open ADC. Set A/D conversion Clock to Fosc/2, Acuisition time is 20TAD (10 microseconds)
    //Read from channel 0, and disable A/D interrupts

    // On the MNML board, use a different ADC
#ifdef MNML
    OpenADC(ADC_FOSC_2 & ADC_0_TAD & ADC_INT_OFF, ADC_RIGHT_JUST & ADC_1ANA, ADC_CH0);
#else
    OpenADC(ADC_FOSC_2 & ADC_RIGHT_JUST & ADC_20_TAD, ADC_CH0 & ADC_INT_OFF);
#endif

    TRISAbits.TRISA0 = 1;   //Set channel 0 on port A input
    TRISAbits.TRISA1 = 1;   //Set channel 1 on port A input
    TRISAbits.TRISA2 = 1;   //Set channel 2 on port A input

    NEXT_STATE_PTR(SRCH, state);
}