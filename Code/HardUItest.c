#include <p18f4520.h>
#include "ConfigRegs18f4520.h"
#include <stdio.h>
#include <stdlib.h>

#define ADCON0_set 0x41
#define ADCON1_patch 0x80

char LEDtest[]={0x33, 0x66, 0x9A, 0xCE, 0xFF};
char LEDson[]={0x00, 0x08, 0x0C, 0x0E, 0x0F};
char * LEDtestpntr;
char * LEDsonpntr;

const static rom char LCDWELCOME1[] = "Welcome to Yavin";
const static rom char LCDWELCOME2[] = "Orbital Tracking";

const static rom char TOPMESSAGE1[] = "Top Menu  xxxxx";
const static rom char TOPMEAUTO12[] = " Auto Tracking ";
const static rom char TOPMEMANU22[] = "Manual Tracking";
const static rom char TOPMESTAT32[] = "    Status     ";
const static rom char TOPMESWAP42[] = "  Remote Mode  ";
const static rom char TOPMESLEE52[] = "     Sleep     ";

const char TOPMEHOLDER[] = {TOPMEAUTO12, TOPMEMANU22, TOPMESTAT32, TOPMESWAP42, TOPMESLEE52};
char *topMenuPtr;

const static rom char AUTOMENUTO1[] = "Auto Mode xxxxx";
const static rom char AUTOMENUV12[] = "R:** E:***A:***";
const static rom char AUTOMENUV22[] = "Range:   ****mm";
const static rom char AUTOMENUV32[] = "Elevation: ***o";
const static rom char AUTOMENUV42[] = "Azimuth:   ***o";
const static rom char AUTOMENUV52[] = " Stop Tracking ";

const char AUTOMHOLDER[] = {AUTOMENUV12, AUTOMENUV22, AUTOMENUV32, AUTOMENUV42, AUTOMENUV52};
char *autoMenuPtr;

void PORTconfig(void);
void LEDselect(char val);
void setup(void);
void INTconfig(void);
void ADconfig(void);
void ADgo(void);

void ISR_high_vect(void);
void ISR_high(void);
void ISR_low_vect(void);
void ISR_low(void);

#pragma code highPriorityInterruptAddress=0x0008
void ISR_high_vect(void) {
    _asm GOTO ISR_high _endasm
}
#pragma code lowPriorityInterruptAddress=0x0018
void ISR_low_vect(void) {
    _asm GOTO ISR_low _endasm
}

#pragma interrupt ISR_high
void ISR_high(void){
    char get;
    get = PORTB&0xF0;

    if (PORTBbits.RB4){
        //get = PORTB & 0x10;
        //LEDselect(get);
        ADgo();
    }
    else if (PORTBbits.RB5){
        get = PORTB & 0x00;
        LEDselect(get);
    }
    else if (PORTBbits.RB6){
        get = PORTB & 0x40;
        LEDselect(get);
    }
    else if (PORTBbits.RB7){
        get = PORTB & 0x80;
        LEDselect(get);
    }
//    else{
//        get = PORTB & 0XF0;
//        LEDselect(get);
//    }
}

#pragma interrupt ISR_low
void ISR_low(void){}

void PORTconfig(void){
    TRISBbits.RB7 = 1;
    TRISBbits.RB6 = 1;
    TRISBbits.RB5 = 1;
    TRISBbits.RB4 = 1;
    TRISBbits.RB3 = 0;
    TRISBbits.RB2 = 0;
    TRISBbits.RB1 = 0;
    TRISBbits.RB0 = 0;
}

void INTconfig(void){
    INTCONbits.GIE_GIEH = 1;    /*enable high priority interrupts*/
    INTCONbits.PEIE_GIEL = 1;   /*enable low priority interrupts*/
    INTCONbits.RBIE = 1;        //!enable RB port change interrupt

    //!Check RBIF for change (at least one) (software cleared=> read or write)

    INTCON2bits.RBIP = 1;       //!Set pin change as high interrupt
}

void ADconfig(void){
    //error ADCON1bits.ADFM = 0;        //!Left justify the conversion bank
    ADCON1 &= ADCON1_patch;     //!Patch until error is resolved
    ADCON1bits.PCFG1 = 1;       //!Configure port configuration, all set to
    ADCON1bits.PCFG2 = 1;       //!digital I/O, except AN0 use analogue and
    ADCON1bits.PCFG3 = 1;       //!use standard vrefs
    ADCON0 = ADCON0_set;        //!FOSC/8 and enable conversions
}

void setup(void){
    PORTconfig();
    INTconfig();
    ADconfig();
}

void LEDselect(char val){
    val=val>>4;
    PORTB=val;
}

void ADgo(void){
    char a;
    LEDtestpntr = LEDtest;          //!Assign pointer to beginning of array
    LEDsonpntr = LEDson;            //!Assign pointer for LED choice
    ADCON0bits.GO = 1;              //!Begin a conversion
    while(PIR1bits.ADIF == 0){}     //!Poll the conversion flag until complete
    for(a=0;a<=5;a++){              //!Loop through the options
        if(ADRESH<=*LEDtestpntr){   //!If the converted number is less than the
            PORTB = *LEDsonpntr;    //!stored reference, turn on corresponging LED
            break;                  //!If the correct bin is found, get out of loop
        }
        LEDtestpntr++;LEDsonpntr++; //!Increment pointers for next case
    }

    
}

void main(void){
    setup();
    PORTB = 0;
    while(1){}
}