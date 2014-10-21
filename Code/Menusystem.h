/*! ****************************************************************************
 * File:   Menusystem.h
 * Author: Jacob
 *
 * Created on 7 October 2014, 9:56 PM
 ******************************************************************************/

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef MENU_H

#define MENU_ISR 0

extern void initialiseMenu(void);
extern void serviceMenu(void);
extern void menuISR(void);

extern void menu(void);

#define MENU_H
#endif