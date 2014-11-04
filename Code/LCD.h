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

/*============================================================================*/
//External declarations of public access functions
/*============================================================================*/

/*! **********************************************************************
 * Function: lcdWriteString(char *string, unsigned char line)
 *
 * \brief
 *
 * Include: LCD.h
 *
 * Description: Writes a string to the LCD at the given line
 *
 * Arguments: string - The string to write
 *            line - the line to write to
 *
 * Returns: None
 *************************************************************************/
extern void lcdWriteString(char *string, char line);   //!Feed character string, and line (1 or 2)

/*! **********************************************************************
 * Function: lcdWriteChar(unsigned char byte, unsigned char line, unsigned char column)
 *
 * \brief
 *
 * Include: LCD.h
 *
 * Description: Writes a character to the LCD at a given location
 *
 * Arguments: byte - byte to write
 *            line - line to wrtie to
 *            column - column to write in
 *
 * Returns: None
 *************************************************************************/
extern void lcdWriteChar(char byte, char line, char column);    //!Feed character, line (1 or 2), and column(1-16)

/*! **********************************************************************
 * Function: confiigLCD(void)
 *
 * \brief Initialises the LCD so that it can be used
 *
 * Include: LCD.h
 *
 * Description: Initialises the LCD hardware so that data can be displayed
 *              on the LCD in local interface mode
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void configLCD(void);                //initialize

#define LCD_H
#endif