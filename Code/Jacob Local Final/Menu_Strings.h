/* 
 * File:   Strings.h
 * Author: buyt1635
 *
 * Created on 26 October 2014, 2:21 PM
 */

//Ensure there is only 1 inclusion of this file in the preprocessor execution
#ifndef STRINGS_H

//Global
const static rom char newLine[] = "\r\n";
const static rom char CHOOSE[] = "\n\n\tPlease select your option (eg. 2): \r\n";
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
const static rom char welcomeLcd[] = " Welcome!";
const static far rom char topOption1[] = "\t1:\tAutomatic Tracking\r\n";
const static far rom char topOption2[] = "\t2:\tAzimuth Options\r\n";
const static far rom char topOption3[] = "\t3:\tElevation Options\r\n";
const static far rom char topOption4[] = "\t4:\tRange Options\r\n";
const static far rom char topOption5[] = "\t5:\tDisplay Current Temperature\r\n";
const static far rom char topOptionCalTemp[] = "\t6:\tCalibrate the Temperature sensor\r\n";
const static far rom char topOptionLocal[] = "\t6:\tSwitch to Local mode\r\n";
const static far rom char topOptionFactory[] = "\t7:\tSwitch to Factory mode\r\n";
const static far rom char topOptionRemote[] = "\t6:\tSwitch to Remote Serial mode\r\n";
const static far rom char topOptionRemoteLCD[] = "Switch to Remote";
//

//1.1: Automatic tracking
//const static far rom char automessage[] = "Automatic Tracking Mode";
//const static far rom char autoinit[] = "\tInitialising Automatic Tracking...";
//const static far rom char autohelp1[] = "\tEnter any key to end session";
////const static far rom char autohelp2[] = "\tRange, Elevation, Azimuth and Tracking";
////const static far rom char autohelp3[] = " Status will be displayed every X seconds:";
//const static far rom char autogo[] = "\t3...\n\t2...\n\t1...\n";
//const static far rom char autorange[] = "\tRange:\t";
//const static far rom char autoeleva[] = "\tElevation:\t";
//const static far rom char autoazimu[] = "\tAzimuth:\t";
//const static far rom char autostatu[] = "\tTarget Status:\t";
//const static far rom char autoend[] = "Tracking Session Terminated";
//

//1.2: Azimuth Menu
const static rom char azMenu[] = "\r\nAzimuth Configuration\r\n";
const static rom char azMenuLcd[] = "Azimuth Options";
const static far rom char azOption1[] = "\t1:\tGo to a specified azimuth angle\r\n";
const static far rom char azOption2[] = "\t2:\tSet the minimum azimuth angle\r\n";
const static far rom char azOption3[] = "\t3:\tSet the maximum azimuth angle\r\n";
const static far rom char azOption4[] = "\t4:\tCalibrate the azimuth motor\r\n";
//

//1.3: Elevation Menu
const static rom char elMenu[] = "\r\nElevation Configuration\r\n";
const static rom char elMenuLcd[] = "Elevation Options";
const static far rom char elOption1[] = "\t1:\tGo to a specified elevation angle\r\n";
const static far rom char elOption2[] = "\t2:\tSet the minimum elevation angle\r\n";
const static far rom char elOption3[] = "\t3:\tSet the maximum elevation angle\r\n";
const static far rom char elOption4[] = "\t4:\tCalibrate the elevation motor\r\n";
//

//1.4: Range Menu
const static rom char rngMenu[] = "\r\nRange Configuration\r\n";
const static rom char rngMenuLcd[] = "  Range Options ";
const static far rom char rngOption1[] = "\t1:\tSet the minimum system range\r\n";
const static far rom char rngOption2[] = "\t2:\tSet the maximum system range\r\n";
const static far rom char rngOption3[] = "\t3:\tView the raw ultrasound and infrared sensor readings\r\n";
const static far rom char rngOption4[] = "\t4:\tSet the ultrasound sample rate\r\n";
const static far rom char rngOption5[] = "\t5:\tSet the number of ultrasound samples used per estimate\r\n";
const static far rom char rngOption6[] = "\t6:\tSet the infrared sample rate\r\n";
const static far rom char rngOption7[] = "\t7:\tSet the number of infrared samples used per estimate\r\n";
//

//1.5: Show Temp
const static far rom char showTempLCDTitle[]    = "  Display Temp  ";
const static far rom char showTempLCD[]         = "  Temp = xx*C   ";
const static far rom char showTemp1[] = "\r\n The current temperature is ";
const static far rom char showTemp2[] = " degrees Celcius. \r\n\n Press Esc to return.\r\n";
//

//1.6: Calibrate Temperature
//

//1.7: Remote Mode
//

//1.2.1: Go to Azimuth Angle
const static far rom char gotoAzAngle[] = "\r\n Enter the azimuth angle in degrees. \r\n";
const static far rom char gotoAzAngleLCD[] = "Go to Azimuth";
const static far rom char gotoElAngle[] = "\r\n Enter the elevation angle in degrees. \r\n";
const static far rom char gotoELAngleLCD[] = "Go to Elevation";
const static far rom char gotoAngle2[] = " The current minimum and maximum angles are ";
const static far rom char angleStr[] = "Angle";
//

//1.2.2: Set Max Azimuth Angle
const static far rom char maxAzStr[] = "Max Azimuth";
const static far rom char maxAzSetStr[] = "Set Max Azimuth";
const static far rom char maxAz1[] = " Enter a new maximum azimuth angle: \r\n";
const static far rom char maxAz3[] = "\r\n Maximum azimuth angle set to ";
//

//1.2.2: Set Min Azimuth Angle
const static far rom char currentMinAngleStr[] = "\r\n The current minimum angle is ";
const static far rom char minAzStr[] = "Min Azimuth";
const static far rom char minAzSetStr[] = "Set Min Azimuth";
const static far rom char minAz1[] = " Enter a new minimum azimuth angle: \r\n";
const static far rom char minAz3[] = "\r\n Minimum azimuth angle set to ";
//

//1.2.3: Calibrate Azimuth / Elevation
const static far rom char calibrateAngle1[] = "\r\n Enter the true angle of the current position \r\n";
//

//1.3.2: Set Max Elevation Angle
const static far rom char maxElStr[] = "Max Elevation";
const static far rom char maxElSetStr[] = "Set Max Elevation";
//const static far rom char maxEl1[] = "\r\n The current maximum elevation angle is ";
const static far rom char maxEl1[] = " Enter a new maximum elevation angle: \r\n";
const static far rom char maxEl3[] = "\r\n Maximum elevation angle set to ";
//

//1.3.2: Set Min Elevation Angle
const static far rom char minElStr[] = "Min Elevation";
const static far rom char minElSetStr[] = "Set Min Elevation";
//const static far rom char minEl1[] = "\r\n The current minimum elevation angle is ";
const static far rom char minEl1[] = " Enter a new minimum elevation angle: \r\n";
const static far rom char minEl3[] = "\r\n Minimum elevation angle set to ";
//

//1.4.1 Range Min
const static far rom char minRngStr[] = "Min Range";
const static far rom char minRngSetStr[] = " Set Min Range  ";
const static far rom char minRngSerialStr[] = "Enter a new minimum range: \r\n";
//

// 1.4.2 Range Max
const static far rom char maxRngStr[] = "Max Range";
const static far rom char maxRngSetStr[] = " Set Max Range  ";
const static far rom char maxRngSerialStr[] = "Enter a new minimum range: \r\n";
//

#define STRINGS_H 0
#endif