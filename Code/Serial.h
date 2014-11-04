/*! ****************************************************************************
 * File:   Serial.h
 * Author: Grant
 *
 * Description:
 * Contains the public interface for the serial module. This file contains
 * all the external declarations, macros and global variables for using and
 * Interfacing with the serial module.
 *
 * Created on 17 September 2014, 3:27 PM
 ******************************************************************************/

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef SERIAL_H

//Serial interrupt flag
#define SERIAL_INT (TX_INT || RC_INT)

/*===========================================================================*/
//External declarations of public functions
/*===========================================================================*/

/*! **********************************************************************
 * Function: configureSerial(void)
 *
 * Include: Serial.h
 *
 * Description: Configures the serial ready for communication
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void configureSerial(void);

/*! **********************************************************************
 * Function: serialISR(void)
 *
 * Include: Serial.h
 *
 * Description: Acts as the interrupt service routine for the serial module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void serialISR(void);

/*=======================================================================*/
//Transmit functions:
/*=======================================================================*/

/*! **********************************************************************
 * Function: transmit(char *string)
 *
 * Include: Serial.h
 *
 * Description: Begins transmitting the string over serial (interrupt driven)
 *
 * Arguments: string - pointer to the beginning of the string to transmit
 *
 * Returns: None
 *
 * NOTE: Must be Null Terminated! Cannot receive a literal.
 *************************************************************************/
extern void transmit(char *string);

/*! **********************************************************************
 * Function: transmitComplete(void)
 *
 * Include: Serial.h
 *
 * Description: returns non-zero if the message has been completely transmited
 *              e.g. if the transmit buffer is empty
 *
 * Arguments: None
 *
 * Returns: non-zero if all messages have been transmitted
 *************************************************************************/
extern char transmitComplete(void);

/*! **********************************************************************
 * Function: transChar(char c)
 *
 * Include: Serial.h
 *
 * Description: Transmits a single character
 *
 * Arguments: c - character to transmit
 *
 * Returns: None
 *************************************************************************/
extern void transChar(char c);

/*=======================================================================*/
//Receive functions:
/*=======================================================================*/

/*! **********************************************************************
 * Function: receiveEmpty(void)
 *
 * Include: Serial.h
 *
 * Description: Indicates if the receive buffer is empty
 *
 * Arguments: None
 *
 * Returns: returns true if the recieve buffer is empty
 *************************************************************************/
extern char receiveEmpty(void);

/*! **********************************************************************
 * Function: receivePeek(void)
 *
 * Include: Serial.h
 *
 * Description: Returns the next character in the receive buffer without
 *              removing it from the buffer
 *
 * Arguments: None
 *
 * Returns: The next received character
 *************************************************************************/
extern char receivePeek(void);

/*! **********************************************************************
 * Function: receivePop(void)
 *
 * Include: Serial.h
 *
 * Description: Pops the next received character from the received buffer
 *
 * Arguments: None
 *
 * Returns: The next character from the receive buffer
 *************************************************************************/
extern char receivePop(void);

/*! **********************************************************************
 * Function: receiveCR(void)
 *
 * Include: Serial.h
 *
 * Description: Indicates whether a Carriage Return has been received
 *
 * Arguments: None
 *
 * Returns: non-zero if CR has been received, zero otherwise
 *************************************************************************/
extern char receiveCR(void);

/*! **********************************************************************
 * Function: receiveEsc(void)
 *
 * Include:
 *
 * Description: Indicates whether an Escape character has been received
 *
 * Arguments: None
 *
 * Returns: non-zero if the Esc has been received, zero otherwise
 *************************************************************************/
extern char receiveEsc(void);

/*! **********************************************************************
 * Function: readString(char *string)
 *
 * Include: Serial.h
 *
 * Description: Writes all received data up to a carriage return into given
 *              location.
 *
 * Arguments: string - Pointer to location to store received data
 *
 * Returns: Received data including the carriage return
 *
 * Remarks: Make sure that you reserve at least BUFFERLENGTH elements at the
 *          location pointed to by string before calling this function.
 *************************************************************************/
extern void readString(char *string);

/*! **********************************************************************
 * Function: popEsc(void)
 *
 * Include:
 *
 * Description: Processes the Esc command and removes any input before the
 *              Esc command.
 *
 * Arguments: None
 *
 * Returns: Non-zero if received escape character
 *************************************************************************/
extern void popEsc(void);

/*! **********************************************************************
 * Function: clearReceive(void)
 *
 * Include: Serial.h
 *
 * Description: Clears the receive buffer
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void clearReceive(void);

#define SERIAL_H
#endif