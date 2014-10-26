/* 
 * File:   MenuDefs.h
 * Author: Grant
 *
 * Created on 25 October 2014, 11:49 PM
 */

#ifndef MENUDEFS_H
#define	MENUDEFS_H


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
    menuState menuNum;
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
const rom char menuPrefix3[] = "\t3:";
const rom char menuPrefix4[] = "\t4:";
const rom char menuPrefix5[] = "\t5:";
const rom char menuPrefix8[] = "\t8:";
const rom char goUp[] = "\tReturn to previous menu\r\n";
const rom char goUp2[] = "Press Esc to return to the previous menu.\r\n";
const rom char errNumOutOfRange[] = " Error: Please enter a number between ";
const rom char and[] = " and ";
//

//1: Top
const rom char welcome[] = " Welcome to Yavin IV Defence System ";
const rom char welcomeLcd[] = " Welcome!";
const far rom char topOption1[] = "\t1:\tAutomatic Tracking\r\n";
const far rom char topOption2[] = "\t2:\tAzimuth Options\r\n";
const far rom char topOption3[] = "\t3:\tElevation Options\r\n";
const far rom char topOption4[] = "\t4:\tRange Options\r\n";
const far rom char topOption5[] = "\t5:\tDisplay Current Temperature\r\n";
const far rom char topOptionCalTemp[] = "\t6:\tCalibrate the Temperature sensor\r\n";
const far rom char topOptionLocal[] = "\t6:\tSwitch to Local mode\r\n";
const far rom char topOptionFactory[] = "\t7:\tSwitch to Factory mode\r\n";
const far rom char topOptionRemote[] = "\t6:\tSwitch to Remote Serial mode\r\n";
const far rom char topOptionRemoteLCD[] = "Switch to Remote";
//

//1.1: Automatic tracking
//const far rom char automessage[] = "Automatic Tracking Mode";
//const far rom char autoinit[] = "\tInitialising Automatic Tracking...";
//const far rom char autohelp1[] = "\tEnter any key to end session";
////const far rom char autohelp2[] = "\tRange, Elevation, Azimuth and Tracking";
////const far rom char autohelp3[] = " Status will be displayed every X seconds:";
//const far rom char autogo[] = "\t3...\n\t2...\n\t1...\n";
//const far rom char autorange[] = "\tRange:\t";
//const far rom char autoeleva[] = "\tElevation:\t";
//const far rom char autoazimu[] = "\tAzimuth:\t";
//const far rom char autostatu[] = "\tTarget Status:\t";
//const far rom char autoend[] = "Tracking Session Terminated";
//

//1.2: Azimuth Menu
const rom char azMenu[] = "\r\nAzimuth Configuration\r\n";
const rom char azMenuLcd[] = "Azimuth Options";
const far rom char azOption1[] = "\t1:\tGo to a specified azimuth angle\r\n";
const far rom char azOption2[] = "\t2:\tSet the minimum azimuth angle\r\n";
const far rom char azOption3[] = "\t3:\tSet the maximum azimuth angle\r\n";
const far rom char azOption4[] = "\t4:\tCalibrate the azimuth motor\r\n";
//

//1.3: Elevation Menu
const rom char elMenu[] = "\r\nElevation Configuration\r\n";
const rom char elMenuLcd[] = "Elevation Options";
const far rom char elOption1[] = "\t1:\tGo to a specified elevation angle\r\n";
const far rom char elOption2[] = "\t2:\tSet the minimum elevation angle\r\n";
const far rom char elOption3[] = "\t3:\tSet the maximum elevation angle\r\n";
const far rom char elOption4[] = "\t4:\tCalibrate the elevation motor\r\n";
//

//1.4: Range Menu
const rom char rngMenu[] = "\r\nRange Configuration\r\n";
const rom char rngMenuLcd[] = "Range Options";
const far rom char rngOption1[] = "\t1:\tSet the minimum system range\r\n";
const far rom char rngOption2[] = "\t2:\tSet the maximum system range\r\n";
const far rom char rngOption3[] = "\t3:\tView the raw ultrasound and infrared sensor readings\r\n";
const far rom char rngOption4[] = "\t4:\tSet the ultrasound sample rate\r\n";
const far rom char rngOption5[] = "\t5:\tSet the number of ultrasound samples used per estimate\r\n";
const far rom char rngOption6[] = "\t6:\tSet the infrared sample rate\r\n";
const far rom char rngOption7[] = "\t7:\tSet the number of infrared samples used per estimate\r\n";
//

//1.5: Show Temp
const far rom char showTempLCDTitle[] = "Display Temp";
const far rom char showTempLCD[] = "Temp = ";
const far rom char showTemp1[] = "\r\n The current temperature is ";
const far rom char showTemp2[] = " degrees Celcius. \r\n\n Press Esc to return.\r\n";
//

//1.6: Calibrate Temperature
//

//1.2.1: Go to Azimuth Angle
const far rom char gotoAzAngle[] = "\r\n Enter the azimuth angle in degrees. \r\n";
const far rom char gotoAzAngleLCD[] = "Go to Azimuth";
const far rom char gotoElAngle[] = "\r\n Enter the elevation angle in degrees. \r\n";
const far rom char gotoELAngleLCD[] = "Go to Elevation";
const far rom char gotoAngle2[] = " The current minimum and maximum angles are ";
const far rom char angleStr[] = "Angle";
//

//1.2.2: Set Max Azimuth Angle
const far rom char maxAzStr[] = "Max Azimuth";
const far rom char maxAzSetStr[] = "Set Max Azimuth";
const far rom char maxAz1[] = " Enter a new maximum azimuth angle: \r\n";
const far rom char maxAz3[] = "\r\n Maximum azimuth angle set to ";
//

//1.2.2: Set Min Azimuth Angle
const far rom char currentMinAngleStr[] = "\r\n The current minimum angle is ";
const far rom char minAzStr[] = "Min Azimuth";
const far rom char minAzSetStr[] = "Set Min Azimuth";
const far rom char minAz1[] = " Enter a new minimum azimuth angle: \r\n";
const far rom char minAz3[] = "\r\n Minimum azimuth angle set to ";
//

//1.2.3: Calibrate Azimuth / Elevation
const far rom char calibrateAngle1[] = "\r\n Enter the true angle of the current position \r\n";
//

//1.3.2: Set Max Elevation Angle
const far rom char maxElStr[] = "Max Elevation";
const far rom char maxElSetStr[] = "Set Max Elevation";
//const far rom char maxEl1[] = "\r\n The current maximum elevation angle is ";
const far rom char maxEl1[] = " Enter a new maximum elevation angle: \r\n";
const far rom char maxEl3[] = "\r\n Maximum elevation angle set to ";
//

//1.3.2: Set Min Elevation Angle
const far rom char minElStr[] = "Min Elevation";
const far rom char minElSetStr[] = "Set Min Elevation";
//const far rom char minEl1[] = "\r\n The current minimum elevation angle is ";
const far rom char minEl1[] = " Enter a new minimum elevation angle: \r\n";
const far rom char minEl3[] = "\r\n Minimum elevation angle set to ";
//

//1.4.1 Range Min
const far rom char minRngStr[] = "Min Range";
const far rom char minRngSetStr[] = "Set Min Range";
const far rom char minRngSerialStr[] = "Enter a new minimum range: \r\n";
//

// 1.4.2 Range Max
const far rom char maxRngStr[] = "Max Range";
const far rom char maxRngSetStr[] = "Set Max Range";
const far rom char maxRngSerialStr[] = "Enter a new minimum range: \r\n";
//

#endif	/* MENUDEFS_H */

