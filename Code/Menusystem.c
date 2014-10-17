#include "Common.h"
#include "Serial.h"
#include "User_Interface.h"
<<<<<<< HEAD
#include "Menusystem.h"
=======

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
>>>>>>> 6d2f10e32723cb638cc08e215c543e8a6e3044ad

//Global
const static rom char tMESSAGE[] = "Hello 123\n";
const static rom char fillerthing[] = "+";
const static rom char newline[] = "\n";
const static rom char choose[] = "\tPlease select your option (eg. 2): \n";
const static rom char goup[] = "\tUp a level\n";
//

//1: Top
const static rom char welcome[] = "Welcome to Yavin IV Defence System";
const static rom char topoption1[] = "\t1:\tAutomatic Tracking\n";
const static rom char topoption2[] = "\t2:\tManual Tracking\n";
const static rom char topoption3[] = "\t3:\tStatus\n";
const static rom char topoption4[] = "\t4:\tGo To Local Mode\n";
const static rom char topoption5[] = "\t5:\tSleep\n";
//

//1.1: Auto
const static rom char automessage[] = "Automatic Tracking Mode";
const static rom char autoinit[] = "\tInitialising Automatic Tracking...";
const static rom char autohelp1[] = "\tEnter any key to end session";
//const static rom char autohelp2[] = "\tRange, Elevation, Azimuth and Tracking";
//const static rom char autohelp3[] = " Status will be displayed every X seconds:";
const static rom char autogo[] = "\t3...\n\t2...\n\t1...\n";
const static rom char autorange[] = "\tRange:\t";
const static rom char autoeleva[] = "\tElevation:\t";
const static rom char autoazimu[] = "\tAzimuth:\t";
const static rom char autostatu[] = "\tTarget Status:\t";
const static rom char autoend[] = "Tracking Session Terminated";
//

//1.3: Status
const static rom char statmessage[] = "Display Target Status";
const static rom char statopt1[] = "\t1:"; //go up
const static rom char stattargety[] = "\tTarget Acquired:\t";
const static rom char stattargetn[] = "\tNo Target:\t";
const static rom char statrange[] = "Range:";
const static rom char statazimu[] = "Azimuth:";
const static rom char stateleva[] = "Elevation:";
const static rom char stattempe[] = "Temperature:";
//

void menu(char menuselect);
void topmenu(void);
void topmenudisp(void);
void disptoptions(void);
void clearscreen(char length);
void filler(char length);
void autodisp(void);
void send(const static rom char *romchar);

void send(const static rom char *romchar){
    auto char temp[];
    strcpypgm2ram(temp, romchar);
    transmit(temp);
}

void clearscreen(char length){
    while(length){
        send(newline);
        length--;
    }
}

void filler(char length){
    while(length){
        send(fillerthing);
        length--;
    }
}

void disptoptions(void){

    send(topoption1);
    send(topoption2);
    send(topoption3);
    send(topoption4);
    send(topoption5);
}

void topmenudisp(void){
    clearscreen(height);
    filler(width);
    send(newline);
    filler(23);
    send(welcome);
    filler(23);
    send(newline);
    filler(width);
    send(newline);
    clearscreen(2);
    disptoptions();
    clearscreen(2);
    send(choose);
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
    send(userget);      //!test

    switch(userget){
        case 1 :
            //auto();
            send(userget);
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

void autodisp(void){
    clearscreen(height);
    filler(width);
    send(newline);
    filler(23);
    send(automessage);
    filler(23);
    send(newline);
    filler(width);
    send(newline);
    clearscreen(2);
    send(autoinit);
    clearscreen(2);
    send(autohelp1);
    send(newline);
    //send(autohelp2);
    //send(autohelp3);

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