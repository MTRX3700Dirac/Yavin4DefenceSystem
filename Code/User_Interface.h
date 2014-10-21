/* 
 * File:   User_Interface.h
 * Author: Grant
 *
 * Description: Contains the public interface for the User_Interface module
 *
 * Created on 15 September 2014, 1:20 PM
 */

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef USER_H

//User interface related interrupts
//#define USER_INT (RB_INT || INT0_INT)
#define USER_INT 0

//Public function external declarations
extern void display(TrackingData data);
extern void userISR(void);
extern void configUSER(void);

extern char userEmpty(void);
extern char userPop(void);
extern char userPeek(void);

#define USER_H
#endif