/* 
 * File:   MenuDefs.h
 * Author: Grant
 *
 * Created on 25 October 2014, 11:49 PM
 */

#ifndef MENUDEFS_H
#define	MENUDEFS_H

// Set up the port tp be used for the Factory key
#define FACTORY_SWITCH PORTBbits.RB2

#define MENU_ISR 0
#define width 80
#define height 24

#define MAX_ANGLE_SUPREMUM 45
#define MAX_ANGLE_INFIMUM 20
#define MIN_ANGLE_SUPREMUM -20
#define MIN_ANGLE_INFIMUM -45

#define MAX_RANGE_SUPREMUM 3000     //3m Max range
#define MAX_RANGE_INFIMUM 1000      //1m max range
#define MIN_RANGE_SUPREMUM 600      //60cm min range
#define MIN_RANGE_INFIMUM 300       //30cm min range

#define SAMPLE_PER_AVG_MIN 1
#define SAMPLE_PER_AVG_MAX 5

/// An enum for the different menu IDs, in the with tabs idicating structure that the menus will be in
typedef enum {TOP_LEVEL,
                    TRACKING,
                    AZ_MENU,
                        AZ_GOTO,
                        AZ_MAX,
                        AZ_MIN,
                        AZ_CALIBRATE,
                    EL_MENU,
                        EL_GOTO,
                        EL_MAX,
                        EL_MIN,
                        EL_CALIBRATE,
                    RANGE_MENU,
                        RANGE_MAX,
                        RANGE_MIN,
                        US_SAMPLE_RATE,
                        US_SAMPLE_AVG,
                        IR_SAMPLE_RATE,
                        IR_SAMPLE_AVG,
                        RANGE_RAW,
                        CALIBRATE_RANGE,
                    SHOW_TEMP,
                    CALIBRATE_TEMP
            } menuState;
typedef enum {LOCAL, REMOTE, FACTORY} userState;

// Special Terminal Commands
#define CLEAR_SCREEN_STRING "\033[2J\033[0;0H"
#define CLEAR_LINE_STRING "\033[2K"
#define SERIAL_CURSOR_OFF "\033[?25l"
#define SERIAL_CURSOR_ON "\033[?25h"

// Other Defines
#define ERR_NUM_OUT_OF_RANGE -1000
#define ERR_NOT_NUMERIC -2000
#define ERR_NO_NUMBER -3000
#define ESC_PRESSED -4000
#define MINUS_CHAR 0x2D

typedef void (*numericInputFunction)(int);
typedef void (*voidFunction) (void);

/*! ****************************************************************************
 * typedef of menuStruct struct
 *
 * @brief Defines a sub menu
 *
 * Description:
 * Stores all data required to define a submenu
 *
 * Elements:
 *      - menuNum:
 *      - SerialMessage: The message to be displayed on entering the state
 *      - LcdTitleMessage: LCD Message to be displayed on entering the state
 *      - MinVal: The minimum value accepted by the state
 *      - MaxVal: The maximum value accepted by the state
 *      - increment: The increment between numbers (eg increment = 10 means 10, 20, 30 can be chosen)
 *      - serialDisplayFunction: Function to display result over serial
 *      - confirmFunction: Function to confirm entry
 *      - lcdDisplayFunction: Function to display result on LCD
 *      - returnToPrevious: Function to return to previous menu state
 ******************************************************************************/
struct menuStruct
{
    menuState menuID;
    rom char* serialMessage;    //Serial Message to be displayed on entering the state
    rom char* lcdTitleMessage;       //LCD Message to be displayed on entering the state

    int minVal;
    int maxVal;
    char increment;
    voidFunction serialDisplayFunction;
    numericInputFunction confirmFunction;
    numericInputFunction lcdDisplayFunction;
    voidFunction returnToPrevious;
 } menuStruct;

//Global Strings
const rom char newLine[] = "\r\n";
const rom char CHOOSE[] = "\tPlease select option (eg. 2)";
const rom char CHOOSE2[] = "\tPress Enter to confirm, or Esc to return";
const rom char menuPrefix3[] = "3:";
const rom char menuPrefix4[] = "4:";
const rom char menuPrefix5[] = "5:";
const rom char menuPrefix8[] = "8:";
const rom char goUp[] = "Return to previous menu";
const rom char goUp2[] = "Press Esc to return to the previous menu.";
const rom char errStr[] = "Error: " ;
const rom char inputNumRangeStr[] = "Please enter a number between ";
const rom char currentValueStr[] = "The current value is: ";
const rom char and[] = " and ";
const rom char AzStr[] = "Azimuth";
const rom char ElStr[] = "Elevation";
const rom char RngStr[] = "Range";
const rom char mmStr[] = "Range (mm)";
const rom char sampleRate[] = "Sampling Frequency (Hz)";
const rom char numPerSample[] = "Number of samples per estimate";
const rom char hz[] = "Hz";
const rom char tab[] = "\t";
const rom char set[] = "Set";
const rom char range_str[] = "Range";
const rom char goto_str[] = "Go to";
const rom char Options[] = "Options";
//

//1: Top Level Menu Strings
const rom char title[] = "Welcome to the Yavin IV Defence System!";
const rom char welcomeLcd[] = "Home Menu";
const rom char topOption1[] = "\t1:\tAutomatic Tracking";
const rom char topOption2[] = "\t2:\tAzimuth Options";
const rom char topOption3[] = "\t3:\tElevation Options";
const rom char topOption4[] = "\t4:\tRange Options";
const rom char topOption5[] = "\t5:\tDisplay Current Temperature";
const rom char topOptionCalTemp[] = "\t6:\tCalibrate the Temperature sensor";
const rom char topOptionLocal[] = "\t6:\tSwitch to Local mode";
const rom char topOptionForFactory[] = "\t7:\tSwitch to Factory mode";
const rom char topOptionRemote[] = "\t6:\tSwitch to Remote Serial mode";
const rom char topOptionRemoteLCD[] = "Switch to Remote";
//

