/*! ****************************************************************************
 * File:   LCD.h
 * Author: Grant
 *
 * Description:
 * Contains the public interface for the LCD module.
 *
 * Created on 17 September 2014, 9:01 PM
 ******************************************************************************/

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef LCD_H

//External declarations of public access functions
extern void lcdWriteString(char *string, char line);   //!Feed character string, and line (1 or 2)
extern void lcdWriteChar(char byte, char line, char column);    //!Feed character, line (1 or 2), and column(1-16)
extern void lcdInit(void);                //initialize

#define LCD_H
#endif