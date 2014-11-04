/* 
 * File:   MenuDefs.h
 * Author: Grant
 *
 * Created on 25 October 2014, 11:49 PM
 */

#ifndef MENUDEFS_H
#define	MENUDEFS_H

#define FACTORY_SWITCH PORTBbits.RB2

#define MENU_ISR 0
#define width 80
#define height 24

#define MAX_ANGLE_SUPREMUM 45
#define MAX_ANGLE_INFIMUM 20
#define MIN_ANGLE_SUPREMUM -20
#define MIN_ANGLE_INFIMUM -45

#define MAX_RANGE_SUPREMUM 3000     //3m Max range
#define MAX_RANGE_INFIMUM 2000      //2m max range
#define MIN_RANGE_SUPREMUM 600      //60cm min range
#define MIN_RANGE_INFIMUM 250       //25cm min range

#define SAMPLE_PER_AVG_MIN 1
#define SAMPLE_PER_AVG_MAX 5

typedef enum {TOP_LEVEL,
                    TRACKING,
                    AZ_MENU,
                        AZ_GOTO,    //
                        AZ_MAX,     //
                        AZ_MIN,     //
                        AZ_CALIBRATE,//
                    EL_MENU,
                        EL_GOTO,    //
                        EL_MAX,     //
                        EL_MIN,     //
                        EL_CALIBRATE,//
                    RANGE_MENU,
                        RANGE_MAX,  //
                        RANGE_MIN,  //
                        US_SAMPLE_RATE,//
                        US_SAMPLE_AVG,
                        IR_SAMPLE_RATE,//
                        IR_SAMPLE_AVG,
                        RANGE_RAW,
                    SHOW_TEMP,
                    CALIBRATE_TEMP
            } menuState;
typedef enum {LOCAL, REMOTE, FACTORY} userState;

#define MAX_SER_MSG_LEN 30
#define MAX_LCD_MSG_LEN 16

#define ERR_NUM_OUT_OF_RANGE -1000
#define ERR_NOT_NUMERIC -2000
#define ERR_NO_NUMBER -3000
#define ESC_PRESSED -4000
#define MINUS_CHAR 0x2D
#define CLEAR_SCREEN_STRING "\033[2J\033[0;0H"

//typedef enum setMenu {AZ_GOTO, AZ_MAX, AZ_MIN, EL_GOTO, EL_MIN, EL_MAX, RNG_MAX, RNG_MIN, IR_SAMPLE, IR_PER_AVG, US_SAMPLE, US_PER_AVG};
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
 *      - increment:
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

//Global
const rom char newLine[] = "\r\n";
const rom char CHOOSE[] = "\n\n\tPlease select your option (eg. 2): \r\n";
const rom char menuPrefix3[] = "3:";
const rom char menuPrefix4[] = "4:";
const rom char menuPrefix5[] = "5:";
const rom char menuPrefix8[] = "8:";
const rom char goUp[] = "\tReturn to previous menu\r\n";
const rom char goUp2[] = "Press Esc to return to the previous menu.\r\n";
const rom char errNumOutOfRange[] = " Error: Please enter a number between ";
const rom char and[] = " and ";
const far rom char AzStr[] = "Azimuth";
const far rom char ElStr[] = "Elevation";
const far rom char RngStr[] = "Range";
const far rom char tab[] = "\t";
//


//1: Top
const rom char welcome[] = " Welcome to Yavin IV Defence System ";
//const far rom char topOption1[] = "\t1:\tAutomatic Tracking\r\n";
const far rom char topOption1[] = "\t1:\tAutomatic Tracking";
//const far rom char topOption2[] = "\t2:\tAzimuth Options\r\n";
const far rom char topOption2[] = "\t2:\tAzimuth Options";
const far rom char topOption3[] = "\t3:\tElevation Options";
const far rom char topOption4[] = "\t4:\tRange Options";
const far rom char topOption5[] = "\t5:\tDisplay Current Temperature";
const far rom char topOptionCalTemp[] = "\t6:\tCalibrate the Temperature sensor";
const far rom char topOptionLocal[] = "\t6:\tSwitch to Local mode";
const far rom char topOptionFactory[] = "\t7:\tSwitch to Factory mode";
const far rom char topOptionRemote[] = "\t6:\tSwitch to Remote Serial mode";
const rom char welcomeLcd[] =  "    Top Menu    ";
const rom char welcomeLcd1[] = "Welcome To Yavin";
const rom char welcomeLcd2[] = "Orbital Defence!";
const far rom char topOptionRemoteLCD[] = "Switch to Remote";
//

//1.1: Automatic tracking
const far rom char autoSerialMessage[] = "Automatic tracking mode initiated.";
const far rom char autoLcdTitle[] = "Auto-tracking";
const far rom char autoSearching[] = "Searching...";
//

