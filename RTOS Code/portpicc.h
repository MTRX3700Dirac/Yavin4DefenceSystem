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

$Source: C:\\RCS\\d\\salvo\\inc\\portpicc.h,v $
$Author: aek $
$Revision: 3.7 $
$Date: 2003-06-25 12:21:00-07 $

Porting file for HI-TECH PIC C compiler.

************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>


#if OSTARGET == OSPIC12 || OSTARGET == OSPIC16 || OSTARGET == OSPIC17
#include <pic.h>
#elif OSTARGET == OSPIC18
#include <pic18.h>
#endif


#if OSTARGET == OSPIC12

/* 12-bit PICmicros don't support interrupts. */
#if !defined(OSDi)
#define OSDi()
#endif

#if !defined(OSEi)
#define OSEi()
#endif

/* PIC C uses compile-time gotos to simulate call...return */
/*  stack, so Salvo context switcher must be slightly      */
/*  different to accomodate this scheme.                   */
/* the global asm directive is required for context        */
/*  switchers (in other modules) to be able to see the     */
/*  OSSchedRtn label where it's declared via OSSCHED_-     */
/*  RETURN_LABEL. In this case, "global" is like "extern"  */
/*  in the context switcher, but is like "global" where    */
/*  the label is declared.                                 */
/* ljmp is an additional PIC C mnemonic which does the     */
/*  corect page-bit setting to ensure a proper goto-like   */
/*  jump.                                                  */
/* resetting of FSR is a required hack. PICC isn't taking  */
/*  account of the fact that tasks are "jumped into" when  */
/*  resumed, and operations on FSR bit 5 (RAM banking) are */
/*  being optimized out in error. Since the default bank   */
/*  is RAM bank 0, this should work for all cases.         */
#define OSCTXSW_METHOD                  OSRTNADDR_IS_PARAM
 
#define OSRtnToOSSched()                do { asm("global _OSSchedRtn"); \
                                          asm("ljmp _OSSchedRtn"); \
                                        } while (0)
  
#define OS_Yield(label)                 do { OSSaveRtnAddr(label); \
                                          OSRtnToOSSched(); \
                                          asm("_" _OSMkstr(label) ":"); \
                                          FSR &= ~0x20; \
                                        } while (0)
 
#define OSSCHED_RETURN_LABEL()          do { asm("global _OSSchedRtn"); \
                                           asm("_OSSchedRtn:"); \
                                        } while (0)


#elif OSTARGET == OSPIC16

/* these chips (definitely the first in the series, often  */
/*  the A and B parts, too) have a problem when interrupts */
/*  are disabled AND an interrupt occurs while that's      */
/*  happening. In that case, the RETFIE re-enables         */
/*  interrupts, which is a REALLY BAD THING.               */
#if !defined(OSDi)
#if    defined(_14000)  \
    || defined(_16C61)  \
    || defined(_16C62)  \
    || defined(_16C62A) \
    || defined(_16C62B) \
    || defined(_16CR62) \
    || defined(_16C63)  \
    || defined(_16C63A) \
    || defined(_16CR63) \
    || defined(_16C64)  \
    || defined(_16C64A) \
    || defined(_16CR64) \
    || defined(_16C65)  \
    || defined(_16C65A) \
    || defined(_16C65B) \
    || defined(_16CR65) \
    || defined(_16C71)  \
    || defined(_16C73)  \
    || defined(_16C73A) \
    || defined(_16C73B) \
    || defined(_16C74)  \
    || defined(_16C74A) \
    || defined(_16C74B)
#define OSDi()                          do { GIE = 0; } while ( GIE == 1 ) 
#else
#define OSDi()                          GIE = 0
#endif
#endif
  
#if !defined(OSEi)
#define OSEi()                          GIE = 1
#endif

#define OSCTXSW_METHOD                  OSRTNADDR_IS_PARAM

#define OSRtnToOSSched()                asm(" return")

#define OS_Yield(label)                 do { OSSaveRtnAddr(label); \
                                             OSRtnToOSSched(); \
                                             asm("_" _OSMkstr(label) ":"); \
                                        } while (0)   
 
#elif OSTARGET == OSPIC17
 
/* 17C42 is also afflicted. */
#if !defined(OSDi)
#if   defined(_17C42)  \
   || defined(_17C42A) \
   || defined(_17CR42)
#define OSDi()                          do { GLINTD = 1; } while ( GLINTD == 0 )
#else
#define OSDi()                          GLINTD = 1
#endif
#endif

#if !defined(OSEi)
#define OSEi()                          GLINTD = 0
#endif
     
#define OSCTXSW_METHOD                  OSRTNADDR_IS_PARAM

#define OSRtnToOSSched()                asm(" return")

#define OS_Yield(label)                 do { OSSaveRtnAddr(label); \
                                             OSRtnToOSSched(); \
                                             asm("_" _OSMkstr(label) ":"); \
                                        } while (0)
         
         
#elif OSTARGET == OSPIC18

/* interrupt control depends on OSPIC18_INTERRUPT_MASK. */
#if   ( OSPIC18_INTERRUPT_MASK == 0xC0 ) || \
      ( OSPIC18_INTERRUPT_MASK == 0x80 ) || \
      ( OSPIC18_INTERRUPT_MASK == 0x40 ) || \
      ( OSPIC18_INTERRUPT_MASK == 0x00 )
      
#if !defined(OSDi)
#define OSDi()                          do { INTCON &= ~OSPIC18_INTERRUPT_MASK; \
                                        } while (0)
#endif
#if !defined(OSEi)
#define OSEi()                          do { INTCON |=  OSPIC18_INTERRUPT_MASK; \
                                        } while (0)
#endif   
                                     
#if   ( OSPIC18_INTERRUPT_MASK == 0x00 )
#warning A value of 0x00 for OSPIC18_INTERRUPT_MASK is incompatible with interrupts. 
#endif
                                    
#else
#error portpicc.h: Invalid OSPIC18_INTERRUPT_MASK value.
#endif


#define OSCTXSW_METHOD                  OSRTNADDR_IS_PARAM

#define OSRtnToOSSched()                asm(" return")

#define OS_Yield(label)                 do { OSSaveRtnAddr(label); \
                                             OSRtnToOSSched(); \
                                             asm("_" _OSMkstr(label) ":"); \
                                        } while (0)    
 
#endif /* #if OSTARGET == ... */


/* PICC is not stack-based, so protection is required. */
#define OSProtect()                     OSEnterCritical()
#define OSUnprotect()                   OSLeaveCritical()

 
/* supported.                                          */
#define OSUSE_CHAR_SIZED_BITFIELDS      TRUE


/* Watchdog reset -- same for all PICs                 */
#define OSCLEAR_WATCHDOG_TIMER()        asm(" clrwdt")


/************************************************************ 
****                                                     ****
**                                                         **
Notes 

1. PICC void pointers can only point to ROM -- use const
type if you want to point to ROM and RAM.

2. memset() doesn't work on banks2&3 in PIC12 (obviously), 
PIC16 and PIC17, and is unknown in PIC18. 

3. Default object location is bank0 for PIC12, PIC16 and 
PIC17, and nothing (i.e. _not_ near) for PIC18.

**                                                         **
****                                                     ****
************************************************************/

