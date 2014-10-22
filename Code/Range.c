/*! ****************************************************************************
 * File:   Range.c
 * Author: Grant
 *
 * Description:
 * Contains all the functionality for the range module. All variables and settings
 * concerning the range module including the the max distance, timeouts etc are
 * private to this module. The interface functions allow all valid access to the module.
 *
 * Duties:
 *      -Interface to the IR and Ultrasonic sensors
 *      -Read the range from the IR and ultrasonic sensors
 *      -Fuse distances from the IR and ultrasonic sensors
 *      -Calibrate the IR and ultrasonic sensors
 *
 * Functions: 
 *
 * Created on 15 September 2014, 11:27 AM
 *******************************************************************************/

#include "Common.h"
#include "Temp.h"


//(Approximate) speed of sound calculation macro
#define SPD_SND(T) (DIV_1024(T * (unsigned int)614) + 331)
#define IR_CONV(ad) ((unsigned long)135174 / (ad) - 28)

#ifdef MNML
#define ULTRA_CONV(tme, T) DIV_65536(tme * (unsigned long)(DIV_65536((unsigned long)519078 * T) + (unsigned long)4362)) - 18
#else
#define ULTRA_CONV(tme, T) DIV_65536(tme * (unsigned long)(DIV_65536((unsigned long)1297695 * T) + (unsigned long)10905)) - 18
#endif

#define NUM_IR_READS 10 //The number of IR reads per measurement

//Hardware Related macros
#define INIT_PIN PORTCbits.RC3
#define INIT_TRIS TRISCbits.RC3
#define CCP1_INPT TRISCbits.RC2

//Static calibration offset
static signed int calibration_offset = 0;

//Flag for performing an ultrasonic measurment
volatile static char measuringUS = 0;

//Static variable to store the range
static unsigned int lastRange = 0;

//Calibration offsets
static signed int calibration_offset_IR = 0;
static signed int calibration_offset_US = 0;

static TargetState current_target_state;

//Private function prototypes:
static void beginUS(void);
unsigned int rangeIR(void);
static unsigned int rangeUS(unsigned char temp);

void configureRange(void);

static unsigned int sampleIR(char numSamples);

/*! **********************************************************************
 * Function: configureAD(void)
 *
 * Include: Range.h
 *
 * Description: Configures the ADC,
 * In ADCON1, we set right-justified mode, and select AN0 as the input channel.
 * In ADCON0, we set a sample rate of Fosc/8, select AN0, and enable the ADC.
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configureAD(void)
{
    int i = 0;
    TRISA = 0xFF;

    //Write the configuration values into the configuration registers
    ADCON2bits.ADFM = 1;    //right justified
    ADCON1 = 0x8C;      // ADFM set, AN0 AN1 and AN2 analogue input
    ADCON0 = 0x41;
    
    //Arbitrary wait period to allow the ADC to initialise
    for (i = 0; i < 1000; i++);
}

/*! **********************************************************************
 * Function: configureRange(void)
 *
 * Include: Range.h
 *
 * Description: Configures the Range module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configureRange(void)
{
    unsigned char config;
    
    INIT_PIN = 0;

    //Enable global interrupts and interrupt priority
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    RCONbits.IPEN = 1;

    readTemp();

    //Make sure the AD is configured
    configureAD();

    CCP1_INPT = 1;
    INIT_TRIS = 0;  //Make the INIT

    //Open  Timer
    config = T1_16BIT_RW & T1_SOURCE_INT & T1_OSC1EN_OFF & T1_PS_1_1 & T1_SYNC_EXT_OFF &TIMER_INT_ON;
    OpenTimer1(config);

    //Configure CCP Source timer
//    config = T1_CCP1_T3_CCP2;
//    SetTmrCCPSrc(config);

    config = CAPTURE_INT_ON & CAP_EVERY_RISE_EDGE;

    //CloseCapture1, which will clear any interrupt flags etc
    CloseCapture1();

    //Open the input capture on compare1
    OpenCapture1(config);
}

/*! **********************************************************************
 * Function: beginUS(void)
 *
 * Include: ultrasonic.h
 *
 * Description: starts a scan on the ultrasonic sensor
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
static void beginUS(void)
{
    CCPR1H = 0;
    CCPR1L = 0;
    //Set the INIT_PIN high to begin ultrasonic 'read'
    INIT_PIN = 1;

    //Clear the timer, so the CCP input value is the delay
    TMR1H = 0;
    TMR1L = 0;

    PIE1bits.CCP1IE = 1;

    //Set the measuring flag
    measuringUS = 1;
}

/*! **********************************************************************
 * Function: rangeUS(unsigned char temp)
 *
 * Include: ultrasonic.h
 *
 * Description: Returns the result of the ultrasonic read (zero if no target
 *              found). Will poll until measurement is complete.
 *
 * Arguments: tempx2 - 2x the temperature in deg Celsius
 *
 * Returns: Distance in mm (unsigned int)
 *************************************************************************/
