/************************************************************ 
The contents of this file are subject to the Pumpkin Salvo
License (the "License").  You may not use this file except
in compliance with the License. You may obtain a copy of
the License at http://www.pumpkininc.com, or from
warranty@pumpkininc.com.

Software distributed under the License is distributed on an
"AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express
or implied. See the License for specific language governing
the warranty and the rights and limitations under the
License.

The Original Code is Salvo - The RTOS that runs in tiny
places(TM). Copyright (C) 1995-2002 Pumpkin, Inc. and its
Licensor(s). All Rights Reserved.

$Source: C:\\RCS\\d\\salvo\\inc\\portiar18.h,v $
$Author: aek $
$Revision: 3.15 $
$Date: 2003-06-25 12:21:00-07 $

Porting file for IAR Systems PIC18 C compiler.

************************************************************/

#include <io18c452.h>
#include <inpic18.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* interrupt control depends on OSPIC18_INTERRUPT_MASK.	*/
#if   ( OSPIC18_INTERRUPT_MASK == 0xC0 ) || \
      ( OSPIC18_INTERRUPT_MASK == 0x80 ) || \
      ( OSPIC18_INTERRUPT_MASK == 0x40 ) || \
      ( OSPIC18_INTERRUPT_MASK == 0x00 )
      
#if !defined(OSDi)
#define OSDi() 							do { INTCON &= ~OSPIC18_INTERRUPT_MASK; \
                                        } while (0)
#endif
#if !defined(OSEi)
#define OSEi() 							do { INTCON |=  OSPIC18_INTERRUPT_MASK; \
                                        } while (0)
#endif   
                                     
#if   ( OSPIC18_INTERRUPT_MASK == 0x00 )
#warning A value of 0x00 for OSPIC18_INTERRUPT_MASK is incompatible with interrupts. 
#endif
                                    
#else
#error portiar18.h: Invalid OSPIC18_INTERRUPT_MASK value.
#endif


/* Unfortunately we cannot use IAR PIC18's __monitor    */
/*  keyword for two reasons:                            */
/*  1) IAR PIC18C currently (as of v2.10A) has a bug    */
/*   with the __monitor keyword, in that it doesn't pop */
/*   the parameter stack in the right order, and so     */
/*   interrupts are not restored properly.              */
/*  2) The __monitor keyword only affects the GIE/GIEH  */
/*   bit. This means that it cannot be used in cases    */
/*   where IPEN is set to 1 (high/low priority scheme)  */
/*   and the user wishes to call Salvo services from    */
/*   low (and optionally, from high) interrupt level.   */
/* Therefore we have to roll our own scheme for saving  */
/*  interrupt status on entry and restoring it on exit  */
/*  -- see portc18.c.                                   */
/* NOTE: Leave OSMONITOR_KEYWORD_XYZ undefined!         */
#if !defined(OSEnterCritical)
extern void OSSaveIntStat(void);
#define OSEnterCritical()               OSSaveIntStat()
#endif

#if !defined(OSLeaveCritical)
extern void OSRestoreIntStat(void);
#define OSLeaveCritical() 				OSRestoreIntStat()
#endif

        
/* OSResume|SuspendCriticalSection() follow the "usual"	*/
/*  pattern, but must be explicitly defined to avoid    */
/*  the OSSave|RestoreIntStat() actions in 				*/
/*  OSEnter|LeaveCritical()								*/
#if !defined(OSResumeCriticalSection)
#define OSResumeCriticalSection()  		do { OSDi(); \
                                             OSDiHook(); \
                                   		} while(0) 
#endif                                   		

#if !defined(OSSuspendCriticalSection)
#define OSSuspendCriticalSection() 		do { OSEiHook(); \
                                             OSEi(); \
                                   		} while (0)
#endif                                   		 

 
/* should work fine. 									*/
#define OSUSE_MEMSET                    TRUE


/* printf() supports p (pointer) format. 				*/
#define OSUSE_PRINTF_P_FORMAT			TRUE


/* Force this to avoid any unintentional problems. If   */
/*  the user builds with the static overlay code model, */
/*  they'll get an 'argument of type "void (*)(void)"   */
/*  is incompatible with parameter of type "OStypeTFP"' */
/*  compiler error.                                     */
#define OSTASK_POINTER_TYPE				__stack_func


/* Watchdog reset                                        */
#define OSCLEAR_WATCHDOG_TIMER()        __clear_watchdog_timer()

/************************************************************ 
****                                                     ****
**                                                         **
Notes 

1. OSCtxSw() is in portc18.c. 

2. IAR PIC18 C is fully preemptive by default, so we always
preserve the interrupt mask. However, we must use OSSave|
RestoreInstStat() (in portc18.c) because of a variety of
reasons (see above).

**                                                         **
****                                                     ****
************************************************************/
