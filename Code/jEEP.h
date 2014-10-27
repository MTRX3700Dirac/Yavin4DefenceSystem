/* 
 * File:   jEEP.h
 * Author: Jacob
 *
 * Created on 27 October 2014, 3:24 PM
 */

#define EEPADDRESS 0x00

extern void sendEep(int number, int address);
extern int readEep(int address);

