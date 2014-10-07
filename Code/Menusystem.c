#include "Common.h"
#include "Serial.h"
#include "User_Interface.h"

#define width 80
#define height 24

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

void menu(void);
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
    //display menu via serial
    topmenudisp();
    //wait for/get serial input
    //make decision based on input

    while(e){
        e=receiveEmpty();
    }

    readString(userget);
    transmit(userget);
}

void menu(void){
    //setup();
    configureSerial();
    topmenu();
    //while(1){}
    //get pointer to menu level(vertical)
    //get pointer to menu option(horizontal)
    //call correct subroutine for menu
    //remain in that menu as dictated by operation
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