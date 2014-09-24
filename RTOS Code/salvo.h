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

$Source: C:\\RCS\\d\\salvo\\inc\\salvo.h,v $
$Author: aek $
$Revision: 3.81 $
$Date: 2003-10-21 12:37:48-07 $

Primary Salvo header file. 

************************************************************/

#if !defined(__SALVO_H) 
#define __SALVO_H
 

/************************************************************
****                                                     ****
**                                                         **
Version number. Externally (i.e. in an installer's name),
the strings look like:

            Major release:               2.2.0
            Major release, patched:      2.2.0-c
            Beta release:                2.3.0-beta1
    
**                                                         **
****                                                     ****
************************************************************/
#define OSVER_MAJOR             3
#define OSVER_MINOR             2
#define OSVER_SUBMINOR          2
                                
#define OSVERSION               ( OSVER_MAJOR*100 \
                                + OSVER_MINOR*10  \
                                + OSVER_SUBMINOR )
#define OSVersion()             OSVERSION      

                       
/************************************************************
****                                                     ****
**                                                         **
#defines for use in salvocfg.h.

Salvocfg.h contains user-definable SALVO configurations.

**                                                         **
****                                                     ****
************************************************************/
#define FALSE                   0
#define TRUE                    (!FALSE)  

#define OSUNDEF                 0   /* generic const       */
#define OSNONE                  0   /*  ""                 */

#define OSA                     1   /* letter codes used   */
#define OSB                     2   /*  with libraries     */
#define OSC                     3   /*  etc.               */
#define OSD                     4   /*  ""                 */
#define OSE                     5   /*  ""                 */
#define OSF                     6   /*  ""                 */
#define OSG                     7   /*  ""                 */
#define OSH                     8   /*  ""                 */
#define OSI                     9   /*  ""                 */
#define OSJ                     10  /*  ""                 */
#define OSK                     11  /*  ""                 */
#define OSL                     12  /*  ""                 */
#define OSM                     13  /*  ""                 */
#define OSN                     14  /*  ""                 */
#define OSO                     15  /*  ""                 */
#define OSP                     16  /*  ""                 */
#define OSQ                     17  /*  ""                 */
#define OSR                     18  /*  ""                 */
#define OSS                     19  /*  ""                 */
#define OST                     20  /*  ""                 */
#define OSU                     21  /*  ""                 */
#define OSV                     22  /*  ""                 */
#define OSW                     23  /*  ""                 */
#define OSX                     24  /*  ""                 */
#define OSY                     25  /*  ""                 */
#define OSZ                     26  /*  ""                 */

                                    /* for OSLOGGING       */
#define OSLOG_NONE              0   /* no messages at all  */
#define OSLOG_ERRORS            1   /* error messages only */
#define OSLOG_WARNINGS          2   /* warn & err messages */
#define OSLOG_ALL               3   /* all messages        */
                                                                    
                                    /* for OSTARGET        */
#define OSPIC12                 1   /* Microchip PIC12     */
#define OSPIC16                 2   /* Microchip PIC16     */
#define OSPIC17                 3   /* Microchip PIC17     */
#define OSPIC18                 4   /* Microchip PIC18     */
#define OSIX86                  5   /* Intel x86           */
#define OSI8051                 6   /* Intel MCS-51        */
#define OSVAV8                  7   /* VAutomation V8-uRISC*/
#define OSM68HC11               8   /* Motorola 68HC11     */
#define OSMSP430                9   /* TI MSP430 series    */
#define OSM68HC12               10  /* Motorola 68HC12     */
#define OSM68HC08               11  /* Motorola 68HC08     */
#define OSEZ8                   12  /* Zilog Z8 Enhanced   */
#define OSTMS320C28X            13  /* TI TMS DSP '28x     */
#define OSAVR                   14  /* Atmel's AVR family  */
#define OSTMS320C24X            15  /* TI TMS DSP '24x     */
#define OSDSP56800				16  /* Moto DSP56800       */

                                    /* for OSCOMPILER      */
#define OSHT_PICC               1   /* HI-TECH PICC, PICC-18*/
#define OSMW_CW                 2   /* Metrowerks CodeWarrior*/
#define OSMIX_PC                3   /* Mix Power C         */
#define OSIAR_ICC               4   /* IAR C               */
#define OSMPLAB_C17             5   /* Microchip MPLAB C-17*/
#define OSMPLAB_C18             6   /* Microchip MPLAB C-18*/
#define OSHT_8051C              7   /* HI-TECH 8051C       */
#define OSHT_V8C                8   /* HI-TECH V8C         */
#define OSGCC                   9   /* GNU C               */
#define OSKEIL_C51              10  /* Keil C51            */
#define OSTASKING_CC51          11  /* TASKING CC51        */
#define OSAQ_430                12  /* Quadravox 430       */
#define OSIMAGECRAFT            13  /* ImageCraft C        */
#define OSZILOG_ZDSII           14  /* Zilog ZDS II        */
#define OSTI_DSP_CCS            15  /* TI Code Composer Studio */
#define OSRA_CROSSSTUDIO        16  /* Rowley Assoc. CS    */
#define OSMW_56800              17  /* MW for 56800        */
#define OSHPIT_CVAVR			18	/* HP InfoTech CodeVision AVR */
#define OSAVR_GCC				19  /* AVR GCC             */
#define OSGCC_AVR				OSAVR_GCC 

                                    /* abbreviations       */
#define OSFROM_ANYWHERE         OSA /* fns called from anywhere*/
#define OSFROM_BACKGROUND       OSB /* fns called normally */
#define OSFROM_TASK_ONLY        OSFROM_BACKGROUND
#define OSFROM_FOREGROUND       OSF /* fns called from ISRs only*/
#define OSFROM_ISR_ONLY         OSFROM_FOREGROUND


                                    /* OSCTXSW_METHOD      */
#define OSVIA_OSCTXSW           1   /* ctxSw via OSCtxSw() */
#define OSRTNADDR_IS_PARAM      2   /* OSrtnAddr is a param*/
#define OSRTNADDR_IS_VAR        3   /* OSrtnAddr is a var  */
#define OSVIA_OSDISPATCH        4   /* ctxSw via OSCtxSw() */
                                    /*  and use OSDispatch() */ 
#define OSVIA_OSDISPATCH_WLABEL 5   /* OSDispatch()+label  */                                                                    
                                    

/************************************************************
****                                                     ****
**                                                         **
Auto-detect compiler in use, set OSCOMPILER and OSTARGET
accordingly. 

Can be overriden for testing purposes by forcing to OSUNDEF 
or a defined compiler in salvocfg.h (below).

**                                                         **
****                                                     ****
************************************************************/

/* GNU C Compiler (gcc) */
#if   defined(__GNUC__)
#undef  OSCOMPILER
#undef  OSTARGET

#if  defined(__AVR__)
#define OSCOMPILER                      OSGCC_AVR
#define OSTARGET                        OSAVR
#else
#define OSCOMPILER                      OSGCC
#define OSTARGET                        OSIX86
#endif


/* HI-TECH compilers */
#elif defined(HI_TECH_C)
#undef  OSCOMPILER
#undef  OSTARGET
#if   defined(_PIC12)
#define OSCOMPILER                      OSHT_PICC
#define OSTARGET                        OSPIC12
#elif defined(_PIC14)
#define OSCOMPILER                      OSHT_PICC
#define OSTARGET                        OSPIC16
#elif defined(_PIC16)
#define OSCOMPILER                      OSHT_PICC
#define OSTARGET                        OSPIC17
#elif defined(_PIC18)
#define OSCOMPILER                      OSHT_PICC
#define OSTARGET                        OSPIC18
#elif defined(i8051)
#define OSCOMPILER                      OSHT_8051C
#define OSTARGET                        OSI8051
#elif defined(_V8)
#define OSCOMPILER                      OSHT_V8C
#define OSTARGET                        OSVAV8
#endif /* if .. elif .. */


/* V8C v7.85PL1 failed to define HI_TECH_C */
#elif !defined(HI_TECH_C) && defined(_V8) 
#error salvo.h: V8C v7.85PL1 or higher required -- aborting.


/* IAR AVR, MSP430 and PIC18 compilers */                                   
#elif defined(__IAR_SYSTEMS_ICC__) 
#if defined(OSCOMPILER)
#undef  OSCOMPILER
#endif
#if defined(OSTARGET)
#undef  OSTARGET
#endif

#define OSCOMPILER                      OSIAR_ICC
#if   ((__TID__ >> 8) & 0x7F) == 0x31
#define OSTARGET                        OSPIC18
#elif ((__TID__ >> 8) & 0x7F) == 43
#define OSTARGET                        OSMSP430
#elif ((__TID__ >> 8) & 0x7F) == 0x5A
#define OSTARGET                        OSAVR
#endif        
  
/* Keil Cx51 compiler */
#elif defined(__C51__) || defined(__CX51__)
#undef  OSCOMPILER
#undef  OSTARGET
#define OSCOMPILER                      OSKEIL_C51
#define OSTARGET                        OSI8051


/* Metrowerks x86 compiler */
#elif defined(__MWERKS__)
#undef  OSCOMPILER
#undef  OSTARGET
#define OSCOMPILER                      OSMW_CW
#define OSTARGET                        OSIX86


/* Microchip MPLAB-C18 compiler */                                        
#elif defined(__18CXX)
#undef  OSCOMPILER
#undef  OSTARGET
#define OSCOMPILER                      OSMPLAB_C18
#define OSTARGET                        OSPIC18


/* TASKING CC51 compiler */
#elif defined(_CC51)
#undef  OSCOMPILER
#undef  OSTARGET
#define OSCOMPILER                      OSTASKING_CC51
#define OSTARGET                        OSI8051


/* Archelon / Quadravox 430 compiler */
#elif defined(__ARCHELON__) || defined(__AQCOMPILER__)
#undef  OSCOMPILER
#undef  OSTARGET
#define OSCOMPILER                      OSAQ_430
#define OSTARGET                        OSMSP430


/* ImageCraft compilers */
#elif defined(__IMAGECRAFT__)
#undef  OSCOMPILER
#define OSCOMPILER                      OSIMAGECRAFT
#undef  OSTARGET
#if   defined(_HC11)
#define OSTARGET                        OSM68HC11
#elif defined(_MSP430)
#define OSTARGET                        OSMSP430
#elif defined(_AVR)
#define OSTARGET                        OSAVR
#else
#error salvo.h: Unknown target for ImageCraft ICC. 
#endif


/* TI's DSP Code Composer for TMS320C24x|28x */
#elif defined(_TMS320C2XX) || defined(__TMS320C28XX__)
#undef  OSCOMPILER
#define OSCOMPILER                      OSTI_DSP_CCS
#undef  OSTARGET
#if   defined(_TMS320C2XX)
#define OSTARGET                        OSTMS320C24X
#elif defined(__TMS320C28XX__)
#define OSTARGET                        OSTMS320C28X
#else
#error salvo.h: Unknown target for TI DSP CCS.
#endif


/* Rowley Associates' CrossWorks MSP430 */
#elif defined(__CROSSWORKS_MSP430)
#undef  OSCOMPILER
#undef  OSTARGET
#define OSCOMPILER                      OSRA_CROSSSTUDIO
#define OSTARGET                        OSMSP430


#endif /* #if defined(__GNUC__) #elif ... */


/************************************************************
****                                                     ****
**                                                         **
Include appropriate header files.

If generating a library, no settings should be overridden.
Otherwise include salvocfg.h. OSMAKE_LIBRARY is expected to
be defined outside of source files, e.g. on the compiler's
command-line.

salvocfg.h can override (if desired) certain settings in 
salvolib.h.

**                                                         **
****                                                     ****
************************************************************/

/* set to FALSE if not defined externally. */
#if !defined(OSMAKE_LIBRARY)
#define OSMAKE_LIBRARY                  FALSE
#endif

/* if TRUE, we're building a library, and so salvocfg.h     */
/*  is disregarded -- we use salvolib.h in its place.       */
#if OSMAKE_LIBRARY
#include <salvolib.h>
#else
#include "salvocfg.h"

/* in case we picked up the user's salvocfg.h, we'll need   */
/*  to define this symbol if it's undefined.                */
#if !defined(OSUSE_LIBRARY)
#define OSUSE_LIBRARY                   FALSE
#endif
                                        
/* to get here, we have a user wanting to build an app by  	*/
/*  linking to libraries. First, verify that user hasn't	*/
/*  specified any configuration options that are only for	*/
/*  source-code builds. Then pull in the proper Salvo		*/
/*  configuration options for the library build.			*/
#if OSUSE_LIBRARY
#include <salvolbo.h>
#include <salvolib.h> 
#endif
#endif


/************************************************************
****                                                     ****
**                                                         **
macro to make / concatenate strings -- used in several
portXyz.h files, so define it now.

**                                                         **
****                                                     ****
************************************************************/
#define _OSMkstr(a)                     #a


/************************************************************
****                                                     ****
**                                                         **
Compiler- and/or target-specific configuration options.

**                                                         **
****                                                     ****
************************************************************/
#if !defined(OSIAR_PIC18_ATTR_ALL)
#define OSIAR_PIC18_ATTR_ALL                /* i.e. no attribute */
#endif


#if !defined(OSMPLAB_C18_LOC_ALL_NEAR)
#define OSMPLAB_C18_LOC_ALL_NEAR        FALSE
#endif


#if !defined(OSMPLAB_C18_STACK_SIZE)
#define OSMPLAB_C18_STACK_SIZE          512  /* will work for any stack size */
#endif
      
                                       
#if !defined(OSPIC18_INTERRUPT_MASK)
#define OSPIC18_INTERRUPT_MASK          0xC0 /* disable both GIE/GIEH and PEIE/GIEL */
#endif


/************************************************************
****                                                     ****
**                                                         **
General configuration options.

Will take effect only if they're not already defined in 
salvocfg.h.

**                                                         **
****                                                     ****
************************************************************/
#if !defined(OSBIG_SEMAPHORES)
#define OSBIG_SEMAPHORES                FALSE
#endif
                                        
#if !defined(OSBYTES_OF_COUNTS)            
#define OSBYTES_OF_COUNTS               0 
#endif 

#if !defined(OSBYTES_OF_DELAYS)           
#define OSBYTES_OF_DELAYS               0
#endif 

#if !defined(OSBYTES_OF_EVENT_FLAGS)
#define OSBYTES_OF_EVENT_FLAGS          1
#endif 

#if !defined(OSBYTES_OF_TICKS)
#define OSBYTES_OF_TICKS                0 
#endif 

#if !defined(OSCALL_OSCREATEEVENT)
#define OSCALL_OSCREATEEVENT            OSFROM_BACKGROUND
#endif

#if !defined(OSCALL_OSGETPRIOTASK)
#define OSCALL_OSGETPRIOTASK            OSFROM_BACKGROUND
#endif

#if !defined(OSCALL_OSGETSTATETASK)
#define OSCALL_OSGETSTATETASK           OSFROM_BACKGROUND
#endif

#if !defined(OSCALL_OSMSGQCOUNT)
#define OSCALL_OSMSGQCOUNT              OSFROM_BACKGROUND
#endif

