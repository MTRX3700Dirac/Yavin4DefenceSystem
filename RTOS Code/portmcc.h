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

$Source: C:\\RCS\\d\\salvo\\inc\\portmcc.h,v $
$Author: aek $
$Revision: 3.13 $
$Date: 2003-06-25 12:20:57-07 $

Porting file for Microchip MPLAB-C18.

************************************************************/

#if OSMAKE_LIBRARY
#include <p18c452.h>
#else
#include <p18cxxx.h>
#endif
//#include <stdarg.h> /* not working in v2.2 */
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
#error portmcc.h: Invalid OSPIC18_INTERRUPT_MASK value.
#endif


/* MPLAB-C18 is stack-based and keeps both a frame		*/
/*  pointer (FSR2) and a stack pointer (FSR1).          */
/*  Therefore we can save interrupt status directly to  */
/*  the stack without fear of messing up arguments and  */
/*  auto variables.                                     */
#undef  OSEnterCritical
#define OSEnterCritical()               do { \
                                          WREG = INTCON & OSPIC18_INTERRUPT_MASK; \
                                          POSTINC1 = WREG; \
                                          OSDi(); \
                                        } while (0)

/* restore GIEH and/or GIEL.                            */
#undef  OSLeaveCritical

/* works for smaller stacks -- faster because only      */
/*  FSR1L is used ...                                   */
#if OSMPLAB_C18_STACK_SIZE <= 256
#define OSLeaveCritical()               do { \
                                          FSR1L--; \
                                          INTCON &= ~OSPIC18_INTERRUPT_MASK; \
                                          INTCON |= INDF1; \
                                        } while (0)
#else
/* default -- works with all stack sizes, but involves  */
/*  all of FSR1.                                        */
#define OSLeaveCritical()               do { \
                                          FSR1--; \
                                          INTCON &= ~OSPIC18_INTERRUPT_MASK; \
                                          INTCON |= INDF1; \
                                        } while (0)
#endif                                        


/* OSResume|SuspendCriticalSection() follow the "usual"	*/
/*  pattern, but must be explicitly defined to avoid    */
/*  the stack actions in OSEnter|LeaveCritical()		*/
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

 
/* unknown.          									*/
#define OSUSE_MEMSET                    FALSE


/* no printf() (yet).                   				*/
#define OSUSE_PRINTF_P_FORMAT			FALSE


/* Watchdog reset                                       */
#define OSCLEAR_WATCHDOG_TIMER()        ClrWdt()

/************************************************************ 
****                                                     ****
**                                                         **
Notes 

1. OSCtxSw() is in portc18.c. 

2. MPLAB-C18 is fully preemptive by default, so we always
preserve the interrupt mask.

3. OSEnterCritical() works by pushing GIE and/or PEIE onto 
the software stack, then disabling appropriate interrupt
sources. OSLeaveCritical() works by pulling the saved 
interrupt status off the stack and overwriting INTCON's GIE
and/or PEIE with it. If you need to control & preserve 
interrupts differently, then create your own OSDi|Ei() and 
OSEnter|LeaveCritical() macros.

4. OSTASK_POINTER_TYPE is unnecessary because OStypeTFP is
implicitly set by chosen memory model (small or large).

    
**                                                         **
****                                                     ****
************************************************************/