static unsigned int rangeUS(unsigned char temp)
{
    unsigned int range;
    unsigned long int t;
    //Continue to poll while measurement is still in progress
    while (measuringUS);

    #ifdef MNML
    if (CCPR1 < 0x1770) return 0;

    //Perform calculation (ReadCapture in us, speed of sound in m/s->um)
    // um/1024 = ~mm

    t = DIV_4096((unsigned long int) CCPR1 * (unsigned long int) 285) - 18;
    
    #else
    if (CCPR1 < 5DC) return 0;

    //Perform calculation (ReadCapture in us, speed of sound in m/s->um)
    // um/1024 = ~mm

    t = DIV_4096((unsigned long int) CCPR1 * (unsigned long int) 712) - 18;
    #endif

    range = (unsigned int) t;
    
    return range;
}

/*! **********************************************************************
 * Function: rangeISR(void)
 *
 * Include: ultrasonic.h
 *
 * Description: Called when an range related interrupt is fired, acts
 *              as the service routine for the rangefinding module.
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void rangeISR(void)
{
    if (CCP1_INT && CCPR1 > 0x5DC)
    {   //Checks if the CCP2 module fired the interrupt
        measuringUS = 0;
        INIT_PIN = 0;
        PIE1bits.CCP1IE = 0;
    }
    if (TMR1_INT)
    {
        measuringUS = 0;
        CCPR1 = 0;
        INIT_PIN = 0;
        PIR1bits.TMR1IF = 0;
        PIE1bits.TMR1IE = 0;
    }
    CCP1_CLEAR;
}

/*! **********************************************************************
 * Function: calibrateRange(unsigned int reference)
 *
 * Include:
 *
 * Description: Calibrates the range of both the IR and ultrasonic sensors
 *              based on a given range.
 *
 * Arguments: reference - The distance in mm to calibrate the current
 *                        measurements from
 *
 * Returns: None
 *************************************************************************/
void calibrateRange(unsigned int reference)
{
    unsigned char temp;
    unsigned int range_US, range_IR, range;

    //Begin the Ultrasonic measurement
    configureRange();
    beginUS();

    //Read the temperature
    temp = readTemp();

    //Measure the IR range
    range_IR = rangeIR();

    //Read the result from the Ultrasonc sensor
    range_US = rangeUS(temp);

    //Check if valid data was returned by the sensors before they perform a calibration
    if (current_target_state != NO_TARGET && current_target_state != CLOSE_RANGE)
    {
        calibration_offset_US = reference - range_US;
    }
    if (current_target_state == GOOD_TRACK)
    {
        calibration_offset_IR = reference - range_IR;
    }
}