#if !defined(OSCALL_OSMSGQEMPTY)
#define OSCALL_OSMSGQEMPTY              OSFROM_BACKGROUND
#endif

#if !defined(OSCALL_OSRETURNEVENT) 
#define OSCALL_OSRETURNEVENT            OSFROM_BACKGROUND
#endif

#if !defined(OSCALL_OSSIGNALEVENT)
#define OSCALL_OSSIGNALEVENT            OSFROM_BACKGROUND
#endif

#if !defined(OSCALL_OSSTARTTASK)
#define OSCALL_OSSTARTTASK              OSFROM_BACKGROUND
#endif

#if !defined(OSCLEAR_GLOBALS)
#define OSCLEAR_GLOBALS                 TRUE
#endif

#if !defined(OSCLEAR_UNUSED_POINTERS)
#define OSCLEAR_UNUSED_POINTERS         FALSE
#endif

#if !defined(OSCOMBINE_EVENT_SERVICES)
#define OSCOMBINE_EVENT_SERVICES        FALSE
#endif

#if !defined(OSCUSTOM_LIBRARY_CONFIG)
#define OSCUSTOM_LIBRARY_CONFIG         0
#endif

#if !defined(OSDISABLE_ERROR_CHECKING)
#define OSDISABLE_ERROR_CHECKING        FALSE
#endif

#if !defined(OSDISABLE_FAST_RESCHEDULING)
#define OSDISABLE_FAST_RESCHEDULING     FALSE
#endif

#if !defined(OSDISABLE_TASK_PRIORITIES)
#define OSDISABLE_TASK_PRIORITIES       FALSE
#endif

#if !defined(OSENABLE_BINARY_SEMAPHORES)
#define OSENABLE_BINARY_SEMAPHORES      FALSE
#endif

#if !defined(OSENABLE_BOUNDS_CHECKING)
#define OSENABLE_BOUNDS_CHECKING        FALSE
#endif

#if !defined(OSENABLE_CYCLIC_TIMERS)
#define OSENABLE_CYCLIC_TIMERS          FALSE
#endif

#if !defined(OSENABLE_EVENT_FLAGS)
#define OSENABLE_EVENT_FLAGS            FALSE
#endif

#if !defined(OSENABLE_EVENT_READING)
#define OSENABLE_EVENT_READING          FALSE
#endif

#if !defined(OSENABLE_EVENT_TRYING)
#define OSENABLE_EVENT_TRYING           FALSE
#endif

#if !defined(OSENABLE_FAST_SIGNALING)
#define OSENABLE_FAST_SIGNALING         FALSE
#endif

#if !defined(OSENABLE_IDLE_COUNTER)
#define OSENABLE_IDLE_COUNTER           FALSE
#endif

#if !defined(OSENABLE_IDLING_HOOK)
#define OSENABLE_IDLING_HOOK            FALSE
#endif

#if !defined(OSENABLE_INTERRUPT_HOOKS)
#define OSENABLE_INTERRUPT_HOOKS        FALSE
#endif

#if !defined(OSENABLE_MESSAGES)
#define OSENABLE_MESSAGES               FALSE
#endif

#if !defined(OSENABLE_MESSAGE_QUEUES)
#define OSENABLE_MESSAGE_QUEUES         FALSE
#endif

#if !defined(OSENABLE_OSSCHED_DISPATCH_HOOK)
#define OSENABLE_OSSCHED_DISPATCH_HOOK  FALSE
#endif

#if !defined(OSENABLE_OSSCHED_ENTRY_HOOK)
#define OSENABLE_OSSCHED_ENTRY_HOOK     FALSE
#endif

#if !defined(OSENABLE_OSSCHED_RETURN_HOOK)
#define OSENABLE_OSSCHED_RETURN_HOOK    FALSE
#endif

#if !defined(OSENABLE_SEMAPHORES)
#define OSENABLE_SEMAPHORES             FALSE
#endif

#if !defined(OSENABLE_STACK_CHECKING)
#define OSENABLE_STACK_CHECKING         FALSE
#endif

#if !defined(OSENABLE_TCBEXT0)
#define OSENABLE_TCBEXT0                FALSE
#endif

#if !defined(OSENABLE_TCBEXT1)
#define OSENABLE_TCBEXT1                FALSE
#endif

#if !defined(OSENABLE_TCBEXT2)
#define OSENABLE_TCBEXT2                FALSE
#endif

#if !defined(OSENABLE_TCBEXT3)
#define OSENABLE_TCBEXT3                FALSE
#endif

#if !defined(OSENABLE_TCBEXT4)
#define OSENABLE_TCBEXT4                FALSE
#endif

#if !defined(OSENABLE_TCBEXT5)
#define OSENABLE_TCBEXT5                FALSE
#endif

#if !defined(OSENABLE_TIMEOUTS)
#define OSENABLE_TIMEOUTS               FALSE
#endif

#if !defined(OSEVENT_FLAGS)
#define OSEVENT_FLAGS                   0
#endif

#if !defined(OSEVENTS)
#define OSEVENTS                        0
#endif

#if !defined(OSEVENTS_LIMIT)
#define OSEVENTS_LIMIT                  OSEVENTS
#endif

#if !defined(OSGATHER_STATISTICS)
#define OSGATHER_STATISTICS             FALSE
#endif

#if !defined(OSINTERRUPT_LEVEL)
#define OSINTERRUPT_LEVEL               0
#endif

#if !defined(OSLOGGING)
#define OSLOGGING                       FALSE
#endif

#if !defined(OSLOG_MESSAGES)
#define OSLOG_MESSAGES                  OSLOG_NONE
#endif
                                        
#if !defined(OSMAKE_LIBRARY)
#define OSMAKE_LIBRARY                  FALSE
#endif

#if !defined(OSMAX_LOST_TICKS)
#define OSMAX_LOST_TICKS                255
#endif

#if !defined(OSMESSAGE_QUEUES)
#define OSMESSAGE_QUEUES                0
#endif

#if !defined(OSOPTIMIZE_FOR_SPEED)
#define OSOPTIMIZE_FOR_SPEED            FALSE
#endif

#if !defined(OSPRESERVE_INTERRUPT_MASK)
#define OSPRESERVE_INTERRUPT_MASK       TRUE
#endif 

#if !defined(OSRPT_HIDE_INVALID_POINTERS)
#define OSRPT_HIDE_INVALID_POINTERS     TRUE
#endif

#if !defined(OSRPT_SHOW_ONLY_ACTIVE)
#define OSRPT_SHOW_ONLY_ACTIVE          TRUE
#endif

#if !defined(OSRPT_SHOW_TOTAL_DELAY)
#define OSRPT_SHOW_TOTAL_DELAY          TRUE
#endif

#if !defined(OSSET_LIMITS)
#define OSSET_LIMITS                    FALSE
#endif

#if !defined(OSSPEEDUP_QUEUEING)
#define OSSPEEDUP_QUEUEING              FALSE
#endif

#if !defined(OSTARGET)
#define OSTARGET                        OSUNDEF
#endif

#if !defined(OSTASKS)
#define OSTASKS                         0
#endif

#if !defined(OSTASKS_LIMIT)
#define OSTASKS_LIMIT                   OSTASKS
#endif

#if !defined(OSTIMER_PRESCALAR)
#define OSTIMER_PRESCALAR               0
#endif

#if !defined(OSTYPE_TCBEXT0)
#define OSTYPE_TCBEXT0                  void *
#endif 

#if !defined(OSTYPE_TCBEXT1)
#define OSTYPE_TCBEXT1                  void *
#endif 

#if !defined(OSTYPE_TCBEXT2)
#define OSTYPE_TCBEXT2                  void *
#endif

#if !defined(OSTYPE_TCBEXT3)
#define OSTYPE_TCBEXT3                  void *
#endif

#if !defined(OSTYPE_TCBEXT4)
#define OSTYPE_TCBEXT4                  void *
#endif

#if !defined(OSTYPE_TCBEXT5)
#define OSTYPE_TCBEXT5                  void *
#endif

#if !defined(OSUSE_ARRAYS)
#define OSUSE_ARRAYS                    FALSE
#endif

#if !defined(OSUSE_EVENT_TYPES)
#define OSUSE_EVENT_TYPES               TRUE
#endif

#if !defined(OSUSE_INLINE_OSSCHED)
#define OSUSE_INLINE_OSSCHED            FALSE
#endif

#if !defined(OSUSE_INLINE_OSTIMER)
#define OSUSE_INLINE_OSTIMER            FALSE
#endif

#if !defined(OSUSE_OSINSELIG_MACRO)
#define OSUSE_OSINSELIG_MACRO           TRUE
#endif    

#if !defined(OSUSE_LIBRARY)
#define OSUSE_LIBRARY                   FALSE
#endif



/************************************************************ 
****                                                     ****
**                                                         **
#include"portXyz.h":

Include the compiler- and target processor-specific items
required for your system.

**                                                         **
****                                                     ****
************************************************************/
/* undefined compiler -- was not set by user */
#if !defined(OSCOMPILER)
#define OSCOMPILER                      OSUNDEF
#endif



/* Zilog ZDSII compiler for Z8 Encore. Put this here because */
/*  of bug in v4.2 in #if ... #elif ... #else ... #endif     */
/*  statements ... but it still screws up on the #else part. */
#if (OSCOMPILER == OSZILOG_ZDSII)

#include "portez8.h"



/* Your Compiler - specific items */
#elif   (OSCOMPILER == OSUNDEF)
  
#include "portuser.h"


/* Archelon/Quadravox 430 */
#elif (OSCOMPILER == OSAQ_430)

#include "portaq430.h"


/* GNU C compiler */
#elif (OSCOMPILER == OSGCC)

#include "portgcc.h"


/* HI-TECH 8051C compiler  */
#elif (OSCOMPILER == OSHT_8051C)

#include "portht51.h"


/* HI-TECH PICC and PICC-18 */
#elif (OSCOMPILER == OSHT_PICC)

#include "portpicc.h"


/* HI-TECH V8C compiler */
#elif (OSCOMPILER == OSHT_V8C)

#include "portv8c.h"


/* IAR PICMicro C Compiler */
#elif (OSCOMPILER == OSIAR_ICC)

#if   (OSTARGET == OSAVR)
#include "portiaravr.h"
#elif (OSTARGET == OSMSP430)
#include "portiar430.h"
#elif (OSTARGET == OSPIC18)
#include "portiar18.h"
#else
#error salvo.h: Unknown target for IAR compiler.
#endif


/* ImageCraft compilers */
#elif (OSCOMPILER == OSIMAGECRAFT) 

#if   (OSTARGET == OSAVR)
#include "porticcavr.h"
#elif (OSTARGET == OSM68HC11)
#include "porticc11.h"
#elif (OSTARGET == OSMSP430)
#include "porticc430.h"
#else
#error salvo.h: Unknown target for ImageCraft compiler.
#endif


/* AVR GCC compiler */
#elif ( (OSCOMPILER == OSAVR_GCC) || (OSCOMPILER == OSGCC_AVR) )

#include "portgccavr.h"

 
/* Keil C51 compiler */
#elif (OSCOMPILER == OSKEIL_C51)

#include "portkc51.h"

 
/* Metrowerks CodeWarrior for i86 */
#elif (OSCOMPILER == OSMW_CW)

#include "portmwcw.h"
  
    
/* Metrowerks CodeWarrior for Motorola DSP56800 */
#elif ( (OSCOMPILER == OSMW_56800) && (OSTARGET == OSDSP56800) )

#include "portmw56800.h"
  
    
/* Microchip MPLAB C-18 Compiler */
#elif (OSCOMPILER == OSMPLAB_C18)

#include "portmcc.h"


/* Mix Power C */
#elif (OSCOMPILER == OSMIX_PC)

#include "portmixc.h"


/* TASKING CC51 compiler */
#elif (OSCOMPILER == OSTASKING_CC51)

#include "portcc51.h"


/* TI Code Composer Studio compiler for TMS320C24x|28x */
#elif (OSCOMPILER == OSTI_DSP_CCS)

#if ( (OSTARGET == OSTMS320C24X) || (OSTARGET == OSTMS320C28X) )
#include "porttic2000.h"
#else
#error salvo.h: Unknown target for TI DSP CCS.
#endif


/* Rowley Associates CrossStudio */
#elif (OSCOMPILER == OSRA_CROSSSTUDIO)

#if (OSTARGET == OSMSP430)
#include "portcs430.h"
#else
#error salvo.h: Unknown target for CrossStudio compiler.
#endif


/* fall-through on undefined or unknown OSCOMPILER */
#else
#error salvo.h: No known porting header file for this OSCOMPILER.


#endif /* #if OSCOMPILER */



/************************************************************
****                                                     ****
**                                                         **
Unsupported, Invalid and/or obsolete configuration options.

**                                                         **
****                                                     ****
************************************************************/
#if defined(OSBIG_MESSAGE_POINTERS) 
#if ( OSCOMPILER == OSHT_PICC )
#if OSBIG_MESSAGE_POINTERS
#define OSMESSAGE_TYPE                  const
#else
#define OSMESSAGE_TYPE                  void
#endif
#else
#error salvo.h: Unsupported or obsolete configuration option: \
OSBIG_MESSAGE_POINTERS. Use OSMESSAGE_TYPE instead.
#endif
#endif

#if defined(OSCALL_OSCREATEBINSEM)
#error salvo.h: Unsupported or obsolete configuration option: \
OSCALL_OSCREATEBINSEM. Use OSCALL_OSCREATEEVENT instead.
#undef OSCALL_OSCREATEBINSEM
#endif

#if defined(OSCALL_OSCREATEMSG)
#error salvo.h: Unsupported or obsolete configuration option: \
OSCALL_OSCREATEMSG. Use OSCALL_OSCREATEEVENT instead.
#undef OSCALL_OSCREATEMSG
#endif

#if defined(OSCALL_OSCREATEMSGQ)
#error salvo.h: Unsupported or obsolete configuration option: \
OSCALL_OSCREATEMSGQ. Use OSCALL_OSCREATEEVENT instead.
#undef OSCALL_OSCREATEMSGQ
#endif

#if defined(OSCALL_OSCREATESEM)
#error salvo.h: Unsupported or obsolete configuration option: \
OSCALL_OSCREATESEM. Use OSCALL_OSCREATEEVENT instead.
#undef OSCALL_OSCREATESEM
#endif

#if defined(OSCALL_OSSIGNALBINSEM)
#error salvo.h: Unsupported or obsolete configuration option: \
OSCALL_OSSIGNALBINSEM. Use OSCALL_OSSIGNALEVENT instead.
#undef OSCALL_OSSIGNALBINSEM
#endif

#if defined(OSCALL_OSSIGNALMSG)
#error salvo.h: Unsupported or obsolete configuration option: \
OSCALL_OSSIGNALMSG. Use OSCALL_OSSIGNALEVENT instead. 
#undef OSCALL_OSSIGNALMSG
#endif

#if defined(OSCALL_OSSIGNALMSGQ)
#error salvo.h: Unsupported or obsolete configuration option: \
OSCALL_OSSIGNALMSGQ. Use OSCALL_OSSIGNALEVENT instead.
#undef OSCALL_OSSIGNALMSGQ
#endif

