#include "Common.h"

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
    //display menu via serial
    topmenudisp();
    //wait for/get serial input
    //make decision based on input
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



