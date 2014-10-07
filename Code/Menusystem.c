#include "Common.h"
#include "Serial.h"
#include "Menusystem.h"

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


void menu(char menuselect){
    
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