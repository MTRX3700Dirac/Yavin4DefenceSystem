/*
 * File:   Menusystem.h
 * Author: Jacob
 *
 * Created on 7 October 2014, 9:56 PM
 */


//Global
extern const rom char newLine[] = "\r\n";
extern const rom char CHOOSE[] = "\n\n\tPlease select your option (eg. 2): \r\n";
extern const rom char menuPrefix3[] = "\t3:";
extern const rom char menuPrefix4[] = "\t4:";
extern const rom char menuPrefix5[] = "\t5:";
extern const rom char menuPrefix8[] = "\t8:";
extern const rom char goUp[] = "\tReturn to previous menu\r\n";
extern const rom char goUp2[] = "Press Esc to return to the previous menu.\r\n";
extern const rom char errNumOutOfRange[] = " Error: Please enter a number between ";
extern const rom char and[] = " and ";
//

//1: Top
extern const rom char welcome[] = " Welcome to Yavin IV Defence System ";
extern const rom char welcomeLcd[] = " Welcome!";
extern const far rom char topOption1[] = "\t1:\tAutomatic Tracking\r\n";
extern const far rom char topOption2[] = "\t2:\tAzimuth Options\r\n";
extern const far rom char topOption3[] = "\t3:\tElevation Options\r\n";
extern const far rom char topOption4[] = "\t4:\tRange Options\r\n";
extern const far rom char topOption5[] = "\t5:\tDisplay Current Temperature\r\n";
extern const far rom char topOptionCalTemp[] = "\t6:\tCalibrate the Temperature sensor\r\n";
extern const far rom char topOptionLocal[] = "\t6:\tSwitch to Local mode\r\n";
extern const far rom char topOptionFactory[] = "\t7:\tSwitch to Factory mode\r\n";
extern const far rom char topOptionRemote[] = "\t6:\tSwitch to Remote Serial mode\r\n";
extern const far rom char topOptionRemoteLCD[] = "Switch to Remote";
//

//1.1: Automatic tracking
//extern const far rom char automessage[] = "Automatic Tracking Mode";
//extern const far rom char autoinit[] = "\tInitialising Automatic Tracking...";
//extern const far rom char autohelp1[] = "\tEnter any key to end session";
////extern const far rom char autohelp2[] = "\tRange, Elevation, Azimuth and Tracking";
////extern const far rom char autohelp3[] = " Status will be displayed every X seconds:";
//extern const far rom char autogo[] = "\t3...\n\t2...\n\t1...\n";
//extern const far rom char autorange[] = "\tRange:\t";
//extern const far rom char autoeleva[] = "\tElevation:\t";
//extern const far rom char autoazimu[] = "\tAzimuth:\t";
//extern const far rom char autostatu[] = "\tTarget Status:\t";
//extern const far rom char autoend[] = "Tracking Session Terminated";
//

//1.2: Azimuth Menu
extern const rom char azMenu[] = "\r\nAzimuth Configuration\r\n";
extern const rom char azMenuLcd[] = "Azimuth Options";
extern const far rom char azOption1[] = "\t1:\tGo to a specified azimuth angle\r\n";
extern const far rom char azOption2[] = "\t2:\tSet the minimum azimuth angle\r\n";
extern const far rom char azOption3[] = "\t3:\tSet the maximum azimuth angle\r\n";
extern const far rom char azOption4[] = "\t4:\tCalibrate the azimuth motor\r\n";
//

//1.3: Elevation Menu
extern const rom char elMenu[] = "\r\nElevation Configuration\r\n";
extern const rom char elMenuLcd[] = "Elevation Options";
extern const far rom char elOption1[] = "\t1:\tGo to a specified elevation angle\r\n";
extern const far rom char elOption2[] = "\t2:\tSet the minimum elevation angle\r\n";
extern const far rom char elOption3[] = "\t3:\tSet the maximum elevation angle\r\n";
extern const far rom char elOption4[] = "\t4:\tCalibrate the elevation motor\r\n";
//

