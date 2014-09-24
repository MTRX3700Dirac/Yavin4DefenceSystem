/************************************************************ 
Copyright (C) 1995-2002 Pumpkin, Inc. and its
Licensor(s). Freely distributable.

$Source: C:\\RCS\\d\\salvo\\inc\\salvoprg.h,v $
$Author: aek $
$Revision: 3.5 $
$Date: 2003-06-11 15:44:58-07 $

This file is used to include / inject compiler-specific 
pragmas where needed in the Salvo code. 
    
See comments in salvomcg.h on why this file doesn't have
include guards.


************************************************************/


/************************************************************
****                                                     ****
**                                                         **


**                                                         **
****                                                     ****
************************************************************/
#if defined(__OSMEM_C) 

	/* prevent Salvo global objects from being  		*/
	/*  initialized. This "lasts" for just the 			*/
	/*  immediately-following object.					*/
	#if   ( OSCOMPILER == OSIAR_ICC ) && ( OSTARGET == OSPIC18 ) 
	
    #pragma object_attribute=OSIAR_PIC18_ATTR_ALL
    
    #if !defined(OSIAR_PIC18_ATTR_ALL)
    #error salvoprg.h: OSIAR_PIC18_ATTR_ALL undefined.
    #endif
    
    #endif

#endif 

