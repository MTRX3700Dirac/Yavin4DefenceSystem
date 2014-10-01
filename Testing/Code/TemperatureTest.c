

#include <p18f452.h>
#include "ConfigRegs18f452.h"

void configureAD(void);

void main (void)
{
        int tempRaw;
        int tempmV;
        int offset; //0mV at 2 degrees??
        int sample_count = 0;
	configureAD();
 while(1){
        ADCON0bits.GO = 1;

        while(ADCON0bits.GO_NOT_DONE == 1)
        {
        }

        tempRaw = ADRESH + ADRESL;
        tempmV  = tempRaw*4.8828 + offset; //each incrememnt of ADRES is 4.88mV
                                       //
        sample_count++;

        
	}


}
void configureAD(void){
    
    DDRAbits.TRISA1 = 1;
    //Write the configuration values into the configuration registers
    ADCON1 = 0xC4;
    ADCON0 = 0b10001101;

}