//1.4: Range Menu
extern const rom char rngMenu[] = "\r\nRange Configuration\r\n";
extern const rom char rngMenuLcd[] = "Range Options";
extern const far rom char rngOption1[] = "\t1:\tSet the minimum system range\r\n";
extern const far rom char rngOption2[] = "\t2:\tSet the maximum system range\r\n";
extern const far rom char rngOption3[] = "\t3:\tView the raw ultrasound and infrared sensor readings\r\n";
extern const far rom char rngOption4[] = "\t4:\tSet the ultrasound sample rate\r\n";
extern const far rom char rngOption5[] = "\t5:\tSet the number of ultrasound samples used per estimate\r\n";
extern const far rom char rngOption6[] = "\t6:\tSet the infrared sample rate\r\n";
extern const far rom char rngOption7[] = "\t7:\tSet the number of infrared samples used per estimate\r\n";
//

//1.5: Show Temp
extern const far rom char showTempLCDTitle[] = "Display Temp";
extern const far rom char showTempLCD[] = "Temp = ";
extern const far rom char showTemp1[] = "\r\n The current temperature is ";
extern const far rom char showTemp2[] = " degrees Celcius. \r\n\n Press Esc to return.\r\n";
//

//1.6: Calibrate Temperature
//

//1.2.1: Go to Azimuth Angle
extern const far rom char gotoAzAngle[] = "\r\n Enter the azimuth angle in degrees. \r\n";
extern const far rom char gotoAzAngleLCD[] = "Go to Azimuth";
extern const far rom char gotoElAngle[] = "\r\n Enter the elevation angle in degrees. \r\n";
extern const far rom char gotoELAngleLCD[] = "Go to Elevation";
extern const far rom char gotoAngle2[] = " The current minimum and maximum angles are ";
extern const far rom char angleStr[] = "Angle";
//

//1.2.2: Set Max Azimuth Angle
extern const far rom char maxAzStr[] = "Max Azimuth";
extern const far rom char maxAzSetStr[] = "Set Max Azimuth";
extern const far rom char maxAz1[] = " Enter a new maximum azimuth angle: \r\n";
extern const far rom char maxAz3[] = "\r\n Maximum azimuth angle set to ";
//

//1.2.2: Set Min Azimuth Angle
extern const far rom char currentMinAngleStr[] = "\r\n The current minimum angle is ";
extern const far rom char minAzStr[] = "Min Azimuth";
extern const far rom char minAzSetStr[] = "Set Min Azimuth";
extern const far rom char minAz1[] = " Enter a new minimum azimuth angle: \r\n";
extern const far rom char minAz3[] = "\r\n Minimum azimuth angle set to ";
//

//1.2.3: Calibrate Azimuth / Elevation
extern const far rom char calibrateAngle1[] = "\r\n Enter the true angle of the current position \r\n";
//

//1.3.2: Set Max Elevation Angle
extern const far rom char maxElStr[] = "Max Elevation";
extern const far rom char maxElSetStr[] = "Set Max Elevation";
//extern const far rom char maxEl1[] = "\r\n The current maximum elevation angle is ";
extern const far rom char maxEl1[] = " Enter a new maximum elevation angle: \r\n";
extern const far rom char maxEl3[] = "\r\n Maximum elevation angle set to ";
//

//1.3.2: Set Min Elevation Angle
extern const far rom char minElStr[] = "Min Elevation";
extern const far rom char minElSetStr[] = "Set Min Elevation";
//extern const far rom char minEl1[] = "\r\n The current minimum elevation angle is ";
extern const far rom char minEl1[] = " Enter a new minimum elevation angle: \r\n";
extern const far rom char minEl3[] = "\r\n Minimum elevation angle set to ";
//

//1.4.1 Range Min
extern const far rom char minRngStr[] = "Min Range";
extern const far rom char minRngSetStr[] = "Set Min Range";
extern const far rom char minRngSerialStr[] = "Enter a new minimum range: \r\n";
//

// 1.4.2 Range Max
extern const far rom char maxRngStr[] = "Max Range";
extern const far rom char maxRngSetStr[] = "Set Max Range";
extern const far rom char maxRngSerialStr[] = "Enter a new minimum range: \r\n";
//

extern void initialiseMenu(void);
extern char checkForSerialInput(void);
extern void menuISR(void);
extern void serviceMenu(void);


