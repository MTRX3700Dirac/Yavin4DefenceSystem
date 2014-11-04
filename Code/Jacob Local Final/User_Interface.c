/*! ****************************************************************************
 * File:   User_Interface.c
 * Author: Grant
 *
 * Description:
 * Contains all the functionality for the User_Interface module.
 * Works the same way as the serial module, but for the user interface.
 *
 * Duties:
 *      -Stores any local user input in a receive buffer
 *      -Sends display data to the LCD
 *
 * Created on 15 September 2014, 1:21 PM
 ******************************************************************************/

#include "Common.h"
#include "CircularBuffers.h"
#include "Range.h"
#include "User_Interface.h"
#include "Serial.h"

#define CONFIRM_PRESS INTCONbits.INT0IF
#define BACK_PRESS INTCON3bits.INT1F
//#define BACK_PRESS RB_INT

#define ADC_MAX 1023  // Max number allocated by a 10 bit number

//Store anything entered by the user
circularBuffer receive;

/*! **********************************************************************
 * Function: display(TrackingData data)
 *
 * Include: User_Interface.h
 *
 * Description: displays the current tracking information
 *
 * Arguments: data - Struct which contains all known data concerning the
 *                   The position of the target. A Range of 0 indicates
 *                   that no target was observed.
 *
 * Returns: None
 *************************************************************************/
void display(TrackingData data)
{

}

/*! **********************************************************************
 * Function: userISR(void)
 *
 * Include: User_Interface.h
 *
 * Description: Acts as the ISR for the User_interface module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void userISR(void)
{
    if (CONFIRM_PRESS)
    {
        push(CONFIRM_CHAR, receive);
        CONFIRM_PRESS = 0;
    }
    if (BACK_PRESS)
    {
            push(BACK_CHAR, receive);
            BACK_PRESS = 0;
    }
    return;
}

/*! **********************************************************************
 * Function: configUSER(void)
 *
 * Include: User_Interface.h
 *
 * Description: Configures the user interface for use
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configUSER(void)
{
    //Initialises the receive buffer
    init(receive);

    configureAD();

//    // Set RB 0 and 1 to input
    TRISB = 0;
    PORTB = 0;
    TRISB = 0xFF;

    INTCONbits.GIE_GIEH = 1;    /*enable high priority interrupts*/
    INTCONbits.PEIE_GIEL = 1;   /*enable low priority interrupts*/

    // Enable INT0 interrupt
    INTCON2bits.INTEDG0 = 1;    // Interrupt on rising edge
    INTCONbits.INT0IE = 1;

//    INTCON2bits.RBPU = 1;
//    INTCON2bits.RBIP = 1;
//    INTCONbits.RBIE = 1;

    // Enable INT1 interrupt
    INTCON3bits.INT1IP = 1;
    INTCON2bits.INTEDG1 = 1;    // Interrupt on rising edge
    INTCON3bits.INT1E = 1;
}

/*! **********************************************************************
 * Function: readDial(void)
 *
 * Include:
 *
 * Description: Read the position of the dial
 *
 * Arguments: None
 *
 * Returns: The dial position scaled by
 *************************************************************************/
unsigned int readDial(unsigned int max)
{
    unsigned int value;
    int divisor;
    unsigned int retval;

    //Sets the AD channel for the DIAL

    //SetChanADC(ADC_DIAL_READ);
    ADCON0 = 0x05;  //! Channel 1, an1

    //Begin convertion
//    ConvertADC();
//    while(BusyADC());
//    value = ReadADC();
     ADCON0bits.GO = 1;              //!Begin a conversion
    while(PIR1bits.ADIF == 0){}     //!Poll the conversion flag until complete
    value = ADRES;
    if (value >= (ADC_MAX - 9)) return max;
    divisor = ADC_MAX/(max + 1);
    // Return a number from 0 - max
    retval = (value/divisor);
    return retval;
}

/*!
 * Returns a value from 1 to max
 */
unsigned int readDialForMenu(unsigned int max)
{
    unsigned int value;
    ADCON0 = 0x05;
    ADCON0bits.GO = 1;
    while(PIR1bits.ADIF == 0){}
    value = ADRES;
    if(max == 3){
        if(value<=333){return 1;}
        else if(value>333&&value<666){return 2;}
        else{return 3;}
    }
    else if(max == 2){
    if(value<=500){return 1;}
    else{return 2;}
    }
    else if(max == 6){
        if(value<=200){return 1;}
        else if(value>200&&value<400){return 2;}
        else if(value>400&&value<600){return 3;}
        else if(value>600&&value<800){return 4;}
        else if(value>800&&value<1000){return 5;}
        else{return 6;}
    }
    else{
        if(value<=200){return 1;}
        else if(value>200&&value<400){return 2;}
        else if(value>400&&value<600){return 3;}
        else if(value>600&&value<800){return 4;}
        else if(value>800&&value<1000){return 5;}
        else{return 6;}
    }
}

unsigned int readDialForSelect(unsigned int max, unsigned int min, unsigned char binstep)
{
    unsigned int value;
    unsigned int binsize;
    unsigned char i=0;

    ADCON0 = 0x05;
    ADCON0bits.GO = 1;
    while(PIR1bits.ADIF == 0){}
    value = ADRES;
    binsize = (max-min)/binstep;

    while(1){
        if(value<(min+binsize*i)){return(min+i*binstep);}
        i++;
    }
}

/*! **********************************************************************
 * Function: userEmpty(void)
 *
 * Include: User_Interface.h
 *
 * Description: returns non-zero if the user interface buffer is empty (i.e.
 *              no user input has been detected)
 *
 * Arguments: None
 *
 * Returns: if the user input buffer is empty
 *************************************************************************/
char userEmpty(void)
{
    return empty(receive);
}

/*! **********************************************************************
 * Function: userPop(void)
 *
 * Include: User_Interface.h
 *
 * Description: pops a character from the user interface receive buffer
 *
 * Arguments: None
 *
 * Returns: a character poped from the user Interface buffer
 *************************************************************************/
extern char userPop(void)
{
    char c;
    c = pop(receive);
    return c;
}

/*! **********************************************************************
 * Function: userPeek(void)
 *
 * Include: User_Interface.h
 *
 * Description: returns a character in the user_Interface buffer without
 *              removing it from the buffer
 *
 * Arguments: None
 *
 * Returns: a character in the user interface buffer
 *************************************************************************/
extern char userPeek(void)
{
    return peek(receive);
}