#if defined(OSCALL_OSSIGNALSEM)
#error salvo.h: Unsupported or obsolete configuration option: \
OSCALL_OSSIGNALSEM. Use OSCALL_OSSIGNALEVENT instead.
#undef OSCALL_OSSIGNALSEM
#endif

#if defined(OSENABLE_IDLE_TASK)
#error salvo.h: Unsupported or obsolete configuration option: \
OSENABLE_IDLE_TASK.
#undef OSENABLE_IDLE_TASK
#endif

#if defined(OSENABLE_IDLE_TASK_HOOK)
#error salvo.h: Unsupported or obsolete configuration option: \
OSENABLE_IDLE_TASK_HOOK.
#undef OSENABLE_IDLE_TASK_HOOK
#endif

#if defined(OSMONITOR_KEYWORD_POST) && !defined(OSMONITOR_KEYWORD_POST_PROTO)
#error salvo.h: OSMONITOR_KEYWORD_POST_PROTO must also be defined.
#undef OSMONITOR_KEYWORD_POST
#endif

#if defined(OSMONITOR_KEYWORD_PRE) && !defined(OSMONITOR_KEYWORD_PRE_PROTO)
#error salvo.h: OSMONITOR_KEYWORD_PRE_PROTO must also be defined.
#undef OSMONITOR_KEYWORD_PRE
#endif

#if defined(OSPIC16_GIE_BUG)
#error salvo.h: Unsupported or obsolete configuration option: \
OSPIC16_GIE_BUG.
#undef OSPIC16_GIE_BUG
#endif

#if defined(OSSUPERTIMER_PRESCALAR)
#error salvo.h: Unsupported or obsolete configuration option: \
OSSUPERTIMER_PRESCALAR.
#undef OSSUPERTIMER_PRESCALAR
#endif

#if OSUSE_ARRAYS
#error salvo.h: Unsupported or obsolete configuration option: \
OSUSE_ARRAYS. Coming to a later version ...
#undef OSUSE_ARRAYS
#define OSUSE_ARRAYS FALSE
#endif

#if defined(OSUSE_LOCAL_ECBP)
#error salvo.h: Unsupported or obsolete configuration option: \
OSUSE_LOCAL_ECBP.
#undef OSUSE_LOCAL_ECBP           
#endif

#if defined(OSUSE_LOCAL_TCBP)
#error salvo.h: Unsupported or obsolete configuration option: \
OSUSE_LOCAL_TCBP.
#undef OSUSE_LOCAL_TCBP           
#endif

#if defined(OSUSE_CIRCULAR_QUEUES)
#error salvo.h: Unsupported or obsolete configuration option: \
OSUSE_CIRCULAR_QUEUES.
#undef OSUSE_CIRCULAR_QUEUES
#endif

#if OSUSE_INLINE_OSSCHED
#if ( OSCOMPILER == OSIAR_ICC ) && ( OSTARGET == OSMSP430 )
#error salvo.h: Option not supported with this compiler: OSUSE_INLINE_OSSCHED.
#endif
#endif

#if defined(OSUSE_INSELIGQ_MACRO)
#error salvo.h: Unsupported or obsolete configuration option: \
OSUSE_INSELIGQ_MACRO. Use OSUSE_INSELIG_MACRO instead.
#undef OSUSE_INSELIGQ_MACRO
#endif

#if defined(OSUSE_SUPERTIMER)
#error salvo.h: Unsupported or obsolete configuration option: \
OSUSE_SUPERTIMER.
#undef OSUSE_SUPERTIMER
#endif

/* The user should not set any of these if the compiler    */
/*  in use doesn't need them.                            */
#if  ( OSCALL_OSCREATEEVENT  != OSFROM_BACKGROUND ) \
  || ( OSCALL_OSGETPRIOTASK  != OSFROM_BACKGROUND ) \
  || ( OSCALL_OSGETSTATETASK != OSFROM_BACKGROUND ) \
  || ( OSCALL_OSMSGQEMPTY    != OSFROM_BACKGROUND ) \
  || ( OSCALL_OSRETURNEVENT  != OSFROM_BACKGROUND ) \
  || ( OSCALL_OSSIGNALEVENT  != OSFROM_BACKGROUND ) \
  || ( OSCALL_OSSTARTTASK    != OSFROM_BACKGROUND )
#if  ( OSCOMPILER != OSHT_PICC )  \
  && ( OSCOMPILER != OSHT_V8C )   \
  && ( OSCOMPILER != OSKEIL_C51 )
#error salvo.h: Unsupported or unnecessary configuration option: OSCALL_OSXYZ.
#endif
#endif

/************************************************************
****                                                     ****
**                                                         **
Packaged defines for dealing with compiler incompatibilities.
Each symbol represents a particular bug found, and is used
to invoke a workaround. These are provided because users
may not have a current revision of the specified compiler.

All workarounds default to FALSE to ensure that the symbols
are always defined.

**                                                         **
****                                                     ****
************************************************************/
/* all workarounds are initially defined as FALSE to avoid */
/*  "unknown identifier" problems with unrelated compilers.*/
#define OSWORKAROUND_HT_PICC_1          FALSE
#define OSWORKAROUND_HT_V8C_2           FALSE


/* now begin compiler-specific workaround section. */
#if ( OSCOMPILER == OSHT_PICC ) || ( OSCOMPILER == OSHT_V8C )

#if !defined(_HTC_VER_MAJOR_)
#define _HTC_VER_MAJOR_                 0
#endif
#if !defined(_HTC_VER_MINOR_)
#define _HTC_VER_MINOR_                 0
#endif
#if !defined(_HTC_VER_PATCH_)
#define _HTC_VER_PATCH_                 0
#endif
#define OSHTC_VER                         (_HTC_VER_MAJOR_*1000) \
                                        + (_HTC_VER_MINOR_*  10) \
                                        + (_HTC_VER_PATCH_*   1)

#endif


/* version tracking for HI-TECH PICC compilers began with   */
/*  v7.87.                                                  */
#if ( OSCOMPILER == OSHT_PICC )
 
/* PICC workaround #1 -- on PIC12, functions that return an */
/*  8-bit value and have parameters MUST return a value     */
/*  immediately after a comparison with one of the param-   */
/*  eters. O/wise undefined symbol:btemp error occurs. This */
/*  bug was present in v7.87 and earlier and has not been   */
/*  fixed, TTBOMK.                                          */
#if ( OSTARGET == OSPIC12 )
#undef  OSWORKAROUND_HT_PICC_1
#define OSWORKAROUND_HT_PICC_1          TRUE
#endif

#endif /* HI-TECH PICC compilers */


/* version tracking for HI-TECH V8C compilers began with    */
/*  v7.85PL1.                                               */
#if ( OSCOMPILER == OSHT_V8C )

 
/* V8C workaround #1. "Can't generate code for this         */
/*  expression" when a pointer parameter is used to point   */
/*  to a field in an rvalue. Rendered obsolete 12/6/02      */
/*  because of the way we were using #define and #undef to  */
/*  implement this solution.                                */
#if OSHTC_VER <= 7850
#error salvo.h You must upgrade to V8C v7.85PL1 or later ...
#endif

/* V8C workaround #2. Doing:                                 */
/*      tcbP->status.bits.prio = prio                       */
/* results in a huge number of incorrect instructions.        */
/* Not yet fixed in V8C.                                    */
#undef  OSWORKAROUND_HT_V8C_2
#define OSWORKAROUND_HT_V8C_2            TRUE

#endif /* HI-TECH V8C compiler */



/************************************************************
****                                                     ****
**                                                         **
#defines that lead to conflicts.

**                                                         **
****                                                     ****
************************************************************/
#if ( OSCOMPILER == OSMIX_PC ) && OSUSE_INLINE_OSTIMER
#error salvo.h: In-lining OSTimer() is not permitted with Mix PC Compiler.
#endif


/************************************************************
****                                                     ****
**                                                         **
Special #defines for creating demo versions.

Hard-coded limits for the number of events, message queues 
and tasks are used in places like OSCreateTask() and 
OSWaitBinSem().

They are enabled when OSSET_LIMITS is TRUE.

Note that these limits do not prevent the creation of large
ecbs, mqcbs and tcbs -- it's just that the code won't allow 
access to the ones beyond the set limits.

**                                                         **
****                                                     ****
************************************************************/
#if OSSET_LIMITS
#undef OSENABLE_BOUNDS_CHECKING
#define OSENABLE_BOUNDS_CHECKING        TRUE
#endif


/************************************************************
****                                                     ****
**                                                         **
Special Salvo configurations.

#defines which override other #defines.

**                                                         **
****                                                     ****
************************************************************/
/* reference the external user function if in use */
#if OSENABLE_INTERRUPT_HOOKS
#define OSDiHook()                      OSDisableIntsHook()
#define OSEiHook()                      OSEnableIntsHook()
#else
#define OSDiHook() 
#define OSEiHook()
#endif
                                        

/* cyclic timers require that timeouts be enabled */
#if OSENABLE_CYCLIC_TIMERS
  #undef OSENABLE_TIMEOUTS
  #define OSENABLE_TIMEOUTS             TRUE
#endif


/* timeouts require that events and delays be enabled */
#if OSENABLE_TIMEOUTS
 #if ( OSBYTES_OF_DELAYS == 0 )
  #undef OSBYTES_OF_DELAYS
  #define OSBYTES_OF_DELAYS             1
 #endif
 #if !OSEVENTS
  #undef OSEVENTS
  #define OSEVENTS                      1
 #endif
#endif


/* must have at least one event flag if they're enabled.    */
/*  An exception exists when using libraries -- you want to */
/*  be able to remove them entirely from your memory map.   */
#if OSENABLE_EVENT_FLAGS && !OSUSE_LIBRARY
 #if ( OSEVENT_FLAGS == 0 )
  #undef OSEVENT_FLAGS
  #define OSEVENT_FLAGS                 1
 #endif
#endif


/* must have at least one message queue if they're enabled. */
/*  An exception exists when using libraries -- you want to */
/*  be able to remove them entirely from your memory map.   */
#if OSENABLE_MESSAGE_QUEUES && !OSUSE_LIBRARY
 #if ( OSMESSAGE_QUEUES == 0 )
  #undef OSMESSAGE_QUEUES
  #define OSMESSAGE_QUEUES              1
 #endif
#endif


/* statistics must have counters enabled and > 0 */
#if OSGATHER_STATISTICS
 #if ( OSBYTES_OF_COUNTS == 0 )
 #undef OSBYTES_OF_COUNTS
 #define OSBYTES_OF_COUNTS              1
 #endif
 #if !defined(OSBYTES_OF_COUNTS)
 #define OSBYTES_OF_COUNTS              1
 #endif
#endif


/* message logging is only allowed if logging is enabled */
#if OSLOG_MESSAGES && !OSLOGGING
 #undef OSLOG_MESSAGES
 #define OSLOG_MESSAGES                 OSLOG_NONE
#endif

/* we only support 7 bits of lost tick collecting ... */
#if ( (OSMAX_LOST_TICKS < 1) || (OSMAX_LOST_TICKS > 255) )
#error salvo.h: OSMAX_LOST_TICKS must be > 0 and < 256.
#endif


/* makes sense, esp. for timestamp stuff. */
#if OSBYTES_OF_TICKS && OSBYTES_OF_DELAYS
 #if ( OSBYTES_OF_TICKS < OSBYTES_OF_DELAYS )
 #error salvo.h: OSBYTES_OF_TICKS must be greater than or equal to OSBYTES_OF_DELAYS
 #endif
#endif
 
 
/************************************************************
****                                                     ****
**                                                         **
Special SALVO configurations.

meta-#defines based on lower-level #defines.

**                                                         **
****                                                     ****
************************************************************/
#if defined(OSENABLE_COUNTS)
#undef OSENABLE_COUNTS
#endif
#if OSBYTES_OF_COUNTS
#define OSENABLE_COUNTS                 TRUE
#else
#define OSENABLE_COUNTS                 FALSE
#endif

#if defined(OSENABLE_DELAYS)
#undef OSENABLE_DELAYS
#endif
#if OSBYTES_OF_DELAYS
#define OSENABLE_DELAYS                 TRUE
#else
#define OSENABLE_DELAYS                 FALSE
#endif

#if defined(OSENABLE_ERROR_CHECKING)
#undef OSENABLE_ERROR_CHECKING
#endif
#define OSENABLE_ERROR_CHECKING         !OSDISABLE_ERROR_CHECKING

#if OSENABLE_EVENT_TRYING
#undef OSENABLE_EVENT_READING
#define OSENABLE_EVENT_READING          TRUE
#endif

#if defined(OSENABLE_TICKS)
#undef OSENABLE_TICKS
#endif
#if OSBYTES_OF_TICKS
#define OSENABLE_TICKS                  TRUE
#else
#define OSENABLE_TICKS                  FALSE
#endif

#if defined(OSENABLE_PRESCALAR)
#undef OSENABLE_PRESCALAR
#endif
#if ( OSTIMER_PRESCALAR >= 1 )    /* avoid TRUE/FALSE problems with big PS */
#define OSENABLE_PRESCALAR              TRUE
#else
#define OSENABLE_PRESCALAR              FALSE
#endif

#if defined(OSENABLE_EVENTS)
#undef OSENABLE_EVENTS
#endif
#if OSEVENTS && ( OSENABLE_BINARY_SEMAPHORES \
   || OSENABLE_SEMAPHORES     || OSENABLE_MESSAGES \
   || OSENABLE_MESSAGE_QUEUES || OSENABLE_EVENT_FLAGS )
#define OSENABLE_EVENTS                 TRUE
#else
#define OSENABLE_EVENTS                 FALSE
#endif

#if defined(OSENABLE_TASKS)
#undef OSENABLE_TASKS
#endif
#if OSTASKS
#define OSENABLE_TASKS                  TRUE
#else
#define OSENABLE_TASKS                  FALSE
#endif


#if defined(OSARRAY_SIZE_IS_BYTE)
#undef OSARRAY_SIZE_IS_BYTE
#endif
#if defined(OSARRAY_SIZE_IS_WORD)
#undef OSARRAY_SIZE_IS_WORD
#endif
#if OSUSE_ARRAYS
#if ( OSTASKS < 9 )
#define OSARRAY_SIZE_IS_BYTE            TRUE
#else
#define OSARRAY_SIZE_IS_WORD            TRUE
#endif
#endif


#if OSENABLE_EVENTS \
  || ( OSCALL_OSSTARTTASK == OSFROM_FOREGROUND ) \
  || ( OSCALL_OSSTARTTASK == OSFROM_ANYWHERE )
#define OSENABLE_SIGQ                   TRUE
#else
#define OSENABLE_SIGQ                   FALSE
#endif
                                        

/************************************************************
****                                                     ****
**                                                         **
Compiler- and target-specific special settings

**                                                         **
****                                                     ****
************************************************************/


/************************************************************
****                                                     ****
**                                                         **
Salvo's native typedefs.

**                                                         **
****                                                     ****
************************************************************/
typedef unsigned char OStypeBoolean;   /* FALSE or TRUE       */
typedef signed char   OStypeInt8;      /* -128 to +127        */
typedef unsigned char OStypeInt8u;     /* 0 to +255           */
typedef signed int    OStypeInt16;     /* -32768 to +32767    */
typedef unsigned int  OStypeInt16u;    /* 0 to +65,535        */
typedef signed long   OStypeInt32;     /* -2.1B to +2.1B      */
typedef unsigned long OStypeInt32u;    /* 0 to +4,294,967,295 */

