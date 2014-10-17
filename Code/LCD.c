/*
 * File:   User_Interface.c
 * Author: Grant
 *
 * Description: Contains all the interface to the LCD hardware
 *
 * Created on 15 September 2014, 1:21 PM
 */

#include "Common.h"

    //!; BLACK boards have LCD control bits on PORTD and the LCD power
    //!; MUST BE ENABLED by setting PORTD.7 high to turn on Q2
    
    #define LCD_D4 PORTDbits.RD0    //!LCD data bits
    #define LCD_D5 PORTDbits.RD1
    #define LCD_D6 PORTDbits.RD2
    #define LCD_D7 PORTDbits.RD3

    #define LCD_D4_DIR TRISDbits.RD0    //!LCD data bits
    #define LCD_D5_DIR TRISDbits.RD1
    #define LCD_D6_DIR TRISDbits.RD2
    #define LCD_D7_DIR TRISDbits.RD3

    #define LCD_PWR PORTDbits.RD7 //!LCD Power
    #define LCD_E PORTDbits.RD6   //!LCD E clock
    #define LCD_RW PORTDbits.RD5  //!LCD read/write line
    #define LCD_RS PORTDbits.RD4  //!LCD register select line

    #define LCD_PWR_DIR TRISDbits.RD7
    #define LCD_E_DIR   TRISDbits.RD6
    #define LCD_RW_DIR  TRISDbits.RD5
    #define LCD_RS_DIR  TRISDbits.RD4

//    ; GREEN and RED boards have LCD always powered and LCD control bits on PORTA
//    #define LCD_D4      PORTD, 0    ; LCD data bits
//    #define LCD_D5      PORTD, 1
//    #define LCD_D6      PORTD, 2
//    #define LCD_D7      PORTD, 3
//
//    #define LCD_D4_DIR  TRISD, 0    ; LCD data bits
//    #define LCD_D5_DIR  TRISD, 1
//    #define LCD_D6_DIR  TRISD, 2
//    #define LCD_D7_DIR  TRISD, 3
//
//    #define LCD_E       PORTA, 1    ; LCD E clock
//    #define LCD_RW      PORTA, 2    ; LCD read/write line
//    #define LCD_RS      PORTA, 3    ; LCD register select line
//
//    #define LCD_E_DIR   TRISA, 1
//    #define LCD_RW_DIR  TRISA, 2
//    #define LCD_RS_DIR  TRISA, 3

#define LCD_INS     0               //! instruction
#define LCD_DATA    1               //! data

void lcdLine1(void);    //!set cursor to start of line 1 (upper)
void lcdLine2(void);    //!set cursor to start of line 2 (lower)
void d_Write(void);     //!Writes the 8-bit data found in temp_wr to the LCD data register AND to serial port.
void i_Write(void);     //!Writes the 8-bit data found in temp_wr to the LCD instruction register.
void lcdInit(void);     //!Initialises the LCD display to 4-bit bus, 2 lines 5x8 font, display on, cursor off, blink on, increment cursor and don't shift display, clear display and place the cursor at start of line 1.
void lcdWrite(char *jessicat);  //!Writes the 8-bit data found in temp_wr to LCD
void lcdBusy(void);     //!Reads the LCD busy flag
void lcdRead(void);     //!Read data byte from LCD
void lcdWriteNibble(char *betelgeuse);  //!Write nibble to LCD
void delayXCycles(char delay);

/* **********************************************************************
 * Function: config(void)
 *
 * Include: LCD.h
 *
 * Description: Configures the LCD for use, and puts it in its default state
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configLCD(void)
{
    
}

<<<<<<< HEAD

void lcdLine1(void){}
void lcdLine2(void){}
void d_Write(void){}
void i_Write(void){}
void lcdInit(void){}
void lcdWrite(char *jessicat){}
void lcdBusy(void){}
void lcdWriteNibble(char *betelguese){}
void lcdRead(void){}
void delayXCycles(char delay){}
=======
/*! **********************************************************************
 * Function: displayLCD(char *string)
 *
 * Include: LCD.h
 *
 * Description: Displays the given string on the LCD
 *
 * Arguments: string - pointer to the data to display
 *
 * Returns: None
 *************************************************************************/
void displayLCD(char *string)
{
    
}
>>>>>>> 6d2f10e32723cb638cc08e215c543e8a6e3044ad
