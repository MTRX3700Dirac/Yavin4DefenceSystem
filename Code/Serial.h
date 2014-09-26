/* 
 * File:   Serial.h
 * Author: Grant
 *
 * Created on 17 September 2014, 3:27 PM
 */

//Serial interrupt flag
//#define SERIAL_INT (TX_INT || RC_INT)
#define SERIAL_INT 0

//External declarations of public functions
extern void configureSerial(void);
extern void serialISR(void);
extern void transmit(char *string);
extern char receiveEmpty(void);
extern char receivePeek(void);
extern char receivePop(void);