typedef OStypeInt8u OStypePrio;        /* 16 unique priorities */
#define OStypeCTMode OStypePrio            /* synonymous */
typedef OStypeInt8u OStypeState;       /* 8 unique states      */
typedef OStypeInt8u OStypeOption;      /* generic option type, */
                                       /*  e.g. for eFlgs      */
                                                                                        
typedef OStypeInt8u  OStypeEType;      /* 256 event types      */                            
typedef OStypeInt8u  OStypeDepth;      /* 256 stack depth      */
typedef OStypeInt8u  OStypeID;         /* 256 IDs              */

typedef OStypeInt8u  OStypeErr;        /* 8-bit return (error) */
									   /*  codes               */
                                
typedef struct ecb  OStypeEcb;         /* event control block  */
typedef struct tcb  OStypeTcb;         /* task control block   */
typedef struct mqcb OStypeMqcb;        /* msg Q control block  */
typedef struct efcb OStypeEfcb;        /* ev flag control block*/

typedef OSTYPE_TCBEXT0 OStypeTcbExt0;  /* user-definable tcb   */
typedef OSTYPE_TCBEXT1 OStypeTcbExt1;  /*  extension types     */
typedef OSTYPE_TCBEXT2 OStypeTcbExt2;  /*                      */
typedef OSTYPE_TCBEXT3 OStypeTcbExt3;  /*                      */
typedef OSTYPE_TCBEXT4 OStypeTcbExt4;  /*                      */
typedef OSTYPE_TCBEXT5 OStypeTcbExt5;  /*                      */


/* NOTE: OStypeBoolean, OStypeBinSem and OStypeSem                 */
/* (!OSBIG_SEMAPHORES) are all alike -- event processing expects   */
/*  and requires this.  See OSWaitXXX(). Also OStypeMsgQSize       */

typedef OStypeBoolean OStypeBinSem;    /* binSems are just 0 or 1  */

#if !OSBIG_SEMAPHORES                  /* small semaphores have a  */
typedef OStypeInt8u OStypeSem;         /*  maximum value of 255,   */
#define MAX_SEM 255                    /*  big ones 32,767         */
#else            
typedef OStypeInt16u OStypeSem;    
#define MAX_SEM 32767                    
#endif /* #if !OSBIG_SEMAPHORES  */            

typedef OStypeInt8u OStypeMsgQSize;    /* 255 messages per queue   */
typedef OStypeMsgQSize * OStypeMsgQSizeP;                    

#if OSUSE_ARRAYS                                
#if OSARRAY_SIZE_IS_BYTE
typedef OStypeInt8u OStypePrioA;       /* size of priority arrays  */
#else                                  /*  depends on the number   */
typedef OStypeInt16u OStypePrioA;      /*  of tasks                */
#endif
#endif




/************************************************************ 
****                                                     ****
**                                                         **
Port-specific symbol defaults.

These are a safety net in case the symbol is not set in
portxxxx.c and the default is not desired.

**                                                         **
****                                                     ****
************************************************************/
#if !defined(OSBYTES_OF_FRAMEP)
#define OSBYTES_OF_FRAMEP               2 
#endif 

#if !defined(OSBYTES_OF_SRGIE)
#define OSBYTES_OF_SRGIE                2 
#endif 

#if !defined(OSCTXSW_METHOD)
#define OSCTXSW_METHOD                  OSVIA_OSCTXSW
#endif

#if !defined(OSCLEAR_WATCHDOG_TIMER)
#define OSCLEAR_WATCHDOG_TIMER()
#endif

#if !defined(OSLOC_DEFAULT)
#define OSLOC_DEFAULT
#endif

#if !defined(OSMESSAGE_TYPE)
#define OSMESSAGE_TYPE                  void
#endif

#if !defined(OSMONITOR_KEYWORD_PRE) && !defined(OSMONITOR_KEYWORD_POST)
#define OSMONITOR_KEYWORD_EXISTS        FALSE
#define    OSMONITOR_KEYWORD_PRE
#define    OSMONITOR_KEYWORD_PRE_PROTO
#define    OSMONITOR_KEYWORD_POST
#define    OSMONITOR_KEYWORD_POST_PROTO
#else
#define OSMONITOR_KEYWORD_EXISTS        TRUE
#if   !defined(OSMONITOR_KEYWORD_PRE)
#define OSMONITOR_KEYWORD_PRE
#define OSMONITOR_KEYWORD_PRE_PROTO
#elif !defined(OSMONITOR_KEYWORD_POST)
#define OSMONITOR_KEYWORD_POST
#define OSMONITOR_KEYWORD_POST_PROTO
#endif
#endif

#if !defined(NULL)
#define NULL                            ((void *) 0)
#endif

#if !defined(OSProtect)
#define OSProtect()
#endif

#if !defined(OSRtnToOSSched)
#define OSRtnToOSSched()                return
#endif
                                        
#if !defined(OSRTNADDR_OFFSET)
#define OSRTNADDR_OFFSET                0
#endif
                                        
#if !defined(OSSCHED_RETURN_LABEL)
#define OSSCHED_RETURN_LABEL()
#endif

#if !defined(OSTASK_POINTER_TYPE)
#define OSTASK_POINTER_TYPE
#endif

#if !defined(OSUnprotect)
#define OSUnprotect()
#endif    
                                        
#if !defined(OSUSE_CHAR_SIZED_BITFIELDS)
#define OSUSE_CHAR_SIZED_BITFIELDS      FALSE
#endif
#if ( OSUSE_CHAR_SIZED_BITFIELDS \
  && ( ( OSCOMPILER == OSHT_8051C ) \
  || ( ( OSCOMPILER == OSIAR_ICC ) && ( OSTARGET == OSMSP430 ) ) ) )
#error salvo.h: selected compiler does not support bitfield packing.
#endif

#if !defined(OSUSE_EXTERN_ARRAY_SIZES)        
#define OSUSE_EXTERN_ARRAY_SIZES        FALSE    
#endif    

#if !defined(OSUSE_MEMSET)
#define OSUSE_MEMSET                    FALSE
#endif    

#if !defined(OSUSE_PRINTF_P_FORMAT)
#define OSUSE_PRINTF_P_FORMAT           FALSE
#endif
                                    
/************************************************************ 
****                                                     ****
**                                                         **
Numeric Type Definitions:

**                                                         **
****                                                     ****
************************************************************/
#if   OSBYTES_OF_COUNTS == 1
typedef OStypeInt8u  OStypeCount;
#elif OSBYTES_OF_COUNTS == 2 
typedef OStypeInt16u OStypeCount;
#elif OSBYTES_OF_COUNTS == 4 
typedef    OStypeInt32u OStypeCount;
#else
typedef OStypeInt8u OStypeCount;
#endif 
    
#if   OSBYTES_OF_DELAYS == 1 
typedef OStypeInt8u  OStypeDelay;     
typedef OStypeInt8   OStypeInterval; 
#elif OSBYTES_OF_DELAYS == 2
typedef OStypeInt16u OStypeDelay;  
typedef OStypeInt16  OStypeInterval; 
#elif OSBYTES_OF_DELAYS == 4
typedef OStypeInt32u OStypeDelay;
typedef OStypeInt32  OStypeInterval; 
#else
typedef OStypeInt8u OStypeDelay;     
typedef OStypeInt8  OStypeInterval; 
#endif 

#define OStypeTS OStypeDelay /* synonymous */

#if   OSBYTES_OF_EVENT_FLAGS == 1 
typedef OStypeInt8u  OStypeEFlag;     
#elif OSBYTES_OF_EVENT_FLAGS == 2
typedef OStypeInt16u OStypeEFlag;  
#elif OSBYTES_OF_EVENT_FLAGS == 4
typedef OStypeInt32u OStypeEFlag;
#else
typedef OStypeInt8u OStypeEFlag;     
#endif 

#if   OSBYTES_OF_FRAMEP == 1      
typedef OStypeInt8u  OStypeFrameP;    
#elif OSBYTES_OF_FRAMEP == 2 
typedef OStypeInt16u OStypeFrameP; 
#elif OSBYTES_OF_FRAMEP == 4      
typedef OStypeInt32u OStypeFrameP;
#else
typedef OStypeInt8u  OStypeFrameP;          
#endif 

#if   OSBYTES_OF_TICKS == 1      
typedef OStypeInt8u  OStypeTick;    
#elif OSBYTES_OF_TICKS == 2 
typedef OStypeInt16u OStypeTick; 
#elif OSBYTES_OF_TICKS == 4      
typedef OStypeInt32u OStypeTick;
#else
typedef OStypeInt8u OStypeTick;          
#endif 

#if   OSBYTES_OF_SRGIE == 1      
typedef OStypeInt8u  OStypeSRGIE;    
#elif OSBYTES_OF_SRGIE == 2 
typedef OStypeInt16u OStypeSRGIE; 
#elif OSBYTES_OF_SRGIE == 4      
typedef OStypeInt32u OStypeSRGIE;
#else
typedef OStypeInt8u  OStypeSRGIE;          
#endif 

#if   OSTIMER_PRESCALAR > 65535
typedef OStypeInt32u OStypePS;  
#elif OSTIMER_PRESCALAR > 255
typedef OStypeInt16u OStypePS;  
#elif OSTIMER_PRESCALAR > 0
typedef OStypeInt8u OStypePS;  
#else
typedef OStypeInt8u OStypePS;
#endif 


/************************************************************
****                                                     ****
**                                                         **
Additional function attributes as necessary.

**                                                         **
****                                                     ****
************************************************************/
#include <salvomcg.h>


/************************************************************
****                                                     ****
**                                                         **
Port-specific typedefs.

These mainly have to do with differences among 8-bit
compilers w/regard to bitfields and pointer types.

**                                                         **
****                                                     ****
************************************************************/
#if OSUSE_CHAR_SIZED_BITFIELDS
typedef OStypeInt8u   OStypeBitField;       /* depends on whether    */
#else                                       /*  compiler follows     */
typedef OStypeInt16u  OStypeBitField;       /*  ANSI strictly. Also  */
                                            /*  related to some tar- */
                                            /*  gets' OSDispatch().  */ 
#endif 


typedef struct {                            /* status consists of:   */
    OStypeBitField prio:4;                  /*  4 bits of priority   */
    OStypeBitField state:3;                 /*  3 bits of state      */
    OStypeBitField yielded:1;               /*  1 yielded bit        */
    #if ( (OSCTXSW_METHOD == OSVIA_OSDISPATCH) \
      ||  (OSCTXSW_METHOD == OSVIA_OSDISPATCH_WLABEL) )
    OStypeBitField frameSize:8;             /*  8 bits of stack frame*/
                                            /*     size (only some   */
                                            /*     distributions)    */
    #endif
    } OStypeStatus;
        
typedef OStypeBitField OStypeStatusValue;   /* this is used where    */
                                            /*  a compiler can't     */
                                            /*  properly handle bit- */
                                            /*  field operations.    */
                                            /* Highly non-portable,  */
                                            /*  be careful!          */  
                                                  
typedef OStypeInt8u  OStypeLostTick;		/* no point in tracking  */
											/*  more than 8 bits of  */
											/*  lost ticks			 */

typedef OSMESSAGE_TYPE OStypeMsg;           /* usually void          */ 

typedef void (OSTASK_POINTER_TYPE * OStypeTFP) (void);


/************************************************************
****                                                     ****
**                                                         **
Port-specific context switcher support.

If the context-switcher used is OSCtxSw(), then there's no
need for labels.

If it's done in-line, then labels are required so that the
compiler can reference the "resume at" address.

**                                                         **
****                                                     ****
************************************************************/

#if (OSCTXSW_METHOD == OSVIA_OSCTXSW)

#define _OSLabel(a)
void OSCtxSw( void );
#if !defined(OS_Yield)
#define OS_Yield(label)                 OSCtxSw()
#endif


#elif (OSCTXSW_METHOD == OSVIA_OSDISPATCH)

#define _OSLabel(a)
void OSDispatch( void );
void OSCtxSw( void );
#if !defined(OS_Yield)
#define OS_Yield(label)                 OSCtxSw()
#endif


#elif ( (OSCTXSW_METHOD == OSRTNADDR_IS_PARAM) \
   ||   (OSCTXSW_METHOD == OSRTNADDR_IS_VAR) )
     
#if !defined(_OSLabel)
#define _OSLabel(a)                     void a (void);      
#endif


#elif (OSCTXSW_METHOD == OSVIA_OSDISPATCH_WLABEL)

void OSDispatch( void );
void OSCtxSw( OStypeTFP tFP );
#if !defined(_OSLabel)
#define _OSLabel(a)                     void a (void);      
#endif


#else 

#error salvo.h: OSCTXSW_METHOD not defined.

#endif
                                       

/************************************************************
****                                                     ****
**                                                         **
Bank specifiers and memory type for some compilers. Used for
objects and pointers to objects.

If OSLOC_ALL is undefined(i.e. user hasn't defined it in
salvocfg.h), it defaults to OSLOC_DEFAULT, defined in
portXyz.h. Else it's set by user in salvocfg.h.

Every undefined OSLOC_XYZ is set to OSLOC_ALL.

This allows the user to specify OSLOC_ALL and then explicitly
set individual ones independently.

MPLAB-C18 doesn't support OSLOC_XYZ because of the need for
explicit sections declared via #pragma udata access SecName.

**                                                         **
****                                                     ****
************************************************************/
#if OSCOMPILER == OSMPLAB_C18
#if OSMPLAB_C18_LOC_ALL_NEAR
#undef  OSLOC_ALL                        
#define OSLOC_ALL                        near
#else
#undef  OSLOC_ALL                        
#define OSLOC_ALL                        
#endif /* #if OSMPLAB_C18_LOC_ALL_NEAR */
#undef  OSLOC_COUNT
#define OSLOC_COUNT                     OSLOC_ALL
#undef  OSLOC_CTCB
#define OSLOC_CTCB                      OSLOC_ALL
#undef  OSLOC_DEPTH
#define OSLOC_DEPTH                     OSLOC_ALL
#undef  OSLOC_ECB
#define OSLOC_ECB                       OSLOC_ALL
#undef  OSLOC_EFCB
#define OSLOC_EFCB                      OSLOC_ALL
#undef  OSLOC_ERR
#define OSLOC_ERR                       OSLOC_ALL
#undef  OSLOC_LOGMSG
#define OSLOC_LOGMSG                    OSLOC_ALL
#undef  OSLOC_LOST_TICK
#define OSLOC_LOST_TICK                 OSLOC_ALL
#undef  OSLOC_MQCB
#define OSLOC_MQCB                      OSLOC_ALL
#undef  OSLOC_MSGQ
#define OSLOC_MSGQ                      OSLOC_ALL
#undef  OSLOC_PS
#define OSLOC_PS                        OSLOC_ALL
#undef  OSLOC_SIGQ
#define OSLOC_SIGQ                      OSLOC_ALL
#undef  OSLOC_TCB
#define OSLOC_TCB                       OSLOC_ALL
#undef  OSLOC_TICK
#define OSLOC_TICK                      OSLOC_ALL
#endif /* #if OSCOMPILER ... */


