/* 
 * File:   Menusystem.h
 * Author: Jacob
 *
 * Created on 7 October 2014, 9:56 PM
 */

#define MENU_ISR 0

extern void initialiseMenu(void);
extern void serviceMenu(void);
extern void menuISR(void);

<<<<<<< HEAD
extern void menu(char menuselect);

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
=======
extern void menu(void);

#define MENU_H
>>>>>>> 6d2f10e32723cb638cc08e215c543e8a6e3044ad
