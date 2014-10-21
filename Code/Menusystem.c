/*!******************************************************************************
 * File:   Menusystem.c
 * Author: 
 *
 * Description:
 *
 * Duties:
 *
 * Functions:
 *
 * Created on 16 September 2014, 6:47 PM
 *******************************************************************************/

#include "Common.h"
#include "Serial.h"
#include "User_Interface.h"

#define width 80
#define height 24

#define top1 0xFF
#define auto11 0x10
#define manu12 0x20
#define manugoto121 0x21
#define manusetl122 0x22
#define manushow123 0x23
//#define manugoup124 0x24
#define stat13 0x30
#define swap14 0x40
#define slee15 0x50

//Global
char tMESSAGE[] = "Hello 123\n";
char fillerthing[] = "+";
char newline[] = "\n";
char choose[] = "\tPlease select your option (eg. 2): \n";
char goup[] = "\tUp a level\n";
//

//1: Top
char welcome[] = "Welcome to Yavin IV Defence System";
char topoption1[] = "\t1:\tAutomatic Tracking\n";
char topoption2[] = "\t2:\tManual Tracking\n";
char topoption3[] = "\t3:\tStatus\n";
char topoption4[] = "\t4:\tGo To Local Mode\n";
char topoption5[] = "\t5:\tSleep\n";
//

void menu(char menuselect);
void topmenu(void);
void topmenudisp(void);
void disptoptions(void);
void clearscreen(char length);
void filler(char length);

void clearscreen(char length){
    while(length){
        transmit(newline);
        length--;
    }
}

void filler(char length){
    while(length){
        transmit(fillerthing);
        length--;
    }
}

void disptoptions(void){
    transmit(topoption1);
    transmit(topoption2);
    transmit(topoption3);
    transmit(topoption4);
    transmit(topoption5);
}

void topmenudisp(void){
    clearscreen(height);
    filler(width);
    transmit(newline);
    filler(23);
    transmit(welcome);
    filler(23);
    transmit(newline);
    filler(width);
    transmit(newline);
    clearscreen(2);
    disptoptions();
    clearscreen(2);
    transmit(choose);
    clearscreen((height-14));
    filler(width);
}

void topmenu(void){
    char e;
    char userget;
    e=1;
    
    topmenudisp();      //!Display the menu screen via serial
                        //!wait for/get serial input
                        //!make decision based on input

    while(e){
        e=receiveEmpty();   //!Wait until the receive buffer is no longer empty
    }                       //!Indicating that a command has been passed
    e=1;                    //!Reset status flag

    readString(userget);    //!Get the input string and store it in @userget
    transmit(userget);      //!test

    switch(userget){
        case 1 :
            //auto();
            break;
        case 2 :
            //manual();
            break;
        case 3 :
            //status();
            break;
        case 4 :
            //swapmode();
            break;
        case 5 :
            //sleep();
            break;
        default :
            //error();
            break;
    }
}

/*! **********************************************************************
 * Function: initialiseMenu(void)
 *
 * \brief Initialises the menu system
 *
 * Include: Menusystem.h
 *
 * Description: initialises the menu system so that it is fully operational
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void initialiseMenu(void)
{
    configureSerial();
    configLCD();
    configUSER();
}

/*! **********************************************************************
 * Function: serviceMenu(void)
 *
 * \brief services any user interface with the menu
 *
 * Include:
 *
 * Description: Checks if the user has made any inputs to the system. If not
 *              the function simply returns. If they have then it services
 *              the inputs, displays the correct outputs and performs the
 *              specified actions
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void serviceMenu(void)
{
    //Return if there is no user input
    if (receiveEmpty() && userEmpty()) return;
}

/*! **********************************************************************
 * Function: menuISR(void)
 *
 * \brief ISR function for the menu subsystem
 *
 * Include: Menusystem.h
 *
 * Description: services any interrupts associated with the menu system
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void menuISR(void)
{
    
}
    
void menu(char menuselect)
{
    
    configureSerial();      //!Call the serial configuration to enable USART Subsysten

    switch(menuselect){
        case top1 :
            topmenu();
            break;
        case auto11 :
            //auto();
            break;
        case manu12 :
            //manual();
            break;
        case stat13 :
            //status();
            break;
        case swap14 :
            //swapmode();
            break;
        case slee15 :
            //sleep();
        case manugoto121 :
            //manopt1();
        case manusetl122 :
            //manopt2();
        case manushow123 :
            //manopt3();
        default :
            //error();
            break;
    }
}