#if !defined(OSLOC_ALL)
#define OSLOC_ALL                       OSLOC_DEFAULT
#endif
                                        
#if !defined(OSLOC_COUNT)
#define OSLOC_COUNT                     OSLOC_ALL
#endif

#if !defined(OSLOC_CTCB)
#define OSLOC_CTCB                      OSLOC_ALL
#endif

#if !defined(OSLOC_DEPTH)
#define OSLOC_DEPTH                     OSLOC_ALL
#endif

#if !defined(OSLOC_ECB)
#define OSLOC_ECB                       OSLOC_ALL
#endif

#if !defined(OSLOC_EFCB)
#define OSLOC_EFCB                      OSLOC_ALL
#endif

#if !defined(OSLOC_ERR)
#define OSLOC_ERR                       OSLOC_ALL
#endif

#if !defined(OSLOC_LOGMSG)
#define OSLOC_LOGMSG                    OSLOC_ALL
#endif

#if !defined(OSLOC_LOST_TICK)
#define OSLOC_LOST_TICK                 OSLOC_ALL
#endif

#if !defined(OSLOC_MQCB)
#define OSLOC_MQCB                      OSLOC_ALL
#endif

#if !defined(OSLOC_MSGQ)
#define OSLOC_MSGQ                      OSLOC_ALL
#endif

#if !defined(OSLOC_PS)
#define OSLOC_PS                        OSLOC_ALL
#endif

#if !defined(OSLOC_SIGQ)
#define OSLOC_SIGQ                      OSLOC_ALL
#endif

#if !defined(OSLOC_TCB)
#define OSLOC_TCB                       OSLOC_ALL
#endif

#if !defined(OSLOC_TICK)
#define OSLOC_TICK                      OSLOC_ALL
#endif

    
/************************************************************
****                                                     ****
**                                                         **
Unqualified and qualified typedefs.

So far all the supported compilers follow ANSI by accepting
memory type qualifiers after the reserved types and before
the pointer *.

**                                                         **
****                                                     ****
************************************************************/
#define OStypeCharEcbP   unsigned char   OSLOC_ECB *
#define OStypeCharTcbP   unsigned char   OSLOC_TCB *
#define OStypeEcbP       OStypeEcb       OSLOC_ECB *
#define OStypeEfcbP      OStypeEfcb      OSLOC_EFCB *
#define OStypeMqcbP      OStypeMqcb      OSLOC_MQCB *
#define OStypeMsgP       OStypeMsg     *
#define OStypeMsgPP      OStypeMsg     * *
#define OStypeMsgQPP     OStypeMsg     * OSLOC_MSGQ *
#define OStypePrioAP     OStypePrioA     OSLOC_ECB *
#define OStypeTcbP       OStypeTcb       OSLOC_TCB *
#define OStypeTcbPP      OStypeTcb       OSLOC_TCB *  OSLOC_ECB *

#define OSgltypeCount    OStypeCount     OSLOC_COUNT 
#define OSgltypeDepth    OStypeDepth     OSLOC_DEPTH 
#define OSgltypeEcb      OStypeEcb       OSLOC_ECB 
#define OSgltypeEfcb     OStypeEfcb      OSLOC_EFCB
#define OSgltypeErr      OStypeErr       OSLOC_ERR
#define OSgltypeLostTick OStypeLostTick  OSLOC_LOST_TICK
#define OSgltypeLogMsg   char            OSLOC_LOGMSG
#define OSgltypeMqcb     OStypeMqcb      OSLOC_MQCB
#define OSgltypePrioA    OStypePrioA     OSLOC_ECB
#define OSgltypePS       OStypePS        OSLOC_PS
#define OSgltypeTcb      OStypeTcb       OSLOC_TCB
#define OSgltypeTick     OStypeTick      OSLOC_TICK

#define OSgltypeCTcbP    OStypeTcbP      OSLOC_CTCB
#define OSgltypeEcbP     OStypeEcbP      OSLOC_ECB
#define OSgltypeMsgQP    OStypeMsgP      OSLOC_MSGQ
#define OSgltypeSigQP    OStypeTcbP      OSLOC_SIGQ
#define OSgltypeTcbP     OStypeTcbP      OSLOC_ECB

#define OSgltypeFrameP   OStypeFrameP
#define OSgltypeSRGIE    OStypeSRGIE


/************************************************************ 
****                                                     ****
**                                                         **
OSEnter|LeaveCritical():
OSBegin|EndCriticalSection():
OSSuspend|ResumeCriticalSection():

Macros for entering and exiting critical regions of code.

OSBegin|EndCriticalSection() are essentially placeholders 
for OSEnter|LeaveCritical(), and are sometimes redefined
in the various modules to support special interrupt-related
issues. 

Compilers that support the monitor keyword use the
OSMONITOR_KEYWORD_PRE symbol as an extended keyword on each 
function that needs interrupts disabled, and therefore do
not need OSBegin|EndCriticalSection() macros inside the
function.

OSSuspend|ResumeCriticalSection() are special interrupt-
enabling and disabling macros, respectively, to be used
inside large functions where interrupts should not be
disabled for the duration. 

**                                                         **
****                                                     ****
************************************************************/
#if !defined(OSEnterCritical)
#define OSEnterCritical()               do { OSDi(); \
                                         OSDiHook(); \
                                         } while(0)
#endif
                                        
#if !defined(OSLeaveCritical)
#define OSLeaveCritical()               do { OSEiHook(); \
                                          OSEi(); \
                                        } while (0) 
#endif


#if OSMONITOR_KEYWORD_EXISTS
#define OSBeginCriticalSection()        
#define OSEndCriticalSection()          
#else
#define OSBeginCriticalSection()        OSEnterCritical()
#define OSEndCriticalSection()          OSLeaveCritical()
#endif                                        


#if !defined(OSResumeCriticalSection)
#define OSResumeCriticalSection()       OSEnterCritical()
#endif

#if !defined(OSSuspendCriticalSection)
#define OSSuspendCriticalSection()      OSLeaveCritical()
#endif


/************************************************************ 
****                                                     ****
**                                                         **
Task Priorities:

16 separate task priorities are supported, from 0 =
highest priority to 15 = lowest. If the idle task is
enabled, we exclude its priority (lowest, 15) from
the range of available priorities.

By default, idle task has a tID of 1.  However, since v2.2.0
and earlier had the OSIDLE_TASK_NUM default to OSTASKS, the
user can override this setting if necessary.

**                                                         **
****                                                     ****
************************************************************/
#if !OSDISABLE_TASK_PRIORITIES
#if defined(OSONLY_PRIO)
#undef  OSONLY_PRIO
#endif
#define OSHIGHEST_PRIO                  0
#define OSLOWEST_PRIO                   15
#else
#define OSONLY_PRIO                     0
#define OSHIGHEST_PRIO                  0
#define OSLOWEST_PRIO                   0
#endif

#define OSCT_ONE_SHOT                   0
#define OSCT_CONTINUOUS                 1
                                        
                                        
/************************************************************ 
****                                                     ****
**                                                         **
Task State Definitions:

 OSTCB_DESTROYED          uninitialized / dead. Uninitialized
                           only valid if compiler initializes all 
                           global vars to 0.
 OSTCB_TASK_STOPPED       task is stopped.
 OSTCB_TASK_DELAYED       task is delayed.
 OSTCB_TASK_WAITING       task is waiting for event.
 OSTCB_TASK_WAITING_TO    task is waiting for an event, with a timeout if
                           in an event queue. Waited for an event
                           and timed out if in eligible queue.
 OSTCB_TASK_ELIGIBLE      task is enqueued in the eligibel queue or 
                           running, normal.
 OSTCB_TASK_SIGNALED      task is enqueued in the eligible queue, waited 
                           an event that was signaled.
 OSTCB_CYCLIC_TIMER       tcb is holding a cyclic timer.
 
A task is running when it is the current task and its state 
is OSTCB_TASK_ELIGIBLE.

**                                                         **
****                                                     ****
************************************************************/
#define OSTCB_DESTROYED                 0
#define OSTCB_TASK_STOPPED              1
#define OSTCB_TASK_DELAYED              2
#define OSTCB_TASK_WAITING              3
#define OSTCB_TASK_WAITING_TO           4
#define OSTCB_TASK_ELIGIBLE             5
#define OSTCB_TASK_SIGNALED             6
#define OSTCB_CYCLIC_TIMER              7

#define OSTCB_TASK_RUNNING      8   /* this is never stored in */
                                    /*  the state, but is used */
                                    /*  by OSGetState[Task](). */


/************************************************************ 
****                                                     ****
**                                                         **
Generic No-timeout Definition:

**                                                         **
****                                                     ****
************************************************************/
#define OSNO_TIMEOUT                    0


/************************************************************ 
****                                                     ****
**                                                         **
Bit Masks:

Bit masks used to "extract" status or priority from the 
task control block.

By convention, masks preserve bits of interest and destroy 
those not of interest, via AND.

Three masks are not normally used -- rather, bitfields for
priority, state and running are defined in the task's
status byte, and are operated on as bitfields.

OSDONT_START_TASK is used with OSCreateTask() to leave the 
task in the stopped state after it has been created.

**                                                         **
****                                                     ****
************************************************************/
#define OSBITMASK_PRIO                  0x0F    
#define OSBITMASK_STATE                 0x70    
#define OSBITMASK_YIELDED               0x80

#define OSDONT_START                    0x80
#define OSDONT_START_TASK               0x80
#define OSDONT_START_CYCTMR             0x80
                                        

/************************************************************ 
****                                                     ****
**                                                         **
Error Codes:

**                                                         **
****                                                     ****
************************************************************/
#define OSNOERR                         0
#define OSERR                           1

#define OSERR_BAD_P                     2

#define OSERR_EVENT_NA                  3
#define OSERR_EVENT_FULL                4
#define OSERR_EVENT_CB_UNINIT           5
#define OSERR_EVENT_BAD_TYPE            6

#define OSERR_BAD_PRIO                  7
#define OSERR_BAD_STATE                 8

#define OSERR_BAD_CT                    9
#define OSERR_BAD_CT_MODE               10
#define OSERR_BAD_CT_DELAY              11
#define OSERR_CT_RUNNING                12
#define OSERR_CT_STOPPED                13


#define OSERR_NOYIELD                   1    /* return codes for */
#define OSERR_YIELD                     2    /*  OSWaitEvent().  */
#define OSERR_TIMEOUT                   4    /*  return value is */
#define OSERR_AVAILABLE                 8    /*  OR'd combo of   */
#define OSERR_SIGNALED                  16   /*  these values.   */
#define OSERR_SEVERE                    32   /* used internally  */


/************************************************************ 
****                                                     ****
**                                                         **
Defined Event Types:

Event types are always defined, but not necessarily
stored in the ecb.

**                                                         **
****                                                     ****
************************************************************/
#define OSEV_DESTROYED                  0   
#define OSEV_BINSEM                     1   
#define OSEV_EFLAG                      2    
#define OSEV_MSG                        3
#define OSEV_MSGQ                       4
#define OSEV_SEM                        5

#define OSANY_BITS                      1  /* bit positions */
#define OSALL_BITS                      2  /*  ""           */    
#define OSEXACT_BITS                    4  /*  ""           */ 

#define OSCLR_EFLAG                     1  /*  ""           */  
#define OSSET_EFLAG                     2  /*  ""           */  
                            

/************************************************************ 
****                                                     ****
**                                                         **
OS_Delay/DelayTS/Destroy/Replace/SetPrio/Stop/:

Macros for simple SALVO services that require a context 
switch.

Interrupt control follows the traditional pattern only inside
the called function. This may be incompatible with future
desired functionality, and may need to be brought into line
with what's going on in OSWaitXyz().

**                                                         **
****                                                     ****
************************************************************/
#if   OSENABLE_DELAYS && !OSENABLE_TICKS
#define OS_Delay(delay, label) { \
    OSDelay(delay); \
    OS_Yield(label); } 
#elif OSENABLE_DELAYS && OSENABLE_TICKS
#define OS_Delay(delay, label) { \
    OSDelay(delay, FALSE); \
    OS_Yield(label); } 
#endif


#if OSENABLE_DELAYS && OSENABLE_TICKS
#define OS_DelayTS(delay, label) { \
    OSDelay(delay, TRUE); \
    OS_Yield(label); }
#endif


#define OS_Destroy(label) { \
    OSDestroy(); \
    OS_Yield(label); }
    

#define OS_Replace(tFP, prio) { \
    OSCreateTask(tFP, OScTcbP, prio); \
    OSRtnToOSSched(); }
    

#define OS_SetPrio(prio, label)    { \
    OSSetPrio(prio); \
    OS_Yield(label); }
   
   
#if   OSENABLE_DELAYS && !OSENABLE_TICKS
#define OS_Stop(label) { \
    OSDelay(0); \
    OS_Yield(label); }
#elif OSENABLE_DELAYS && OSENABLE_TICKS
#define OS_Stop(label) { \
    OSDelay(0, FALSE); \
    OS_Yield(label); }
#else
#define OS_Stop(label) { \
    OSStop(); \
    OS_Yield(label); }
#endif


/************************************************************ 
****                                                     ****
**                                                         **
OSCreateBinSem(ecbP, binSem)
OSSignalBinSem(ecbP)
OS_WaitBinSem(ecbP, timeout, label)

OSCreateEflag(ecbP, efcbP, eFlag)
OSClrEFlag(ecbP, mask)
OSSetEFlag(ecbP, mask)
OS_WaitEFlag(ecbP, mask, options, timeout, label)

OSCreateMsg(ecbP, msgP)
OSSignalMsg(ecbP, msgP)
OS_WaitMsg(ecbP, msgP, timeout, label)

OSCreateMsgQ(ecbP, mqcbP, msgPP, size)
OSSignalMsgQ(ecbP, msgP)
OS_WaitMsgQ(ecbP, msgP, timeout, label)

OSCreateSem(ecbP, sem)
OSSignalSem(ecbP)
OS_WaitSem(ecbP, timeout, label)


Definitions for Salvo services implemented as macros that
call functions, and macros for more complex SALVO services 
that require a context switch.

Conditional interrupt control is accomplished inside of the
called function -- if resource is available (i.e. task does
not have to wait), interrupts will be re-enabled and task
will continue without context-switching. O/wise program
flows back to OSSched() with interrupts disabled.

**                                                         **
****                                                     ****
************************************************************/
/* here are the event services for the flattened case.    */
/*  They all have macro front-ends, and all go through    */
/*  event.c                                                */
#if OSCOMBINE_EVENT_SERVICES

/* BINSEM                                                */
#if OSENABLE_BINARY_SEMAPHORES
#define OSCreateBinSem(ecbP, binSem) \
  OSCreateEvent(ecbP, OSEV_BINSEM, binSem)
  
#define OSSignalBinSem(ecbP) \
  OSSignalEvent(ecbP, OSEV_BINSEM)
  
#if !OSENABLE_TIMEOUTS
#define OS_WaitBinSem(ecbP, timeout, label) \
    while ( OSWaitEvent(ecbP, OSEV_BINSEM) & OSERR_YIELD ) \
        OS_Yield(label)
