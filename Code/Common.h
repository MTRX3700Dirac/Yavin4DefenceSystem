/* 
 * File:   Common.h
 * Author: Grant
 *
 * Created on 11 September 2014, 12:24 PM
 */

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef COMMON_H

// Use the MNML Board. Comment this out for the PICDEM
#define MNML

//Include files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef MNML
#include <p18f4520.h>
#else
#include <p18f452.h>
#endif

//Peripherial headers
#include <timers.h>
#include <adc.h>
#include <capture.h>
#include <usart.h>
#include <capture.h>
#include <compare.h>

#ifndef MNML
//System configurations
#pragma config WDR = OFF
#pragma config OSC = HS
#pragma config LVP = OFF
#pragma config DEBUG = ON
#endif

//Direction definition: Stores an inclination and azimuth - i.e. a fully defined
//direction to point the pan tilt.
typedef struct
{
    int azimuth;
    int inclination;
} Direction;

//Tracking Data definition: Stores the current target information
typedef struct
{
    unsigned int distance;      //Distance to the target
    int azimuth;       //Azimuth to the target
    int inclination;   //inclination to the target
} TrackingData;

//           !(IR||US)  (US&&!IR) (US&&!IR), (US&&IR)    (IR&&!US)
typedef enum{NO_TARGET, OUT_OF_IR, BAD_DIR, GOOD_TRACK, CLOSE_RANGE} TargetState;


//Define Macros to change the state of the system
#define NEXT_STATE(s, state) state.previous = state.current; state.current = s
#define NEXT_STATE_PTR(s, state) state->previous = state->current; state->current = s

//Define the enum and struct to store the current system state
typedef enum{UNDEF, INIT, SRCH, TRCK} possible_states;
typedef struct {
    possible_states current;
    possible_states previous;
} systemState;

//Efficient Division macros
#define DIV_2(v) ((v) >> 1)       //Divide by 2, Cannot be used on negative numbers
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

#define SWAP(x, y) (y = (y ^ (x = (x ^ (y = (x ^ y))))))

//ADC Channel Select macros
#define ADC_IR_READ 0            //Sets ADC to read the IR
#define ADC_TEMP_READ 1          //Sets the ADC to read the temp
#define ADC_DIAL_READ 2          //Sets the ADC to read the DIAL

//Interrupt macros
#define TX_INT (PIR1bits.TXIF && PIE1bits.TXIE)       //serial transmit interrupt fired
#define RC_INT (PIR1bits.RCIF && PIE1bits.RCIE)       //serial receive interrupt fired
#define CCP1_INT (PIR1bits.CCP1IF && PIE1bits.CCP1IE) //Whether CCP1 fired the interrupt
#define CCP2_INT (PIR2bits.CCP2IF && PIE2bits.CCP2IE) //Whether CCP2 fired the interrupt
#define INT0_INT (INTCONbits.INT0IF && INTCONbits.INT0IE) //Whether the external interrupt fired
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

#ifdef MNML
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