/* 
 * File:   LCD.h
 * Author: Grant
 *
 * Description: Contains the public interface for the LCD module.
 *
 * Created on 17 September 2014, 9:01 PM
 */

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef LCD_H

//External declarations of public access functions
extern void configLCD(void);
extern void displayLCD(char *string);

#define LCD_H
#endif