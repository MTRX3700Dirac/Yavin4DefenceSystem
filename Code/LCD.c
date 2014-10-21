
#include "Common.h"
#include "LCD.h"
#include "LCD_defs.h"

void lcdInit(void){

    delay(15);

    LCD_DATA_LINE_DIR = LCD_OUTPUT; //! Set data lines to output

    //LCD_PWR_DIR = LCD_PIN_OUTPUT;    //!Set control lines to output
    LCD_RS_DIR  = LCD_PIN_OUTPUT;
    LCD_RW_DIR  = LCD_PIN_OUTPUT;
    LCD_E_DIR   = LCD_PIN_OUTPUT;

    //LCD_PWR = LCD_ON;               //!Enable power
    LCD_E   = LCD_CLKLOW;           //!Set control lines low
    LCD_RS = LCD_INS;
    LCD_RW = LCD_WRITE;

    lcdWrite((SETDISPFXN | DL_8BIT | N_2LINE | F_5X7DOT), LCD_INS);   //! 8 bits, 2 lines, 5x7 dots, 0x38
    delay(2);
    lcdWrite((DISPOPT | D_DISPON | C_CURSOFF | B_BLINKON), LCD_INS);  //! Display on, cursor off, blinking on (Z, 0x0F)
    lcdWrite((SETENTRYMODE | ID_CURSL | SH_DISPNSHIFT), LCD_INS);     //! Cursor moves right?, display not shift (Z, 0x04)
    lcdWrite((DISPCLR), LCD_INS);                                     //! Clear display
    delay(15);
}

char lcdBusy(void){

    //LCD_PWR_DIR = LCD_PIN_OUTPUT;       //! Set control lines to output
    LCD_RS_DIR  = LCD_PIN_OUTPUT;
    LCD_RW_DIR  = LCD_PIN_OUTPUT;
    LCD_E_DIR   = LCD_PIN_OUTPUT;

    LCD_DATA_LINE_DIR = LCD_INPUT;      //! Set data lines to input

    LCD_E   = LCD_CLKLOW;               //!Set the enable low, ensure clock signal is low
    LCD_RW  = LCD_READ;                 //!Set RW to read read from LCD
    LCD_RS  = LCD_INS;                  //!Set the register select to low for instruction

    LCD_E   = LCD_CLKHGH;               //!Set the enable high, ensure clock signal is high to allow data transmission
    delay(2);

    if(LCD_D7 == BF_BUSY){
        LCD_E_DIR   = LCD_PIN_OUTPUT;   //!Set control lines to output
        LCD_RW_DIR  = LCD_PIN_OUTPUT;
        LCD_RS_DIR  = LCD_PIN_OUTPUT;

        LCD_DATA_LINE_DIR = LCD_OUTPUT; //! Set data lines to output

        LCD_E = LCD_CLKLOW;              //!Set enable low to allow data to flow through
        return 1;
    }

    else {
        LCD_E_DIR   = LCD_PIN_OUTPUT;   //!Set control lines to output
        LCD_RW_DIR  = LCD_PIN_OUTPUT;
        LCD_RS_DIR  = LCD_PIN_OUTPUT;

        LCD_DATA_LINE_DIR = LCD_OUTPUT; //! Set data lines to output

        LCD_E = LCD_CLKLOW;              //!Set enable low to allow data to flow through
        return 0;
    }
}


void delay(unsigned int t)  //delay 1 ms
{
    while(t!=0){t--;}
    t=100;
    while(t!=0){t--;}
}

void lcdWrite(unsigned char byte, unsigned char mode){
    while(lcdBusy()){}
    LCD_DATA_LINE_DIR = LCD_OUTPUT; //! Set data lines to output

    LCD_RW = LCD_WRITE;
    LCD_RS = mode;

    LCD_DATA_LINE = byte;     //! Write data to data lines
    delay(2);

    LCD_E = LCD_CLKHGH;  //! Set clock high
    LCD_E = LCD_CLKLOW;  //! Set clock low
}

//!Feed character string, and line (1 or 2)
void lcdWriteString(char *string, unsigned char line){
    unsigned char row;
    if(line==1){row=LINE1;}
    else(row=LINE2);
    while((row & LINESTART) <= LINEEND){
        lcdWrite((SETDDRAMADD | line++), LCD_INS);
        lcdWrite((*string)++, LCD_DATA);
        delay(5);
    }
}

//!Feed character, line (1 or 2), and column(1-16)
void lcdWriteChar(unsigned char byte, unsigned char line, unsigned char column){
    unsigned char row;
    if(line==1){row=LINE1;}
    else(row=LINE2);
    lcdWrite((SETDDRAMADD | row | column), LCD_INS);
    lcdWrite(byte, LCD_DATA);
    delay(5);
}