/*! **********************************************************************
 * Function: speed_sound(unsigned char tempx2)
 *
 * Include:
 *
 * Description: Returns the calibration offset to calculate the raw data
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
unsigned int rawRange(void)
{
    return lastRange;
}

/*! **********************************************************************
 * Function: range()
 *
 * Include:
 *
 * Description: Uses the IR and Ultrasonic sensors to find the range
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
unsigned int range(void)
{
    //unsigned int i;
    unsigned char temp;
    unsigned int range_US, range_IR, range;

    configureRange();
    
    //Begin the Ultrasonic measurement
    beginUS();

    //Read the temperature
    //temp = getTemp();
    temp = 25;

    //Measure the IR range
    range_IR = rangeIR();

    //Read the result from the Ultrasonc sensor
    range_US = rangeUS(temp);

    //Check which sensor(s) have observed a target
    if (range_US && range_IR)
    {
        //Calibrate the sensors
        range_US += calibration_offset_US;
        range_IR += calibration_offset_IR;

        // CASE 1: Range: 150-450mm
        // Ignore US reading as it is inaccurate at these ranges
        if (range_IR >= 150 && range_IR <= 450)
        {
            range = range_IR;
             current_target_state = CLOSE_RANGE;
        }
        // CASE 2: Range: 1m - 1.5m
        // Don't trust the IR ranges much
        else if (range_US >= 1000 && range_IR >=1000)
        {
            // @TODO Implement IR in here a little?
            range = range_US;
            current_target_state = OUT_OF_IR;
        }
        else
        {
            // CASE 3: Range: 450mm - 1m
            // Average the ultrasonic and IR ranges
            // TODO: Do we want to average these completely?
            range = DIV_2(range_US + range_IR);
            current_target_state = GOOD_TRACK;
        }
        
    }
    // CASE 4: Range: 1.5m+
    // Rely on Ultrasound
    else if (range_US)
    {
        //Calibrate the ultrasonic range
        range_US += calibration_offset_US;
       
        range = range_US;

        //Check whether No IR is because out of IR range, or just bad direction
        if (range > 1500) current_target_state = OUT_OF_IR;
        else current_target_state = BAD_DIR;
    }
    else if (range_IR)
    {
        //Calibrate the IR range
        range_IR += calibration_offset_IR;
        
        range = range_IR;
        current_target_state = CLOSE_RANGE;
    }
    else
    {
        // @TODO: Report Error?
        range = 0;
        current_target_state = NO_TARGET;
    }
    lastRange = range;

    //for (i = 0;i < 50000;i++);
    return range;
}

/*! **********************************************************************
 * Function: rangeIR(void)
 *
 * Include: 
 *
 * Description: Reads the range from the IR Sensor
 *
 * Arguments: None
 *
 * Returns: Range (in mm) as an unsigned int.
 *
 * Remark: Returns 0 if there is no target found
 *************************************************************************/
unsigned int rangeIR(void)
{
    unsigned int ad_result;
    unsigned int range;

    ad_result = sampleIR(10);

    //Return 0 if there is no target detected
    if (ad_result < 100) return 0;

    //Convert voltage (0-5v) into range (mm)
    range = IR_CONV(ad_result);

    return range;
}

/*! **********************************************************************
 * Function: rangeUS(void)
 *
 * Include:
 *
 * Description: performs an ultrasonic range reading.
 * Pins:
 *
 * Arguments: None
 *
 * Returns: the average of the samples
 *************************************************************************/
unsigned int rangeUltrasonic(void)
{
    unsigned int rng;

        configureRange();

        beginUS();

        rng = rangeUS(25);

        INIT_PIN = 0;
        CloseCapture1();
        CloseTimer1();

        return rng;

}

/*! **********************************************************************
 * Function: sampleIR(void)
 *
 * Include:
 *
 * Description: takes numSamples samples of the IR sensor and returns the average
 *
 * Arguments: None
 *
 * Returns: the average of the samples
 *************************************************************************/
static unsigned int sampleIR(char numSamples)
{
    unsigned long int sum = 0;
    unsigned int temp;
    char i = 0;
    
    //Multiplex onto the IR sensor
    SetChanADC(ADC_IR_READ);

    //Perform numSamples samples
    for (i = 0; i < numSamples; i++)
    {
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_NOT_DONE);
        temp = ADRES >> 6;
        sum += temp;
    }

    //Average all samples taken
    temp = sum / (unsigned int)numSamples;
    return temp;
}

/*! **********************************************************************
 * Function: getTargetState(void)
 *
 * Include: Range.h
 *
 * Description: Returns the target state from the last range reading. E.g.
 *              Good track, or direction not quite correct as US returned,
 *              but IR didn't and was within IR range etc.
 *
 * Arguments: None
 *
 * Returns: the target state
 *************************************************************************/
TargetState getTargetState(void)
{
    return current_target_state;
}

/*! **********************************************************************
 * Function: readTargetState(void)
 *
 * Include: Range.h
 *
 * Description: Does the same thing as getTargetState, but actually performs
 *              a range() read
 *
 * Arguments: None
 *
 * Returns: the target state
 *************************************************************************/
TargetState readTargetState(void)
{
    unsigned i = 0;
    range();
    //for (i = 0; i < 10000; i++);
    return getTargetState();
}