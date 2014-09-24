/* 
 * File:   Temp.h
 * Author: Grant
 *
 * Created on 17 September 2014, 2:16 PM
 */

//External public access function prototypes
extern unsigned char rawTemp(void);
extern unsigned char readTemp(void);
extern unsigned char readTempx2(void);
extern unsigned char getTemp(void);
extern void calibrateTemp(unsigned char reference);

//The temperature sample time in system ticks
#define TEMP_SAMPLE_PERIOD 1000