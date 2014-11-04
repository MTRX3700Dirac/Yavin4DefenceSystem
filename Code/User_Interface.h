/*******************************************************************************
 * File:   User_Interface.h
 * Author: Grant
 *
 * Description: Contains the public interface for the User_Interface module
 *
 * Created on 15 September 2014, 1:20 PM
 ******************************************************************************/

//#include "Common.h"

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef USER_H

//User interface related interrupts
#define USER_INT (RB_INT || INT0_INT || INT1_INT )
#define CONFIRM_CHAR 0x0D
#define BACK_CHAR 0x1B

/*============================================================================*/
//Public function external declarations
/*============================================================================*/

/*! **********************************************************************
 * Function: display(TrackingData data)
 *
 * Include: User_Interface.h
 *
 * Description: displays the current tracking information
 *
 * Arguments: data - Struct which contains all known data concerning the
 *                   The position of the target. A Range of 0 indicates
 *                   that no target was observed.
 *
 * Returns: None
 *************************************************************************/
extern void display(TrackingData data);

/*! **********************************************************************
 * Function: userISR(void)
 *
 * Include: User_Interface.h
 *
 * Description: Acts as the ISR for the User_interface module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void userISR(void);

/*! **********************************************************************
 * Function: configUSER(void)
 *
 * Include: User_Interface.h
 *
 * Description: Configures the user interface for use
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void configUSER(void);


/*! **********************************************************************
 * Function: userEmpty(void)
 *
 * Include: User_Interface.h
 *
 * Description: returns non-zero if the user interface buffer is empty (i.e.
 *              no user input has been detected)
 *
 * Arguments: None
 *
 * Returns: if the user input buffer is empty
 *************************************************************************/
extern char userEmpty(void);

/*! **********************************************************************
 * Function: userPop(void)
 *
 * Include: User_Interface.h
 *
 * Description: pops a character from the user interface receive buffer
 *
 * Arguments: None
 *
 * Returns: a character poped from the user Interface buffer
 *************************************************************************/
extern char userPop(void);

/*! **********************************************************************
 * Function: userPeek(void)
 *
 * Include: User_Interface.h
 *
 * Description: returns a character in the user_Interface buffer without
 *              removing it from the buffer
 *
 * Arguments: None
 *
 * Returns: a character in the user interface buffer
 *************************************************************************/
extern char userPeek(void);

/*! **********************************************************************
 * Function: readDial(void)
 *
 * Include:
 *
 * Description: Read the position of the dial by splitting the value
 *              returned from the ADC into even discrete steps based on the
 *              given argument. For instance, an input of 7 will return
 *              a value from 0 to 7 based on the value found from the potentiometer
 *
 * Arguments: int max - The number of maximum state to split values into
 *
 * Returns: The dial position scaled by the maximum number
 *************************************************************************/
extern unsigned int readDial(unsigned int max);

#define USER_H
#endif