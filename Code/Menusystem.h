/* 
 * File:   Menusystem.h
 * Author: Jacob
 *
 * Created on 7 October 2014, 9:56 PM
 */

#define MENU_ISR 0
#define width 80
#define height 24

#define MAX_ANGLE_SUPREMUM 45
#define MAX_ANGLE_INFIMUM 20
#define MIN_ANGLE_SUPREMUM -20
#define MIN_ANGLE_INFIMUM -45

#define MAX_RANGE_SUPREMUM 3000     //3m Max range
#define MAX_RANGE_INFIMUM 2000      //2m max range
#define MIN_RANGE_SUPREMUM 600     //25cm min range
#define MIN_RANGE_INFIMUM 250      //60cm min range

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

//Global
const static rom char tMESSAGE[] = "Hello 123\n";
const static rom char fillerChar[] = "+";
const static rom char newLine[] = "\r\n";
const static rom char CHOOSE[] = "\tPlease select your option (eg. 2): \r\n";
const static rom char menuPrefix3[] = "\t3:";
const static rom char menuPrefix4[] = "\t4:";
const static rom char menuPrefix5[] = "\t5:";
const static rom char menuPrefix8[] = "\t8:";
const static rom char goUp[] = "\tReturn to previous menu\r\n";
const static rom char goUp2[] = "Press Esc to return to the previous menu.\r\n";
const static rom char errNumOutOfRange[] = " Error: Please enter a number between ";
const static rom char and[] = " and ";
//

//1: Top
const static rom char welcome[] = " Welcome to Yavin IV Defence System ";
const static rom char topOption1[] = "\t1:\tAutomatic Tracking\r\n";
const static rom char topOption2[] = "\t2:\tAzimuth Menu\r\n";
const static rom char topOption3[] = "\t3:\tElevation Menu\r\n";
const static rom char topOption4[] = "\t4:\tRange Menu\r\n";
const static rom char topOption5[] = "\t5:\tShow Current Temperature\r\n";
const static rom char topOptionCalTemp[] = "\t6:\tCalibrate the Temperature sensor\r\n";
const static rom char topOptionLocal[] = "\t6:\tSwitch to Local mode\r\n";
const static rom char topOptionFactory[] = "\t7:\tSwitch to Factory mode\r\n";
const static rom char topOptionRemote[] = "\t6:\tSwitch to Remote Serial mode\r\n";
//

//1.1: Automatic tracking
const static rom char automessage[] = "Automatic Tracking Mode";
const static rom char autoinit[] = "\tInitialising Automatic Tracking...";
const static rom char autohelp1[] = "\tEnter any key to end session";
//const static rom char autohelp2[] = "\tRange, Elevation, Azimuth and Tracking";
//const static rom char autohelp3[] = " Status will be displayed every X seconds:";
const static rom char autogo[] = "\t3...\n\t2...\n\t1...\n";
const static rom char autorange[] = "\tRange:\t";
const static rom char autoeleva[] = "\tElevation:\t";
const static rom char autoazimu[] = "\tAzimuth:\t";
const static rom char autostatu[] = "\tTarget Status:\t";
const static rom char autoend[] = "Tracking Session Terminated";
//

//1.2: Azimuth Menu
const static rom char azMenu[] = "\r\nAzimuth Configuration\r\n";
const static rom char azOption1[] = "\t1:\tGo to a specified azimuth angle\r\n";
const static rom char azOption2[] = "\t2:\tSet the minimum azimuth angle\r\n";
const static rom char azOption3[] = "\t3:\tSet the maximum azimuth angle\r\n";
const static rom char azOption4[] = "\t4:\tCalibrate the azimuth motor\r\n";
//

//1.3: Elevation Menu
const static rom char elMenu[] = "\r\nElevation Configuration\r\n";
const static rom char elOption1[] = "\t1:\tGo to a specified elevation angle\r\n";
const static rom char elOption2[] = "\t2:\tSet the minimum elevation angle\r\n";
const static rom char elOption3[] = "\t3:\tSet the maximum elevation angle\r\n";
const static rom char elOption4[] = "\t4:\tCalibrate the elevation motor\r\n";
//

//1.4: Range Menu
const static rom char rngMenu[] = "\r\nRange Configuration\r\n";
const static rom char rngOption1[] = "\t1:\tSet the minimum system range\r\n";
const static rom char rngOption2[] = "\t2:\tSet the maximum system range\r\n";
const static rom char rngOption3[] = "\t3:\tView the raw ultrasound and infrared sensor readings\r\n";
const static rom char rngOption4[] = "\t4:\tSet the ultrasound sample rate\r\n";
const static rom char rngOption5[] = "\t5:\tSet the number of ultrasound samples used per estimate\r\n";
const static rom char rngOption6[] = "\t6:\tSet the infrared sample rate\r\n";
const static rom char rngOption7[] = "\t7:\tSet the number of infrared samples used per estimate\r\n";
//

//1.5: Show Temp
const static rom char showTemp1[] = "\r\n The current temperature is ";
const static rom char showTemp2[] = " degrees Celcius. \r\n\n Press Esc to return.\r\n";
//

//1.6: Calibrate Temperature
//

//1.2.1: Go to Azimuth Angle
const static rom char gotoAzAngle[] = "\r\n Enter the azimuth angle in degrees. \r\n";
const static rom char gotoAngle2[] = " The current minimum and maximum angles are ";
const static rom char gotoAngle3[] = "\r\n Going to angle: ";
//

//1.2.2: Set Max Azimuth Angle
const static rom char maxAz1[] = "\r\n The current maximum azimuth angle is ";
const static rom char maxAz2[] = " Enter a new maximum azimuth angle: \r\n";
const static rom char maxAz3[] = "\r\n Maximum azimuth angle set to ";
//

//1.2.2: Set Min Azimuth Angle
const static rom char minAz1[] = "\r\n The current minimum azimuth angle is ";
const static rom char minAz2[] = " Enter a new minimum azimuth angle: \r\n";
const static rom char minAz3[] = "\r\n Minimum azimuth angle set to ";
//

//1.2.3: Calibrate Azimuth / Elevation
const static rom char calibrateAngle1[] = "\r\n Enter the true angle of the current position \r\n";
//

//1.3.1: Go to Elevation Angle
const static rom char gotoElAngle[] = "\r\n Enter the elevation angle in degrees. \r\n";
//

//1.3.2: Set Max Elevation Angle
const static rom char maxEl1[] = "\r\n The current maximum elevation angle is ";
const static rom char maxEl2[] = " Enter a new maximum elevation angle: \r\n";
const static rom char maxEl3[] = "\r\n Maximum elevation angle set to ";
//

//1.3.2: Set Min Elevation Angle
const static rom char minEl1[] = "\r\n The current minimum elevation angle is ";
const static rom char minEl2[] = " Enter a new minimum elevation angle: \r\n";
const static rom char minEl3[] = "\r\n Minimum elevation angle set to ";
//

extern void initialiseMenu(void);
extern void waitForSerialInput(void);
extern void menuISR(void);

extern void menu(void);


