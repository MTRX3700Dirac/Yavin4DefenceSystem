/*
 * File:   User_Interface.h
 * Author: Grant
 *
 * Description: Contains the public interface for the User_Interface module
 *
 * Created on 15 September 2014, 1:20 PM
 */

//#include "Common.h"

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef USER_H

//User interface related interrupts
#define USER_INT (RB_INT || INT0_INT || INT1_INT )
#define CONFIRM_CHAR 0x0D
#define BACK_CHAR 0x1B

//Public function external declarations
extern void display(TrackingData data);
extern void userISR(void);
extern void configUSER(void);

extern char userEmpty(void);
extern char userPop(void);
extern char userPeek(void);
extern unsigned int readDial(unsigned int max);
extern unsigned int readDialForSelect(unsigned int max, unsigned int min, unsigned char binstep);

#define USER_H
#endif