/* 
 * File:   ultrasonic.h
 * Author: Grant
 *
 * Description: Contains the public interface for the ultrasonic module
 *
 * Created on 15 September 2014, 11:24 AM
 */

//Ultrasonic module interrupt macro
//#define RANGE_INT  (PIR1bits.CCP1IF && PIE1bits.CCP1IE) || (PIR1bits.CCP2IF && PIE1bits.CCP2IE)
#define RANGE_INT 0

//External declarations of the public access functions
extern void configureAD(void);
extern unsigned int range();
extern void rangeISR(void);
extern void calibrateRange(signed int distance);
extern signed int rawRange(void);

extern unsigned int rangeIR(void);
