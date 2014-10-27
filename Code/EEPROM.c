#include "Common.h"

//! Send int to eeprom
void sendEep(int number, int address){
    unsigned char lowNum = number & 0xFF;
    unsigned char highNum = number >> 8;

    Write_b_eep(address,  highNum);     //! Write into EEPROM
    address++;                          //! Go to next EEP address
    Busy_eep();                         //! Wait until ready, checks status of EECON1 register
    Write_b_eep(address,  lowNum);      //! Write into EEPROM
    address++;                          //! Go to next EEP address
    Busy_eep();                         //! Wait until ready, checks status of EECON1 register

}

//! Return int from eeprom, send address of first bit
int readEep(int address){
    int number;
    unsigned char lowNum;
    unsigned char highNum;

    highNum = Read_b_eep(address);      //! Read byte from internal eep
    address++;
    lowNum = Read_b_eep(address);

    number = (highNum<<8 | lowNum);
    return number;
}