#else        
#define OS_WaitBinSem(ecbP, timeout, label) \
    while ( OSWaitEvent(ecbP, OSEV_BINSEM, timeout) & OSERR_YIELD ) \
        OS_Yield(label)
#endif  
#endif


/* EFLAG                                                */
#if OSENABLE_EVENT_FLAGS
#define OSCreateEFlag(ecbP, efcbP, eFlag) \
  OSCreateEvent(ecbP, OSEV_EFLAG, efcbP, eFlag)
  
#define OSClrEFlag(ecbP, mask) \
  OSSignalEvent(ecbP, OSEV_EFLAG, mask, OSCLR_EFLAG)
  
#define OSSetEFlag(ecbP, mask) \
  OSSignalEvent(ecbP, OSEV_EFLAG, mask, OSSET_EFLAG)

#if !OSENABLE_TIMEOUTS  
#define OS_WaitEFlag(ecbP, mask, options, timeout, label) \
    while ( OSWaitEvent(ecbP, OSEV_EFLAG, mask, options) & OSERR_YIELD ) \
        OS_Yield(label)
#else        
#define OS_WaitEFlag(ecbP, mask, options, timeout, label) \
    while ( OSWaitEvent(ecbP, OSEV_EFLAG, timeout, mask, options) & OSERR_YIELD ) \
        OS_Yield(label)
#endif
#endif


/* MSG                                                   */
#if OSENABLE_MESSAGES
#define OSCreateMsg(ecbP, msgP) \
  OSCreateEvent(ecbP, OSEV_MSG, msgP)
  
#define OSSignalMsg(ecbP, msgP) \
  OSSignalEvent(ecbP, OSEV_MSG, msgP)
  
#if !OSENABLE_TIMEOUTS  
#define OS_WaitMsg(ecbP, msgP, timeout, label) \
    while ( OSWaitEvent(ecbP, OSEV_MSG, msgP) & OSERR_YIELD ) \
        OS_Yield(label)
#else
#define OS_WaitMsg(ecbP, msgP, timeout, label) \
    while ( OSWaitEvent(ecbP, OSEV_MSG, timeout, msgP) & OSERR_YIELD ) \
        OS_Yield(label)
#endif  
#endif


/* MSGQ                                                    */
#if OSENABLE_MESSAGE_QUEUES
#define OSCreateMsgQ(ecbP, mqcbP, msgPP, size) \
  OSCreateEvent(ecbP, OSEV_MSGQ, mqcbP, msgPP, size)
  
#define OSSignalMsgQ(ecbP, msgP) \
  OSSignalEvent(ecbP, OSEV_MSGQ, msgP)
  
#if !OSENABLE_TIMEOUTS  
#define OS_WaitMsgQ(ecbP, msgP, timeout, label) \
    while ( OSWaitEvent(ecbP, OSEV_MSGQ, msgP) & OSERR_YIELD ) \
        OS_Yield(label)
#else
#define OS_WaitMsgQ(ecbP, msgP, timeout, label) \
    while ( OSWaitEvent(ecbP, OSEV_MSGQ, timeout, msgP) & OSERR_YIELD ) \
        OS_Yield(label)
#endif  
#endif


/* SEM                                                    */
#if OSENABLE_SEMAPHORES
#define OSCreateSem(ecbP, sem) \
  OSCreateEvent(ecbP, OSEV_SEM, sem)
  
#define OSSignalSem(ecbP) \
  OSSignalEvent(ecbP, OSEV_SEM)
  
#if !OSENABLE_TIMEOUTS  
#define OS_WaitSem(ecbP, timeout, label) \
    while ( OSWaitEvent(ecbP, OSEV_SEM) & OSERR_YIELD ) \
        OS_Yield(label)
#else
#define OS_WaitSem(ecbP, timeout, label) \
    while ( OSWaitEvent(ecbP,  OSEV_SEM, timeout) & OSERR_YIELD ) \
        OS_Yield(label)
#endif  
#endif

/* here are the event services for the non-flattened     */
/*  case. Most of these are direct function calls, but    */
/*  a few have macro front-ends.                        */
#else /* #if OSCOMBINE_EVENT_SERVICES */

#define OSClrEFlag(ecbP, mask) \
  OSSignalEFlag(ecbP, mask, OSCLR_EFLAG)
  
#define OSSetEFlag(ecbP, mask) \
  OSSignalEFlag(ecbP, mask, OSSET_EFLAG)
  
#if !OSENABLE_TIMEOUTS

#define OS_WaitBinSem(ecbP, timeout, label) \
    while ( OSWaitBinSem(ecbP) & OSERR_YIELD ) \
        OS_Yield(label)

#define OS_WaitEFlag(ecbP, mask, options, timeout, label) \
    while ( OSWaitEFlag(ecbP, mask, options) & OSERR_YIELD ) \
        OS_Yield(label)
        
#define OS_WaitMsg(ecbP, msgP, timeout, label) \
    while ( OSWaitMsg(ecbP, msgP) & OSERR_YIELD ) \
        OS_Yield(label)
        
#define OS_WaitMsgQ(ecbP, msgP, timeout, label) \
    while ( OSWaitMsgQ(ecbP, msgP) & OSERR_YIELD ) \
        OS_Yield(label)
        
#define OS_WaitSem(ecbP, timeout, label) \
    while ( OSWaitSem(ecbP) & OSERR_YIELD ) \
        OS_Yield(label)

#else

#define OS_WaitBinSem(ecbP, timeout, label) \
    while ( OSWaitBinSem(ecbP, timeout) & OSERR_YIELD ) \
        OS_Yield(label)

#define OS_WaitEFlag(ecbP, mask, options, timeout, label) \
    while ( OSWaitEFlag(ecbP, mask, options, timeout) & OSERR_YIELD ) \
        OS_Yield(label)

#define OS_WaitMsg(ecbP, msgP, timeout, label) \
    while ( OSWaitMsg(ecbP, msgP, timeout) & OSERR_YIELD ) \
        OS_Yield(label)

#define OS_WaitMsgQ(ecbP, msgP, timeout, label) \
    while ( OSWaitMsgQ(ecbP, msgP, timeout) & OSERR_YIELD ) \
        OS_Yield(label)

#define OS_WaitSem(ecbP, timeout, label) \
    while ( OSWaitSem(ecbP, timeout) & OSERR_YIELD ) \
        OS_Yield(label)
                    
#endif /* #if OSENABLE_TIMEOUTS */

#endif /* #if OSCOMBINE_EVENT_SERVICES */


/* and here are the services that are independent of     */
/*  event service flattening.                            */

#if ( OSENABLE_EVENT_READING && !OSENABLE_EVENT_TRYING )
#define OSReadBinSem(ecbP) \
  OSReturnBinSem(ecbP)
  
#define OSReadEFlag(ecbP) \
  OSReturnEFlag(ecbP)
  
#define OSReadSem(ecbP) \
  OSReturnSem(ecbP)
  
#define OSReadMsg(ecbP) \
  OSReturnMsg(ecbP)
  
#define OSReadMsgQ(ecbP) \
  OSReturnMsgQ(ecbP)
#endif


#if ( OSENABLE_EVENT_READING && OSENABLE_EVENT_TRYING )
#define OSReadBinSem(ecbP) \
  OSReturnBinSem(ecbP, FALSE)
  
#define OSReadEFlag(ecbP) \
  OSReturnEFlag(ecbP)
  
#define OSReadSem(ecbP) \
  OSReturnSem(ecbP, FALSE)
  
#define OSReadMsg(ecbP) \
  OSReturnMsg(ecbP, FALSE)
  
#define OSReadMsgQ(ecbP) \
  OSReturnMsgQ(ecbP, FALSE)
  
#define OSTryBinSem(ecbP) \
  OSReturnBinSem(ecbP, TRUE)
  
#define OSTrySem(ecbP) \
  OSReturnSem(ecbP, TRUE)
  
#define OSTryMsg(ecbP) \
  OSReturnMsg(ecbP, TRUE)
  
#define OSTryMsgQ(ecbP) \
  OSReturnMsgQ(ecbP, TRUE)
#endif

#define OSGetPrio() OSGetPrioTask(OScTcbP)
#define OSGetState() OSGetStateTask(OScTcbP)

         
/************************************************************ 
****                                                     ****
**                                                         **
Task Control Block (tcb) structure:

 tcbP:          start / resume address of task
 ctxSwVect:     additional words required in some x86 
                 implementations to enable the scheduler to 
                 dispatch the task
 state:         b7:    0: task is not running
                       1: task is running / is the current task
                b6-b4: task state (OSTCB_DESTROYED, etc.)
                b3-b0: task priority
 nextTcbP:      ptr to next tcb in eligible or event queue
 prevTcbP:            "  previous         "
 ecbP:          ptr to ecb of event queue this task is in
 runStatus:     a copy of the current task's state when it was
                  made ready to tun.  Is used only while task
                  is RUNNING (i.e. is the current task). 
 nextDlyTcbP:   ptr to next tcb in delay queue
 prevDlyTcbP:     "    previous
 delay:         delay in ticks for waiting task
 
Note: for some implementations (e.g. x86), order is 
important!
 
**                                                         **
****                                                     ****
************************************************************/
struct tcb {
    #if OSCOMPILER == OSMIX_PC
    OStypeTFP tFP;
    long int ctxSwVect;    
    union {
        OStypeStatus      bits;
        OStypeStatusValue value;
    } status;    
        
    #else /* #if OSCOMPILER */
    union {
        OStypeStatus      bits;
        OStypeStatusValue value;
    } status;    
    OStypeTFP tFP;
    #endif /* #if OSCOMPILER */    
    
    
    #if OSUSE_ARRAYS
    #if OSOPTIMIZE_FOR_SPEED
    OStypePrioA prioABits;
    #endif /* #if OSOPTIMIZE_FOR_SPEED */
    #else
    OStypeTcbP nextTcbP;
    #endif /* #if OSUSE_ARRAYS */

            
    #if OSUSE_ARRAYS
    #if OSENABLE_DELAYS
    #if OSENABLE_TIMEOUTS
    union {                            
        OStypeEcbP ecbP;        
        OStypeStatus runStatus;  
        #if OSENABLE_CYCLIC_TIMERS
        OStypeDelay period;
        #endif      
    } u; 
    #endif /* #if OSENABLE_TIMEOUTS */    
    
    OStypeTcbP nextDlyTcbP;            
    #endif /* #if OSENABLE_DELAYS */
    #else /* #if OSUSE_ARRAYS */
    #if OSENABLE_TIMEOUTS
    union {                            
        OStypeEcbP ecbP;        
        OStypeStatus runStatus;        
        #if OSENABLE_CYCLIC_TIMERS
        OStypeDelay period;
        #endif      
    } u; 
    
    OStypeTcbP nextDlyTcbP;            

    #endif /* #if OSENABLE_TIMEOUTS */    
    #endif /* #if OSUSE_ARRAYS */


    /* interval services require system ticks. */
    #if OSENABLE_DELAYS && !OSENABLE_TICKS
    union {
        OStypeDelay delay;                    
    } dly; 
    #elif OSENABLE_DELAYS && OSENABLE_TICKS
    union {
        OStypeDelay delay;    
        OStypeTS    timestamp;                
    } dly;
    #endif
    
    
    #if OSENABLE_FAST_SIGNALING
    #if OSENABLE_MESSAGES || OSENABLE_MESSAGE_QUEUES
    OStypeMsgP msgP;
    #endif
    #endif
    
    
    /* tcb extensions */
    #if OSENABLE_TCBEXT0
    OStypeTcbExt0 tcbExt0;
    #endif
    #if OSENABLE_TCBEXT1
    OStypeTcbExt1 tcbExt1;
    #endif
    #if OSENABLE_TCBEXT2
    OStypeTcbExt2 tcbExt2;
    #endif
    #if OSENABLE_TCBEXT3
    OStypeTcbExt3 tcbExt3;
    #endif
    #if OSENABLE_TCBEXT4
    OStypeTcbExt4 tcbExt4;
    #endif
    #if OSENABLE_TCBEXT5
    OStypeTcbExt5 tcbExt5;
    #endif

};


/************************************************************ 
****                                                     ****
**                                                         **
Message Queue Control Block (mqcb) structure:

 count:     number of messages in queue
 inPP:        message insertion point pointer
 outPP:     message removal point pointer
 beginPP:   start of message queue 
 endPP:        end of message queue
 
The message queue is a simple ring buffer of pointers to
elements of type void. 

**                                                         **
****                                                     ****
************************************************************/
struct mqcb {
    OStypeMsgQSize  count;
    OStypeMsgQPP    inPP;
    OStypeMsgQPP    outPP;
    OStypeMsgQPP    beginPP;
    OStypeMsgQPP    endPP;
};



/************************************************************ 
****                                                     ****
**                                                         **
Event Flag Control Block (efcb) structure:

 flag:    flag
 
The key is a bitfield which is compared against the mask
with an operator. Some operators combine the key with mask2.

**                                                         **
****                                                     ****
************************************************************/
struct efcb {
    OStypeEFlag eFlag;
};


/************************************************************ 
****                                                     ****
**                                                         **
Event structure:

 binSem:  binary semaphore (0, 1)
 msgP:    message pointer (can point to anything)
 mqcbP:   message queue control block pointer
 sem:     counting semaphore (0, ..., MAX_SEM)
              

Event Control Block (ecb) structure:

 tcbP:    tcb ptr to first task in this event queue
 val:     union field for the "meat" of the event
 type:    type of event (semaphore, etc.) (optional)
 
**                                                         **
****                                                     ****
************************************************************/
typedef union {
    OStypeBinSem binSem;
    OStypeEfcbP  efcbP;
    OStypeMsgP   msgP;
    OStypeMqcbP  mqcbP;
    OStypeSem    sem;
} OStypeEvent;

 
struct ecb {
    #if OSUSE_ARRAYS
    OStypePrioA tcbP;
    #else
    OStypeTcbP tcbP;
    #endif
    
    OStypeEvent event;
     
    #if OSUSE_EVENT_TYPES
    OStypeInt8u type;
    #endif
};


/************************************************************ 
****                                                     ****
**                                                         **
Global Variables:

 OStcbArea[]:   storage for tcbs
 OSeligQP:      tcb ptr to queue of eligible tasks
 OScTcbP:       tcb ptr to current (RUNNING) task
 OSecbArea[]:   storage for ecbs
 OSmqcbArea[]:  storage for mqcbs
 OSdelayQP:     tcb ptr to queue of delayed tasks
 OSstkDepth:    current stack depth used by SALVO services
 OSmaxStkDepth: maximum  "
 OSerrs:        number of errors
 OSwarns:        "        warnings
 OStimeouts:     "        task timeouts
 OSctxSws:       "        context switches
 OSidleCtxSws:   "        idle task context switches
 OStimerTicks:   "        timer ticks
 OStimerPS:     current (dynamic) value of timer prescalar

**                                                         **
****                                                     ****
************************************************************/
#if !defined(__OSMEM_C)

#if OSUSE_ARRAYS
#if OSARRAY_SIZE_IS_BYTE
extern const OStypePrioA OSBits[8];
#else
extern const OStypePrioA OSBits[16]; 
#endif
#endif 

