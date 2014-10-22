/*! ****************************************************************************
 * File:   Common.h
 * Author: Grant
 *
 * Description:
 * Contains all program scope definitions, declarations and inclusions. This header
 * should be included in all source files by default.
 *
 * Contains:
 *      -PIC18F family library headers
 *      -Direction struct typedef
 *      -TrackingData struct typedef
 *      -systemState struct typedef
 *      -system state macro functionality
 *      -TargetState enumeration
 *      -Interrupt flag macros
 *      -Division macros
 *      -Clock frequency definitions
 *      -SWAP macro functionality
 *
 * Created on 11 September 2014, 12:24 PM
 ******************************************************************************/

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef COMMON_H

// Use the MNML Board. Comment this out for the PICDEM
#define MNML

//Include files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <p18cxxx.h>
// Commented out for the general case. Put back in if it breaks
//#include <p18f4520.h>



//Peripherial headers
#include <timers.h>
#include <adc.h>
#include <capture.h>
#include <usart.h>
#include <capture.h>
#include <compare.h>

/*! ****************************************************************************
 * typedef of Direction struct
 *
 * @brief Stores an inclination and azimuth
 *
 * Description:
 * A fully defined direction in which to point the pan tilt actuator
 * or any other such purpose
 *
 * Elements:
 *      -Azimuth: Contains the azimuth component of the direction (generally degrees)
 *      -Inclination: Contains the inclination component of the direction (generally degrees)
 ******************************************************************************/

typedef struct
{
    int azimuth;
    int inclination;
} Direction;

//Tracking Data definition: Stores the current target information
/*! ****************************************************************************
 * typedef of TrackingData struct
 *
 * @brief Stores the current target information
 *
 * Description:
 * Stores distance, azimuth and inclination tracking data to the target.
 * This struct is used by the tracking function and others to communicate
 * the position of the target
 ******************************************************************************/
typedef struct
{
    unsigned int distance;      //Distance to the target
    int azimuth;                //Azimuth to the target
    int inclination;            //inclination to the target
} TrackingData;

///The different types of tracking possible depending on which sensors observe the target
//           !(IR||US)  (US&&!IR) (US&&!IR), (US&&IR)    (IR&&!US)
typedef enum{NO_TARGET, OUT_OF_IR, BAD_DIR, GOOD_TRACK, CLOSE_RANGE} TargetState;


/// Macros to change the state of the system
#define NEXT_STATE(s, state) state.previous = state.current; state.current = s
#define NEXT_STATE_PTR(s, state) state->previous = state->current; state->current = s

///Define the possible states the system can be in
typedef enum{UNDEF, INIT, SRCH, TRCK} possible_states;

/*! ****************************************************************************
 * typedef of systemState struct
 *
 * @brief Stores the current state of the system
 *
 * Description:
 * Stores which state the system is currently in, as defined by the
 * possible_states enumeration. Also stores the previous system state
 * so the system knows if this is the first iteration of the state
 ******************************************************************************/
typedef struct {
    possible_states current;
    possible_states previous;
} systemState;

///Efficient Division macros based on bit shifting, Cannot be used on negative numbers
#define DIV_2(v) ((v) >> 1)       //Divide by 2
#define DIV_4(v) ((v) >> 2)       //Divide by 4
#define DIV_8(v) ((v) >> 3)       //Divide by 8
#define DIV_16(v) ((v) >> 4)      //Divide by 16
#define DIV_32(v) ((v) >> 5)      //Divide by 32
#define DIV_64(v) ((v) >> 6)      //Divide by 64
#define DIV_128(v) ((v) >> 7)     //Divide by 128
#define DIV_256(v) ((v) >> 8)     //Divide by 256
#define DIV_512(v) ((v) >> 9)     //Divide by 512
#define DIV_1024(v) ((v) >> 10)   //Divide by 1024
#define DIV_4096(v) ((v) >> 12)   //Divide by 4096
#define DIV_65536(v) ((v) >> 16)    //Divide by 65536

///Swaps the values in two variables
#define SWAP(x, y) (y = (y ^ (x = (x ^ (y = (x ^ y))))))

///ADC Channel Select macros
#define ADC_IR_READ 0            //Sets ADC to read the IR
#define ADC_TEMP_READ 1          //Sets the ADC to read the temp
#define ADC_DIAL_READ 2          //Sets the ADC to read the DIAL

///Interrupt macros
#define TX_INT (PIR1bits.TXIF && PIE1bits.TXIE)       //serial transmit interrupt fired
#define RC_INT (PIR1bits.RCIF && PIE1bits.RCIE)       //serial receive interrupt fired
#define CCP1_INT (PIR1bits.CCP1IF && PIE1bits.CCP1IE) //Whether CCP1 fired the interrupt
#define CCP2_INT (PIR2bits.CCP2IF && PIE2bits.CCP2IE) //Whether CCP2 fired the interrupt
#define INT0_INT (INTCONbits.INT0IF && INTCONbits.INT0IE) //Whether the external interrupt fired
#define INT1_INT (INTCON3bits.INT1IF && INTCON3bits.INT1IE) //Whether the external interrupt fired
#define INT2_INT (INTCON3bits.INT2IF && INTCON3bits.INT2IE) //Whether the external interrupt fired
#define RB_INT   (INTCONbits.RBIF && INTCONbits.RBIE)  //Whether the RB port change interrupt fired
#define TMR2_INT (PIR1bits.TMR2IF && PIE1bits.TMR2IE)   //TMR2 matching PR2 fired the interrupt

#define TMR0_INT (INTCONbits.TMR0IF && INTCONbits.TMR0IE) //Whether the timer0 overflow fired the interrupt
#define TMR1_INT (PIR1bits.TMR1IF && PIE1bits.TMR1IE)   //TMR1 overflow fired interrupt
#define TMR3_INT (PIR2bits.TMR3IF && PIE2bits.TMR3IE)   //TMR3 overflow fired interrupt
#define ADC_INT (PIR1bits.ADIF && PIE1bits.ADIE)        //Whether the ADC fired the interrupt
#define SSP_INT (PIR1bits.SSPIF && PIE1bits.SSPIE)      //Whether the SSP module fired the interrupt
#define BCL_INT (PIR2bits.BCLIF && PIE2bits.BCLIE)      //Bus collision interrupt fired
#define LVD_INT (PIR2bits.LVDIF && PIE2bits.LVDIE)      //Low voltage detect interrupt fired

#define CCP1_CLEAR (PIR1bits.CCP1IF = 0)
#define CCP2_CLEAR (PIR2bits.CCP2IF = 0)

#define WDT_EN WDTCONbits.SWDTE = 1; WDTCONbits.SWDTEN = 1;
#define WDT_CLR _asm CLRWDT _endasm            //Clear watchdog timer


///Dfine the clock rate and FOSC_4
#ifdef MNML 1
#define CLOCK   10000000    //10MHz clock source
#define FOSC_4  2500000     //2.5MHz Fosc_4
#else
#define CLOCK 4000000   //2.5MHz clock source
#define FOSC_4 1000000   //1MHz Fosc_4
#endif

/*
 * Pins 
 */

#define COMMON_H
#endif