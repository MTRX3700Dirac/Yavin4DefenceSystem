/* 
 * File:   Temp.h
 * Author: Grant
 *
 * Created on 17 September 2014, 2:16 PM
 */

//External public access function prototypes
extern void configureTemp(void);
extern unsigned char rawTemp(void);
extern unsigned char readTemp(void);
extern unsigned char readTempx2(void);
extern void calibrateTemp(unsigned char reference);
extern unsigned char getTemp(void);
