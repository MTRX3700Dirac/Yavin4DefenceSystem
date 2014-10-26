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
#include <delays.h>

//ONLY FOR RANGE TESTING PURPOSES
#include "Serial.h"
static void transRange(unsigned int us, unsigned int ir);
//

///Converts AD reading into IR range
#define IR_CONV(ad) ((unsigned long)135174 / (ad) - 28)

///Converts a time delay (in clock cycles) and a temperature into an ultrasonic distance
///Uses a linear appoximation of the speed of sound to temperature relation, which changes the gradient of the Ultrasonic calibration
#ifdef MNML
#define ULTRA_CONV(tme, T) DIV_65536(tme * (unsigned long)(DIV_65536((unsigned long)519078 * T) + (unsigned long)4362)) - 18
#else
#define ULTRA_CONV(tme, T) DIV_65536(tme * (unsigned long)(DIV_65536((unsigned long)1297695 * T) + (unsigned long)10905)) - 18
#endif

//Hardware Related macros
#define INIT_PIN PORTCbits.RC3
#define INIT_TRIS TRISCbits.RC3
#define CCP1_INPT TRISCbits.RC2

//Flag for performing an ultrasonic measurment
volatile static char measuringUS = 0;

//Static variable to store the range
static unsigned int lastRange = 0;
static unsigned int lastUSRange = 0;    //These are used by the calibration function
static unsigned int lastIRRange = 0;

//Calibration offsets
static signed int calibration_offset_IR = 0;
static signed int calibration_offset_US = 0;

//Configuration variables
static char numSamples = 3;         //Number of ultrasonic samples
static unsigned char rateUS = 10;   //Ultrasonic sampling rate in Hz
static unsigned int rateIR = 200;   //IR sampling rate in Hz

static TargetState current_target_state;

//Private function prototypes:
static void beginUS(void);
static unsigned int rangeUS(unsigned char temp);
static unsigned int fuseRange(unsigned int us, unsigned int ir);


static volatile unsigned int ccp_value;

void configureRange(void);

unsigned int range(void);

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
    ADCON1 = 0x8E;      // ADFM set
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
    //if (CCPR1 < 0x1770) return 0;
    //if (CCPR1 < 0x5DC) return 0;
    if (ccp_value < 0x100) return 0;

    //Perform calculation (ReadCapture in us, speed of sound in m/s->um)
    // um/1024 = ~mm

    t = DIV_4096((unsigned long int) ccp_value * (unsigned long int) 285) - 18;

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
    //if (CCP1_INT && CCPR1 > 0x300)
    {   //Checks if the CCP2 module fired the interrupt
        measuringUS = 0;
        INIT_PIN = 0;
        PIE1bits.CCP1IE = 0;
        ccp_value = CCPR1;
    }
    if (TMR1_INT)
    {
        measuringUS = 0;
        CCPR1 = 0;
        ccp_value = 0;
        INIT_PIN = 0;
        PIR1bits.TMR1IF = 0;
        PIE1bits.TMR1IE = 0;
    }
    CCP1_CLEAR;
}

/*! **********************************************************************
 * Function: rangeUltrasonic(void)
 *
 * Include:
 *
 * Description: performs an ultrasonic range reading.
 * Pins:
 *
 * Arguments: None
 *
 * Returns: the average of the samples
 *
 * todo remove this function?
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
    range();    //Sample the range

    //Check if valid data was returned by the sensors before they perform a calibration
    if (current_target_state != NO_TARGET && current_target_state != CLOSE_RANGE)
    {
        calibration_offset_US = reference - lastUSRange;
    }
    if (current_target_state == GOOD_TRACK || current_target_state == CLOSE_RANGE)
    {
        calibration_offset_IR = reference - lastIRRange;
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
 * Function: range(void)
 *
 * Include: Range.h
 *
 * @brief Samples the range
 *
 * Description: Takes a number of samples of the ultrasonic sensor at a specified
 *              rate. Continues to sample the IR sensor at a different rate while
 *              sampling the ultrasonic. Then combines the ranges and sets the
 *              target state
 *
 * Arguments: None
 *
 * Returns: the range
 *************************************************************************/