#if OSENABLE_TASKS
#if OSUSE_EXTERN_ARRAY_SIZES
extern OSgltypeTcb OStcbArea[OSTASKS];
#else
extern OSgltypeTcb OStcbArea[];
#endif
#if OSUSE_ARRAYS
extern OSgltypePrioA OSeligQP;
#else
extern OSgltypeTcbP OSeligQP;
#endif 
extern OSgltypeCTcbP OScTcbP; 
#endif


#if OSENABLE_EVENTS
#if OSUSE_EXTERN_ARRAY_SIZES
extern OSgltypeEcb OSecbArea[OSEVENTS];
#else
extern OSgltypeEcb OSecbArea[];
#endif
#endif

#if OSENABLE_SIGQ
extern OSgltypeSigQP OSsigQinP;
extern OSgltypeSigQP OSsigQoutP;
#endif


#if OSENABLE_EVENT_FLAGS && OSEVENT_FLAGS
#if OSUSE_EXTERN_ARRAY_SIZES
extern OSgltypeEfcb OSefcbArea[OSEVENT_FLAGS];
#else
extern OSgltypeEfcb OSefcbArea[];
#endif
#endif


#if OSENABLE_MESSAGE_QUEUES && OSMESSAGE_QUEUES
#if OSUSE_EXTERN_ARRAY_SIZES
extern OSgltypeMqcb OSmqcbArea[OSMESSAGE_QUEUES];
#else
extern OSgltypeMqcb OSmqcbArea[];
#endif
#endif


#if OSENABLE_DELAYS || OSENABLE_TIMEOUTS
extern OSgltypeTcbP OSdelayQP;
#endif


#if OSENABLE_STACK_CHECKING
extern OSgltypeDepth OSstkDepth, OSmaxStkDepth;
#endif


#if OSGATHER_STATISTICS && OSENABLE_COUNTS
extern OSgltypeCount OSctxSws;
#endif


#if OSGATHER_STATISTICS && OSENABLE_COUNTS && OSENABLE_IDLE_COUNTER
extern OSgltypeCount OSidleCtxSws;
#endif 


#if OSGATHER_STATISTICS && OSENABLE_TIMEOUTS
extern OSgltypeErr OStimeouts;
#endif


#if OSLOGGING
extern OSgltypeErr OSerrs, OSwarns;
#endif
 
 
#if OSLOG_MESSAGES > OSLOG_NONE
extern OSgltypeLogMsg OSlogMsg[80];
#endif


#if OSENABLE_TICKS
extern OSgltypeTick OStimerTicks;
#endif


#if OSENABLE_PRESCALAR
extern OSgltypePS OStimerPS;
#endif


#if OSENABLE_DELAYS
extern OSgltypeLostTick OSlostTicks;
#endif


#if ( (OSCTXSW_METHOD == OSVIA_OSDISPATCH) \
  &&  (OSMONITOR_KEYWORD_EXISTS == FALSE) )
extern OSgltypeSRGIE OSsrGIE;
#endif


#if ( (OSCTXSW_METHOD == OSVIA_OSDISPATCH) \
  ||  (OSCTXSW_METHOD == OSVIA_OSDISPATCH_WLABEL) )
extern OSgltypeFrameP OSframeP;
#endif


#if OSCTXSW_METHOD == OSRTNADDR_IS_VAR
extern OStypeRtnAddr OSrtnAddr;
#endif


#if ( OSTARGET == OSPIC18 ) && ( OSCOMPILER == OSIAR_ICC )

#define OSLOC_SAVEPIC18INTS __nonbanked 

#if OSPIC18_INTERRUPT_MASK & 0x80
extern OSLOC_SAVEPIC18INTS OStypeInt8u OSsavePIC18GIE;
#endif

#if OSPIC18_INTERRUPT_MASK & 0x40
extern OSLOC_SAVEPIC18INTS OStypeInt8u OSsavePIC18PEIE;
#endif

#undef OSLOC_SAVEPIC18INTS

#endif


#endif /* #if !defined(__OSMEM_C) */


#if !defined(__OSPORTV8_C)
#if OSCOMPILER == OSHT_V8C && OSTARGET == OSVAV8
extern unsigned char OSV8img_CTL_REG;
#endif
#endif /* #if !defined(__OSPORTV8_C) */


#if 0 // nobody references the license --- it's just for embedding into libs
#if !defined(__OSLICENSE_C)
extern const char OSlicense[];
#endif
#endif


/************************************************************ 
****                                                     ****
**                                                         **
Macros to directly access task and event fields.

Keep in mind that these are costly when the array 
index (i.e. tID or eID) is not a compile-time constant.                

**                                                         **
****                                                     ****
************************************************************/
#if 1
#define OSECBP(i)                &OSecbArea[(i-1)]
#define OSEFCBP(i)              &OSefcbArea[(i-1)]
#define OSMQCBP(i)              &OSmqcbArea[(i-1)]
#define OSTCBP(i)                &OStcbArea[(i-1)]
#else
#define OSECBP(i)                ((OSecbArea-1)+(i))
#define OSEFCBP(i)              ((OSefcbArea-1)+(i))
#define OSMQCBP(i)              ((OSmqcbArea-1)+(i))
#define OSTCBP(i)                ((OStcbArea-1)+(i))
#endif

#if OSENABLE_TIMEOUTS
#define OSTimedOut()             (OScTcbP->u.runStatus.state == OSTCB_TASK_WAITING_TO)
#endif 

#if !OSENABLE_EVENTS
#define OSAnyEligibleTasks()     (OSeligQP)
#else
#define OSAnyEligibleTasks()     (OSeligQP || OSsigQoutP)
#endif

#if OSENABLE_DELAYS && OSENABLE_TICKS
#define OSGetTS()                 OSGetTSTask(OScTcbP)
#define OSSetTS(timestamp)        OSSetTSTask(OScTcbP, timestamp)
#define OSSyncTS(interval)        OSSyncTSTask(OScTcbP, interval)
#endif

/************************************************************ 
****                                                     ****
**                                                         **
Tcb extension macros.

**                                                         **
****                                                     ****
************************************************************/
#if OSENABLE_TCBEXT0
#define OScTcbExt0        OScTcbP->tcbExt0
#define OStcbExt0(tcbP)    (tcbP)->tcbExt0
#endif

#if OSENABLE_TCBEXT1
#define OScTcbExt1        OScTcbP->tcbExt1
#define OStcbExt1(tcbP)    (tcbP)->tcbExt1
#endif

#if OSENABLE_TCBEXT2
#define OScTcbExt2        OScTcbP->tcbExt2
#define OStcbExt2(tcbP)    (tcbP)->tcbExt2
#endif

#if OSENABLE_TCBEXT3
#define OScTcbExt3        OScTcbP->tcbExt3
#define OStcbExt3(tcbP)    (tcbP)->tcbExt3
#endif

#if OSENABLE_TCBEXT4
#define OScTcbExt4        OScTcbP->tcbExt4
#define OStcbExt4(tcbP)    (tcbP)->tcbExt4
#endif

#if OSENABLE_TCBEXT5
#define OScTcbExt5        OScTcbP->tcbExt5
#define OStcbExt5(tcbP)    (tcbP)->tcbExt5
#endif


/************************************************************ 
****                                                     ****
**                                                         **
Stack-checking macros.

**                                                         **
****                                                     ****
************************************************************/
#if OSENABLE_STACK_CHECKING 
 #define OSIncCallDepth() \
     if ( ++OSstkDepth > OSmaxStkDepth ) OSmaxStkDepth++
 #define OSDecCallDepth() OSstkDepth--       
#else
 #define OSIncCallDepth()     
 #define OSDecCallDepth()    
#endif



/************************************************************ 
****                                                     ****
**                                                         **
OSIncErrs/Warns/Timeouts()

Incrementers for the errors, warnings and timeouts counters.

Suprisingly, 

    if ( a < 255 ) a++
    
is faster and smaller (by one instruction) than

    if ( ++a == 0 ) a--
    
with PIC C -- that's because the rollover is checked by 
putting the result into the w register. With no rollover, 
then increment the file register and keep the results there,
too. Of course this only works for 8-bit unsigned counters.

**                                                         **
****                                                     ****
************************************************************/
#if OSLOGGING
 #define OSIncErrs() \
   if ( OSerrs < 255 ) OSerrs++
 #define OSIncWarns() \
   if ( OSwarns < 255 ) OSwarns++
#else
 #define OSIncErrs()
 #define OSIncWarns()
#endif

#if OSGATHER_STATISTICS && OSENABLE_TIMEOUTS
 #define OSIncTimeouts() \
   if ( OStimeouts < 255 ) OStimeouts++
#else
 #define OSIncTimeouts()   
#endif


/************************************************************ 
****                                                     ****
**                                                         **
Debugging / activity logging macros.

Note that a conventional do { } while (0) approach doesn't
work well here because some compilers (e.g. IAR MSP430) do
not like to see any statements or parts of statements 
following the return keyword, e.g.

    do { return (OStypeErr) OSNOERR; } while (0);
    
results in "Unreachable statement(s)" ([20]) and "Non-void 
function: explicit "return" <expression>;  expected." [22]
warnings because of its construction.

**                                                         **
****                                                     ****
************************************************************/
 
#if OSLOGGING 

#if OSLOG_MESSAGES < OSLOG_ERRORS
#define OSErr(a, b)                 OSIncErrs()
#define OSErrRtn(a, b, c)           OSIncErrs(); \
                                    return c
#else
#define OSErr(a, b)                 OSLogErr(a, b)
#define OSErrRtn(a, b, c)           OSLogErr(a, b); \
                                    return c
#endif

#if OSLOG_MESSAGES < OSLOG_WARNINGS
#define OSWarn(a, b)                OSIncWarns()
#define OSWarnRtn(a, b, c)          OSIncWarns(); \
                                    return c
#else
#define OSWarn(a, b)                OSLogWarn(a, b) 
#define OSWarnRtn(a, b, c)          OSLogWarn(a, b); \
                                    return c
#endif

#if OSLOG_MESSAGES < OSLOG_ALL
#define OSMsg(a, b)
#define OSMsgRtn(a, b, c)           return c
#else
#define OSMsg(a, b)                 OSLogMsg(a, b)
#define OSMsgRtn(a, b, c)           OSLogMsg(a, b); \
                                    return c
#endif

#else /* #if OSLOGGING  */    

#define OSErr(a, b)
#define OSErrRtn(a, b, c)           return c
#define OSWarn(a, b)
#define OSWarnRtn(a, b, c)          return c
#define OSMsg(a, b)
#define OSMsgRtn(a, b, c)           return c

#endif /* #if OSLOGGING */        

    
/************************************************************ 
****                                                     ****
**                                                         **
Function prototypes:

Functions that need additional attributes (e.g. reentrant)
have their symbols defined elsewhere (e.g. salvomcg.h).

**                                                         **
****                                                     ****
************************************************************/

/************************************************************ 
** Event Services                                          **
************************************************************/
#if OSCOMBINE_EVENT_SERVICES

OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr    OSCreateEvent   ( OStypeEcbP      ecbP,           
                               OStypeEType     eType,
                               ... )
OSMONITOR_KEYWORD_POST_PROTO
OSCREATEEVENT_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr    OSSignalEvent   ( OStypeEcbP      ecbP,
                               OStypeEType     eType,
                               ... )
OSMONITOR_KEYWORD_POST_PROTO
OSSIGNALEVENT_ATTR ;


#if !OSENABLE_TIMEOUTS
OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr    OSWaitEvent     ( OStypeEcbP      ecbP, 
                               OStypeEType     eType,
                               ... )
OSMONITOR_KEYWORD_POST_PROTO ;
#else
OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr    OSWaitEvent     ( OStypeEcbP      ecbP, 
                               OStypeEType     eType,
                               OStypeDelay     timeout,
                               ... )
OSMONITOR_KEYWORD_POST_PROTO ;
#endif

#else /* #if OSCOMBINE_EVENT_SERVICES */

OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSCreateBinSem   ( OStypeEcbP      ecbP,            
                               OStypeBinSem    binSem )
OSMONITOR_KEYWORD_POST_PROTO
OSCREATEBINSEM_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSCreateEFlag    ( OStypeEcbP      ecbP, 
                               OStypeEfcbP     efcbP, 
                               OStypeEFlag     value )
OSMONITOR_KEYWORD_POST_PROTO
OSCREATEEFLAG_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSCreateMsg      ( OStypeEcbP      ecbP, 
                               OStypeMsgP      msgP )
OSMONITOR_KEYWORD_POST_PROTO
OSCREATEMSG_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSCreateMsgQ     ( OStypeEcbP      ecbP, 
                               OStypeMqcbP     mqcbP, 
                               OStypeMsgQPP    msgPP, 
                               OStypeMsgQSize  msgQSize )
OSMONITOR_KEYWORD_POST_PROTO
OSCREATEMSGQ_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSCreateSem      ( OStypeEcbP      ecbP, 
                               OStypeSem       sem )
OSMONITOR_KEYWORD_POST_PROTO
OSCREATESEM_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSSignalBinSem   ( OStypeEcbP      ecbP )
OSMONITOR_KEYWORD_POST_PROTO
OSSIGNALBINSEM_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSSignalEFlag    ( OStypeEcbP      ecbP, 
                               OStypeEFlag     mask,
                               OStypeOption    options )
OSMONITOR_KEYWORD_POST_PROTO
OSSIGNALEFLAG_ATTR ; 


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSSignalMsg      ( OStypeEcbP      ecbP, 
                               OStypeMsgP      msgP )
OSMONITOR_KEYWORD_POST_PROTO
OSSIGNALMSG_ATTR ; 


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSSignalMsgQ     ( OStypeEcbP      ecbP, 
                               OStypeMsgP      msgP )
OSMONITOR_KEYWORD_POST_PROTO
OSSIGNALMSGQ_ATTR ; 


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSSignalSem      ( OStypeEcbP      ecbP )
OSMONITOR_KEYWORD_POST_PROTO
OSSIGNALSEM_ATTR ;


#if !OSENABLE_TIMEOUTS

OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitBinSem     ( OStypeEcbP      ecbP )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitEFlag      ( OStypeEcbP      ecbP,
                               OStypeEFlag     mask,
                               OStypeOption    options )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitEvent      ( OStypeEcbP      ecbP, 
                               OStypeBoolean   avail )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitMsg        ( OStypeEcbP      ecbP, 
                               OStypeMsgPP     msgPP )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitMsgQ       ( OStypeEcbP      ecbP, 
                               OStypeMsgPP     msgPP )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitSem        ( OStypeEcbP      ecbP )
OSMONITOR_KEYWORD_POST_PROTO ;

#else

OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitBinSem     ( OStypeEcbP      ecbP, 
                               OStypeDelay     timeout )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitEFlag      ( OStypeEcbP      ecbP, 
                               OStypeEFlag     mask,
                               OStypeOption    options,
                               OStypeDelay     timeout )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitEvent      ( OStypeEcbP      ecbP, 
                               OStypeBoolean   avail, 
                               OStypeDelay     timeout )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitMsg        ( OStypeEcbP      ecbP, 
                               OStypeMsgPP     msgPP, 
                               OStypeDelay     timeout )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitMsgQ       ( OStypeEcbP      ecbP, 
                               OStypeMsgPP     msgPP, 
                               OStypeDelay     timeout )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSWaitSem        ( OStypeEcbP      ecbP, 
                               OStypeDelay     timeout ) 