const rom char set[] = "Set";
const rom char range_str[] = "Range";
const rom char goto_str[] = "Go to";
const rom char Options[] = "Options";

//1.2: Azimuth Menu
const rom char azMenu[] = "\r\nAzimuth Configuration\r\n";
const rom char azMenuLcd[] = "Azimuth Options";
const far rom char azOption1[] = "\t1:\tGo to a specified azimuth angle";
const far rom char azOption2[] = "\t2:\tSet min azimuth";
const far rom char azOption3[] = "\t3:\tSet max azimuth";
const far rom char azOption4[] = "\t4:\tCalibrate the azimuth motor";
//

//1.3: Elevation Menu
const rom char elMenu[] = "Elevation Configuration";
const rom char elMenuLcd[] = "Elevation Options";
const far rom char elOption1[] = "\t1:\tGo to a specified elevation angle";
const far rom char elOption2[] = "\t2:\tSet min elev";
const far rom char elOption3[] = "\t3:\tSet max elev";
const far rom char elOption4[] = "\t4:\tCalibrate elevation servo";
//

//1.4: Range Menu
const rom char rngMenu[] = "Range Configuration";
const rom char rngMenuLcd[] = " Range Options  ";
const far rom char rngOption1[] = "\t1:\tSet min system range";
const far rom char rngOption2[] = "\t2:\tSet max system range";
const far rom char rngOption3[] = "\t3:\tView raw ultrasound and IR sensor data";
const far rom char rngOption4[] = "\t4:\tSet the ultrasound sample rate\r\n";
const far rom char rngOption5[] = "\t5:\tSet number of ultrasound samples per estimate";
const far rom char rngOption6[] = "\t6:\tSet IR sample rate\r\n";
const far rom char rngOption7[] = "\t7:\tSet number of IR samples per estimate";
//

//1.5: Show Temp
const far rom char showTempLCDTitle[]    = "  Display Temp  ";
const far rom char showTempLCD[]         = "  Temp = xx*C   ";
const far rom char showTemp1[] = "Temp: ";
const far rom char showTemp2[] = " deg Celcius. \r\n\n Press Esc to return";
//

//1.6: Calibrate Temperature
//

//1.7: Remote Mode
const static far rom char remoteLcd1[] = "     Remote     ";
const static far rom char remoteLcd2[] = "      Mode      ";
//

//1.2.1: Go to Azimuth Angle
const far rom char gotoAzAngle[] = "Enter azimuth angle in degrees";
const far rom char gotoAzAngleLCD[] = "Go to Azimuth";
const far rom char gotoElAngle[] = "Enter elevation angle in degrees";
const far rom char gotoELAngleLCD[] = "Go to Elevation";
const far rom char gotoAngle2[] = " Current min & max angles: ";
const far rom char angleStr[] = "Angle";
//

//1.2.2: Set Max Azimuth Angle
const far rom char maxAzStr[] = "Max Azimuth";
const far rom char maxAzSetStr[] = "Set Max Azimuth";
const far rom char maxAz1[] = " Enter a new max azimuth: ";
const far rom char maxAz3[] = "Max azimuth set to ";
//

//1.2.2: Set Min Azimuth Angle
const far rom char currentMinAngleStr[] = "Current min ";
const far rom char minAzStr[] = "Min Azimuth";
const far rom char minAzSetStr[] = "Set Min Azimuth";
const far rom char minAz1[] = " Enter a new min azimuth: ";
const far rom char minAz3[] = " Min azimuth set to ";
//

//1.2.3: Calibrate Azimuth / Elevation
const far rom char calibrateAngle1[] = "Enter Calibration angles: ";
//

//1.3.2: Set Max Elevation Angle
const far rom char maxElStr[] = "Max Elevation";
const far rom char maxElSetStr[] = "Set Max Elevation";
//const far rom char maxEl1[] = "\r\n The current maximum elevation angle is ";
const far rom char maxEl1[] = " Enter a new max elevation: ";
const far rom char maxEl3[] = " Maximum elevation set to ";
//

//1.3.2: Set Min Elevation Angle
const far rom char minElStr[] = "Min Elevation";
const far rom char minElSetStr[] = "Set Min Elevation";
//const far rom char minEl1[] = "\r\n The current minimum elevation angle is ";
const far rom char minEl1[] = " Enter a new min elevation: ";
const far rom char minEl3[] = " Min elevation set to ";
//

//1.4.1 Range Min
const far rom char minRngStr[] = "Min Range";
const far rom char minRngSetStr[] = " Set Min Range  ";
const far rom char minRngSerialStr[] = "Enter a new min range: \r\n";
//

// 1.4.2 Range Max
const far rom char maxRngStr[] = "Max Range";
const far rom char maxRngSetStr[] = " Set Max Range  ";
const far rom char maxRngSerialStr[] = "Enter a new minimum range: \r\n";
//

#endif	/* MENUDEFS_H */