//1.1: Automatic tracking Strings
const rom char autoSerialMessage[] = "Automatic tracking mode initiated.";
const rom char autoLcdTitle[] = "Auto-tracking";
const rom char autoSearching[] = "Searching...";
//

//1.2: Azimuth Menu Strings
const rom char azMenu[] = "\r\nAzimuth Configuration\r\n";
const rom char azMenuLcd[] = "Azimuth Options";
const rom char azOption1[] = "\t1:\tGo to a specified azimuth angle";
const rom char azOption2[] = "\t2:\tSet the min azimuth angle";
const rom char azOption3[] = "\t3:\tSet the max azimuth angle";
const rom char azOption4[] = "\t4:\tCalibrate the azimuth motor";
//

//1.3: Elevation Menu Strings
const rom char elMenu[] = "Elevation Configuration";
const rom char elMenuLcd[] = "Elevation Options";
const rom char elOption1[] = "\t1:\tGo to a specified elevation angle";
const rom char elOption2[] = "\t2:\tSet min elevation angle";
const rom char elOption3[] = "\t3:\tSet max elevation angle";
const rom char elOption4[] = "\t4:\tCalibrate elevation servo";
//

//1.4: Range Menu Strings
const rom char rngMenu[] = "Range Configuration";
const rom char rngMenuLcd[] = "Range Options";
const rom char rngOption1[] = "\t1:\tSet min system range";
const rom char rngOption2[] = "\t2:\tSet max system range";
const rom char rngOption3[] = "\t3:\tView raw ultrasound and IR sensor data";
const rom char rngOption4[] = "\t4:\tSet the ultrasound sample rate";
const rom char rngOption5[] = "\t5:\tSet number of ultrasound samples per estimate";
const rom char rngOption7[] = "\t6:\tSet number of IR samples per estimate";
const rom char rngOption8[] = "\t7:\tCalibrate to a set range";
//

//1.5: Show Temp Strings
const rom char showTempLCDTitle[] = "Display Temp";
const rom char showTempLCD[] = "Temp = ";
const rom char showTemp1[] = "Temp: ";
const rom char showTemp2[] = " deg Celcius. \r\n\n\tPress Esc to return";
//

//1.6: Calibrate Temperature
//

//1.2.1: Go to Azimuth Angle Strings
const rom char gotoAzAngle[] = "Enter azimuth angle in degrees";
const rom char gotoAzAngleLCD[] = "Go to Azimuth";
const rom char gotoElAngle[] = "Enter elevation angle in degrees";
const rom char gotoELAngleLCD[] = "Go to Elevation";
const rom char gotoAngle2[] = " Current min & max angles: ";
const rom char angleStr[] = "Angle";
//

//1.2.2: Set Max Azimuth Angle Strings
const rom char maxAzStr[] = "Max Azimuth";
const rom char maxAzSetStr[] = "Set Max Azimuth";
const rom char maxAz1[] = "Enter a new max azimuth: ";
const rom char maxAz3[] = "Max azimuth set to ";
//

//1.2.2: Set Min Azimuth Angle Strings
const rom char currentMinAngleStr[] = "Current min ";
const rom char minAzStr[] = "Min Azimuth";
const rom char minAzSetStr[] = "Set Min Azimuth";
const rom char minAz1[] = "Enter a new min azimuth: ";
const rom char minAz3[] = "Min azimuth set to ";
//

//1.2.3: Calibrate Azimuth / Elevation Strings
const rom char calibrateAngle1[] = "Enter Calibration angles: ";
//

//1.3.2: Set Max Elevation Angle Strings
const rom char maxElStr[] = "Max Elevation";
const rom char maxElSetStr[] = "Set Max Elevation";
//const rom char maxEl1[] = "\r\n The current maximum elevation angle is ";
const rom char maxEl1[] = "Enter a new max elevation: ";
const rom char maxEl3[] = "Max elevation set to ";
//

//1.3.2: Set Min Elevation Angle Strings
const rom char minElStr[] = "Min Elevation";
const rom char minElSetStr[] = "Set Min Elevation";
//const rom char minEl1[] = "\r\n The current minimum elevation angle is ";
const rom char minEl1[] = "Enter a new min elevation: ";
const rom char minEl3[] = "Min elevation set to ";
//

//1.4.1 Range Min Strings
const rom char minRngStr[] = "Min Range";
const rom char minRngSetStr[] = "Set Min Range";
const rom char minRngSerialStr[] = "Enter a new min range: (mm)";
//

// 1.4.2 Range Max Strings
const rom char maxRngStr[] = "Max Range";
const rom char maxRngSetStr[] = "Set Max Range";
const rom char maxRngSerialStr[] = "Enter a new max range (mm):";
//

// RAW RANGE Strings
const rom char rawRangeStr[] = "Displaying raw range in mm:";
const rom char rawRangeTitle[] = "Raw Range";
//

// CALIBRATE RANGE Strings
const rom char calRangeStr[] = "Place an object 500mm away from the sensor and press enter.";
const rom char calRangeTitle[] = "Calibrate Range";
const rom char calRangeConfirm[] = "Range calibrated";
//

// US SAMPLE RATE Strings
const rom char usSampleRateStr[] = "Please enter a sample";
const rom char usSampleRateTitle[] = "Ultrasound Sample Rate";
//

// US NUMBER OF SAMPLE Strings
const rom char numSamplesStr[] = "Enter a number of samples to take.";
const rom char numSampleTitle[] = "Num. of Samples";
//

#endif	/* MENUDEFS_H */