OSMONITOR_KEYWORD_POST_PROTO ;


#endif /* #if !OSENABLE_TIMEOUTS */
#endif /* #if OSCOMBINE_EVENT_SERVICES */

OSMONITOR_KEYWORD_PRE_PROTO
OStypeMsgQSize  OSMsgQCount  ( OStypeEcbP      ecbP )
OSMONITOR_KEYWORD_POST_PROTO
OSMSGQCOUNT_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeMsgQSize  OSMsgQEmpty  ( OStypeEcbP      ecbP )
OSMONITOR_KEYWORD_POST_PROTO
OSMSGQEMPTY_ATTR ;

#if !OSENABLE_EVENT_TRYING    
                           
OSMONITOR_KEYWORD_PRE_PROTO
OStypeBinSem OSReturnBinSem  ( OStypeEcbP      ecbP )
OSMONITOR_KEYWORD_POST_PROTO
OSRETURNBINSEM_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeEFlag OSReturnEFlag    ( OStypeEcbP      ecbp )
OSMONITOR_KEYWORD_POST_PROTO
OSRETURNEFLAG_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeMsgP  OSReturnMsg      ( OStypeEcbP      ecbP )
OSMONITOR_KEYWORD_POST_PROTO
OSRETURNMSG_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeMsgP  OSReturnMsgQ     ( OStypeEcbP      ecbP,
                               OStypeMsgQSizeP countP )
OSMONITOR_KEYWORD_POST_PROTO
OSRETURNMSGQ_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeSem   OSReturnSem      ( OStypeEcbP      ecbP )
OSMONITOR_KEYWORD_POST_PROTO
OSRETURNSEM_ATTR ;

#else /* #if !OSENABLE_EVENT_TRYING  */

OSMONITOR_KEYWORD_PRE_PROTO
OStypeBinSem OSReturnBinSem  ( OStypeEcbP      ecbP,
                               OStypeBoolean   tryBinSem )
OSMONITOR_KEYWORD_POST_PROTO 
OSRETURNBINSEM_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeEFlag OSReturnEFlag    ( OStypeEcbP      ecbp )
OSMONITOR_KEYWORD_POST_PROTO
OSRETURNEFLAG_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeMsgP  OSReturnMsg      ( OStypeEcbP      ecbP,
                               OStypeBoolean   tryMsg )
OSMONITOR_KEYWORD_POST_PROTO
OSRETURNMSG_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeMsgP  OSReturnMsgQ     ( OStypeEcbP      ecbP,
                               OStypeBoolean   tryMsgQ )
OSMONITOR_KEYWORD_POST_PROTO
OSRETURNMSGQ_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeSem   OSReturnSem      ( OStypeEcbP      ecbP,
                               OStypeBoolean   trySem )
OSMONITOR_KEYWORD_POST_PROTO
OSRETURNSEM_ATTR ;

#endif /* #if !OSENABLE_EVENT_TRYING  */
                       

/***********************************************************
** Task Services                                          **
************************************************************/
OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSCreateTask     ( OStypeTFP       tFP, 
                               OStypeTcbP      tcbP, 
                               OStypePrio      prio )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSDestroyTask    ( OStypeTcbP      tcbP )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeState OSGetStateTask   ( OStypeTcbP      tcbP ) 
OSMONITOR_KEYWORD_POST_PROTO 
OSGETSTATETASK_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypePrio  OSGetPrioTask    ( OStypeTcbP      tcbP )
OSMONITOR_KEYWORD_POST_PROTO 
OSGETPRIOTASK_ATTR ;


OStypeErr   OSInitPrioTask   ( OStypeTcbP      tcbP,
                               OStypePrio      prio );

OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSSetPrioTask    ( OStypeTcbP      tcbP,
                               OStypePrio      prio ) 
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSStartTask      ( OStypeTcbP      tcbP ) 
OSMONITOR_KEYWORD_POST_PROTO
OSSTARTTASK_ATTR ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSStopTask       ( OStypeTcbP      tcbP )
OSMONITOR_KEYWORD_POST_PROTO ;


/************************************************************ 
** Current Task Services                                   **
************************************************************/
#if !OSENABLE_TICKS
OSMONITOR_KEYWORD_PRE_PROTO 
void        OSDelay          ( OStypeDelay     delay )
OSMONITOR_KEYWORD_POST_PROTO ;
#else
OSMONITOR_KEYWORD_PRE_PROTO 
void        OSDelay          ( OStypeDelay     delay,
                               OStypeBoolean   useTS )
OSMONITOR_KEYWORD_POST_PROTO ;
#endif


OSMONITOR_KEYWORD_PRE_PROTO
void        OSDestroy        ( void ) 
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
OStypeTS    OSGetTSTask      ( OStypeTcbP      tcbP ) 
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
void OSInterval              ( OStypeDelay     interval )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
void        OSSetPrio        ( OStypePrio      prio ) 
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
void        OSSetTSTask      ( OStypeTcbP      tcbP,
                               OStypeTS        timestamp )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
void        OSStop           ( void )
OSMONITOR_KEYWORD_POST_PROTO ;


OSMONITOR_KEYWORD_PRE_PROTO
void        OSSyncTSTask     ( OStypeTcbP      tcbP,
                               OStypeInterval  interval )
OSMONITOR_KEYWORD_POST_PROTO ;


/************************************************************ 
** General Services                                        **
************************************************************/
OSMONITOR_KEYWORD_PRE_PROTO
OStypeTick  OSGetTicks       ( void )
OSMONITOR_KEYWORD_POST_PROTO ;

void        OSIdlingHook     ( void );
void        OSInit           ( void );
void        OSRpt            ( void );

#if (OSCTXSW_METHOD == OSRTNADDR_IS_PARAM)
OSMONITOR_KEYWORD_PRE_PROTO
void        OSSaveRtnAddr    ( OStypeTFP       tFP );
OSMONITOR_KEYWORD_POST_PROTO
#endif

#if !OSUSE_INLINE_OSSCHED
OSMONITOR_KEYWORD_PRE_PROTO
void        OSSched          ( void )
OSMONITOR_KEYWORD_POST_PROTO ;
#endif

#if OSENABLE_OSSCHED_DISPATCH_HOOK
void		OSSchedDispatchHook( void );
#endif

#if OSENABLE_OSSCHED_ENTRY_HOOK
void		OSSchedEntryHook ( void );
#endif

#if OSENABLE_OSSCHED_RETURN_HOOK
void		OSSchedReturnHook ( void );
#endif

OSMONITOR_KEYWORD_PRE_PROTO
void        OSSetTicks       ( OStypeTick      tick )
OSMONITOR_KEYWORD_POST_PROTO ;

#if !OSUSE_INLINE_OSTIMER
OStypeErr   OSTimer          ( void );
#endif


/************************************************************ 
** Utility Services                                        **
************************************************************/
#if OSLOGGING
OStypeID    OSeID            ( OStypeEcbP      ecbP );
#endif

void        OSInitEcb        ( OStypeEcbP      ecbP );
void        OSInitTcb        ( OStypeTcbP      tcbP );

void        OSLogErr         ( char *          name, 
                               char *          msg  );
void        OSLogMsg         ( char *          name, 
                               char *          msg  );
void        OSLogWarn        ( char *          name, 
                               char *          msg  );
char       *OSMakeStr        ( char *          fmt, 
                               ...                  );

#if OSUSE_ARRAYS
OStypeTcbP  OSRtnTcbPfmA     ( OStypePrioA     array );
#endif

OStypeErr   OSTaskRunning    ( OStypeTcbP      tcbP );

OStypeErr   OSTaskUsed       ( OStypeTcbP      tcbP );

OStypeID    OStID            ( OStypeTcbP      tcbP );


/************************************************************ 
** Queue / Array Services                                  **
************************************************************/
OStypeErr   OSDelDelayQ      ( OStypeTcbP      tcbP );

#if OSUSE_ARRAYS
OStypeErr   OSDelPrioA       ( OStypeTcbP      tcbP, 
                               OStypePrioAP    prioAP );
#else
OStypeErr   OSDelPrioQ       ( OStypeTcbP      tcbP, 
                               OStypeTcbPP     tcbPP );
#endif

OStypeErr   OSDelTaskQ       ( OStypeTcbP      tcbP,
                               OStypeBoolean   delDelayedTask );
OStypeErr   OSInsDelayQ      ( OStypeTcbP      tcbP );
void        OSInsElig        ( OStypeTcbP      tcbP );

#if OSUSE_ARRAYS
OStypeErr   OSInsPrioA       ( OStypeTcbP      tcbP, 
                               OStypePrioAP    prioAP );
#else
OStypeErr   OSInsPrioQ       ( OStypeTcbP      tcbP, 
                               OStypeTcbPP     tcbPP );
#endif

OStypeErr   OSInsTaskQ       ( OStypeTcbP      tcbP );


/************************************************************ 
** Cyclic Timer  Services                                  **
************************************************************/
#if OSENABLE_CYCLIC_TIMERS
OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSCreateCycTmr   ( OStypeTFP       tFP, 
                               OStypeTcbP      tcbP, 
                               OStypeDelay     delay,
                               OStypeDelay     period,
                               OStypeCTMode    mode );
OSMONITOR_KEYWORD_POST_PROTO


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr OSCycTmrRunning    ( OStypeTcbP      tcbP );
OSMONITOR_KEYWORD_POST_PROTO                           


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSDestroyCycTmr  ( OStypeTcbP      tcbP );
OSMONITOR_KEYWORD_POST_PROTO


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSResetCycTmr    ( OStypeTcbP      tcbP );
OSMONITOR_KEYWORD_POST_PROTO


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr OSSetCycTmrPeriod  ( OStypeTcbP      tcbP,
							   OStypeDelay     period );
OSMONITOR_KEYWORD_POST_PROTO                           


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSStartCycTmr    ( OStypeTcbP      tcbP );
OSMONITOR_KEYWORD_POST_PROTO


OSMONITOR_KEYWORD_PRE_PROTO
OStypeErr   OSStopCycTmr     ( OStypeTcbP      tcbP );
OSMONITOR_KEYWORD_POST_PROTO
#endif

/************************************************************ 
** printf()-style debugging                                **
************************************************************/
void        OSPrintEcb       ( OStypeEcbP      ecbP );
void        OSPrintEcbP      ( OStypeEcbP      ecbP, 
                               OStypeBoolean   fixedWidth );
void        OSPrintTcb       ( OStypeTcbP      tcbP );
void        OSPrintTcbP      ( OStypeTcbP      tcbP, 
                               OStypeBoolean   fixedWidth );


/************************************************************ 
****                                                     ****
**                                                         **
Abbreviations list.

    address                  addr
    binary                   bin
    change                   change, chg
    check                    chk
    circular                 circ
    create                   create
    configuration            config
    context                  ctx
    current                  c
    cyclic timer             CT
    delay                    delay
    delete                   del
    depth                    depth
    destroy                  destroy
    disable                  dis
    disable interrupt(s)     di
    eligible                 elig
    enable                   en
    enable interrupt(s)      ei
    enter                    enter
    event                    event, ev, e
    event control block      ecb
    error                    err
    from                     fm
    function                 f
    function pointer         FP
    global                   gl
    global type              gltype
    identifier               ID
    include guard            IG
    initialize               init
    insert                   ins
    length                   len
    local                    l
    location                 loc
    maximum                  max
    message                  msg
    message queue            msgQ
    msgQ control block       mqcb
    minimum                  min
    not available            NA
    number                   num
    operating system         OS
    parameter                parm
    pointer                  ptr, p
    pointer to a pointer     pp
    prescalar                PS
    previous                 prev
    priority                 prio
    queue                    Q
    report                   rpt
    reset                    rst
    restore                  rstr
    return                   rtn
    save                     save
    scheduler                sched
    semaphore                sem
    set                      set
    signal                   signal
    stack                    stk
    statistics               stats
    string                   str
    switch                   sw        
    synchronize              sync            
    task                     task, ta, t
    task control block       tcb
    task function pointer    tFP
    tick                     tick
    timeout                  timeout
    timestamp                TS
    timer                    timer
    toggle                   tgl
    utility                  util
    value                    val
    version                  ver
    wait(ing) (for)          wait, w
    warning                  warn
    
**                                                         **
****                                                     ****
************************************************************/
 
  
/************************************************************ 
****                                                     ****
**                                                         **
Various macros

OSInitTcb/Ecb() normally would use memset(), but banking
issues in the PICs prevent their use there.

OSInsElig() puts the specified task into the eligible
queue. When in use as a macro, it reduces the call ... rtn
depth by 1.

**                                                         **
****                                                     ****
************************************************************/
#if OSUSE_MEMSET
#define OSInitTcb(a) memset((void *)a, '\0', sizeof(OStypeTcb))
#define OSInitEcb(a) memset((void *)a, '\0', sizeof(OStypeEcb))
#endif



#if OSUSE_ARRAYS
#define OSDelDelay(tcbP)             OSDelDelayQ(tcbP)
#define OSDelPrio(tcbP, method)      OSDelPrioA(tcbP, method)
#define OSInsDelay(tcbP)             OSInsDelayQ(tcbP)
#define OSInsPrio(tcbP, method)      OSInsPrioA(tcbP, method)
#else /* #if OSUSE_ARRAYS */
#define OSDelDelay(tcbP)             OSDelDelayQ(tcbP)
#define OSDelPrio(tcbP, method)      OSDelPrioQ(tcbP, method)
#define OSInsDelay(tcbP)             OSInsDelayQ(tcbP)
#define OSInsPrio(tcbP, method)      OSInsPrioQ(tcbP, method)
#endif /* #if OSUSE_ARRAYS */


#if OSUSE_OSINSELIG_MACRO
 #if OSUSE_ARRAYS && OSOPTIMIZE_FOR_SPEED
  #define OSInsElig(tcbP) { \
    tcbP->status.bits.state = OSTCB_TASK_ELIGIBLE; \
    OSeligQP |= tcbP->prioABits; }
 #else
  #define OSInsElig(tcbP) { \
    tcbP->status.bits.state = OSTCB_TASK_ELIGIBLE; \
    OSInsPrio(tcbP, &OSeligQP); }
 #endif
#endif /* #if OSUSE_OSINSELIG_MACRO */


/* if a task is waiting this event, remove it from the  */
/*  event's waiting queue and put it in the signaled    */
/*  queue. Used in OSSignalXyz().                       */
/* The task's nextTcbP must be cleared here.            */
#define OSInsSigQ(a, b) do { \
  if ( OSsigQoutP == 0 ) \
      OSsigQoutP          =           a; \
  else \
      OSsigQinP->nextTcbP =           a; \
  OSsigQinP               =           a; \
  b->tcbP                 = a->nextTcbP; \
  a->nextTcbP             =        NULL; \
  } while (0)


/************************************************************ 
****                                                     ****
**                                                         **
End of salvo.h.

**                                                         **
****                                                     ****
************************************************************/

#endif /* #if !defined(__SALVO_H) */
