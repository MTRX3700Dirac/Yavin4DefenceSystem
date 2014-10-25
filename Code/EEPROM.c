//
//unsigned char ReadEEPROM(unsigned char address){
//    EECON1=0;                   //ensure CFGS=0 and EEPGD=0
//    EEADR = address;
//    EECON1bits.RD = 1;
//    return(EEDATA);
//}
//
//void WriteEEPROM(unsigned char address,unsigned char data){
//char SaveInt;
//    SaveInt=INTCON;             //save interrupt status
//    EECON1=0;                   //ensure CFGS=0 and EEPGD=0
//    EECON1bits.WREN = 1;        //enable write to EEPROM
//    EEADR = address;            //setup Address
//    EEDATA = data;              //and data
//    INTCONbits.GIE=0;           //No interrupts
//    EECON2 = 0x55;              //required sequence #1
//    EECON2 = 0xaa;              //#2
//    EECON1bits.WR = 1;          //#3 = actual write
//    INTCON=SaveInt;             //restore interrupts
//    while(!PIR2bits.EEIF);      //wait until finished
//    EECON1bits.WREN = 0;        //disable write to EEPROM
//}


//microchip code, not ready yet

//* The Processor starts with the External Crystal (8 Mhz).
//**********************************************************************/

//#define USE_OR_MASKS
//#include <p18cxxx.h>
//#include "EEP.h"
//
//unsigned char  EEPWrite[15] = "MICROCHIP_TECH", EEPRead[15],Error=0 ;
//
//void main(void)
//{
//    unsigned char q=0;
//	unsigned int  address;
//
//		address = 0x0200;
//
//      /* Write single byte to Internal EEP*/
//	  for(q=0;q<16;q++)
//	  {
//      Write_b_eep (address, EEPWrite[q]);	// write into to EEPROM
//	  address++;							//increment the address of EEPROM to next location
//      /* Checks & waits the status of ER bit in EECON1 register */
//      Busy_eep ();
//	  }
//
//	  address = 0x0200;		// initialize the starting address
//	  Error = 0;			//clear the error flag
//      /* Read single byte from Internal EEP*/
//	  for(q=0;q<16;q++)
//	  {
//      EEPRead[q] = Read_b_eep (address++);		//read the EEPROM data written previously from corresponding address
//	  if ( EEPRead[q] != EEPWrite[q] )			//check if the data read abck is same as that was written
//	  {
//		Error=1;								//if the data read/ write match does not occur, then flag the error status
//		while(1);								//error occured
//	  }
//	  }
//
//	  while(1);						//End of program
// }
//
//
//