//static unsigned int sampleRange(char numSamples, unsigned char rateUS, unsigned int rateIR)
unsigned int range(void)
{
#define range_IR sumIR      //Come conenient name changes
#define range_US sumUS
    char i;
    unsigned int temp;
    unsigned long int sumUS = 0;
    unsigned long int sumIR = 0;
    int IR_samples = 0;
    unsigned char delayUS = 25;//100 / rateUS;       //100Hz will give 1 delay increment of 10ms
    unsigned char delayIR = 255;//10000 / rateIR;     //10KHz will give 1 delay increment of 0.1ms

    unsigned int j;
    char rng_string[] = "Range: ";
    char ultrasonic[] = "Ultrasonic: ";
    char infra[] = "Infra: ";
    char newLine[] = "\n\r";
    char neg = '-';
    char num[5];

    //Multiplex onto the IR sensor
    SetChanADC(ADC_IR_READ);

    //for (i = 0; i < numSamples; i++)
    {
        configureRange();   //Still have to reconfigure each time???
        beginUS();

        //Continue sampling the IR while waiting for the ultrasonic
        while (measuringUS)
        {
            ADCON0bits.GO = 1;
            while (ADCON0bits.GO_NOT_DONE);
            temp = ADRES >> 6;
            if (temp > 100) sumIR += IR_CONV(temp);
            else IR_samples--;
            //sumIR += IR_CONV(ADRES >> 6);
            IR_samples++;

            Delay1KTCYx(delayIR);  //Delays in inrements of 100Tcy, which is 100 x 1us for 4MHz clock -> 0.1ms or 10KHz
        }

        //get range of ultrasonic reading
        sumUS += rangeUS(25);   ///Standard room temperature for now @todo Read in temperature for US calculation
        Delay10KTCYx(delayUS);  //Delays in increments of 10KTcy, which is 10,000 * 1us for a 4MHz clock
    }

    if (numSamples) sumUS = sumUS / numSamples;     //Calculate the average Ultrasonic range
    else sumUS = 0;

    //Average all IR samples taken, and convert to distance
    if (IR_samples) range_IR = sumIR / IR_samples;
    else sumIR = 0;
    //if (range_IR < 100) range_IR = 0;
    //else range_IR = IR_CONV(range_IR);

    lastIRRange = range_IR;
    lastUSRange = range_US;

    transRange(range_US, range_IR);

    //transChar(sumIR / 100 + '0');



    return lastRange = fuseRange(range_US, range_IR);
#undef range_IR
#undef range_US
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
    range();
    return current_target_state;
}

/*! **********************************************************************
 * Function: fuseRange(unsigned int us, unsigned int ir)
 *
 * Include: Range.h
 *
 * Description: Fuses the IR and Ultrasonic ranges, and sets the target state
 *
 * Arguments: us - the Ultrasonic range (mm)
 *            ir - the IR range (mm)
 *
 * Returns: the fused range
 *
 * Note: Also sets the current target state based on the reading from both
 *      the IR and ultrsonic sensors
 *************************************************************************/
static unsigned int fuseRange(unsigned int us, unsigned int ir)
{
    unsigned int range; //Store the range

    //Check which sensors have observed a target
    if (us && ir)
    {
        //Calibrate the sensors
        us += calibration_offset_US;
        ir += calibration_offset_IR;

        // CASE 1: Range: 150-450mm
        // Ignore US reading as it is inaccurate at these ranges
        if (us >= 150 && us <= 450)
        {
            range = ir;
            current_target_state = CLOSE_RANGE;
        }
        // CASE 2: Range: 1m - 1.5m
        // Don't trust the IR ranges much
        else if (us >= 1000 && ir >=1000)
        {
            /// @TODO Implement IR in here a little?
            range = us;
            current_target_state = OUT_OF_IR;
        }
        else
        {
            // CASE 3: Range: 450mm - 1m
            // Average the ultrasonic and IR ranges
            // TODO: Do we want to average these completely?
            range = DIV_2(us + ir);
            current_target_state = GOOD_TRACK;
        }

    }
    // CASE 4: Range: 1.5m+
    // Rely on Ultrasound
    else if (us)
    {
        //Calibrate the ultrasonic range
        us += calibration_offset_US;

        range = us;

        //Check whether No IR is because out of IR range, or just bad direction
        if (range > 1500) current_target_state = OUT_OF_IR;
        else current_target_state = BAD_DIR;
    }
    else if (ir)
    {
        //Calibrate the IR range
        ir += calibration_offset_IR;

        range = ir;
        current_target_state = CLOSE_RANGE;
    }
    else
    {
        /// @TODO: Report Error?
        range = 0;
        current_target_state = NO_TARGET;
    }
}

static void transRange(unsigned int us, unsigned int ir)
{
    unsigned int j;
    char rng_string[] = "Range: ";
    char ultrasonic[] = "Ultrasonic: ";
    char infra[] = "Infra: ";
    char newLine[] = "\n\r";
    char neg = '-';
    char num[5];

    transmit(ultrasonic);
    sprintf(num, "%u", us);
        transmit(num);
        transmit(newLine);

        transmit(infra);
    sprintf(num, "%u", ir);
        transmit(num);
        transmit(newLine);
}