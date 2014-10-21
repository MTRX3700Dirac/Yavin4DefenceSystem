/* 
 * File:   Serial.h
 * Author: Grant
 *
 * Description:
 * Contains the public interface for the serial module. This file contains
 * all the external declarations, macros and global variables for using and
 * Interfacing with the serial module.
 *
 * Created on 17 September 2014, 3:27 PM
 */

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef SERIAL_H

//Serial interrupt flag
#define SERIAL_INT (TX_INT || RC_INT)

//External declarations of public functions
extern void configureSerial(void);
extern void serialISR(void);

//Transmit functions:
extern void transmit(char *string);
extern char transmitted(void);
extern void transChar(char c);

//Receive functions:
extern char receiveEmpty(void);
extern char receivePeek(void);
extern char receivePop(void);
extern char receiveCR(void);
extern void readString(char *string);

#define SERIAL_H
#endif