/*
 * File:   Menusystem.h
 * Author: Jacob
 *
 * Created on 7 October 2014, 9:56 PM
 */


//Global
extern const rom char newLine[];
extern const rom char CHOOSE[];
extern const rom char menuPrefix3[];
extern const rom char menuPrefix4[];
extern const rom char menuPrefix5[];
extern const rom char menuPrefix8[];
extern const rom char goUp[];
extern const rom char goUp2[];
extern const rom char errNumOutOfRange[];
extern const rom char and[];
//

//1: Top
extern const rom char welcome[];
extern const rom char welcomeLcd[];
extern const far rom char topOption1[];
extern const far rom char topOption2[];
extern const far rom char topOption3[];
extern const far rom char topOption4[];
extern const far rom char topOption5[];
extern const far rom char topOptionCalTemp[];
extern const far rom char topOptionLocal[];
extern const far rom char topOptionFactory[];
extern const far rom char topOptionRemote[];
extern const far rom char topOptionRemoteLCD[];
//

//1.1: Automatic tracking
//extern const far rom char automessage[];
//extern const far rom char autoinit[];
//extern const far rom char autohelp1[];
////extern const far rom char autohelp2[];
////extern const far rom char autohelp3[];
//extern const far rom char autogo[];
//extern const far rom char autorange[];
//extern const far rom char autoeleva[];
//extern const far rom char autoazimu[];
//extern const far rom char autostatu[];
//extern const far rom char autoend[];
//

//1.2: Azimuth Menu
extern const rom char azMenu[];
extern const rom char azMenuLcd[];
extern const far rom char azOption1[];
extern const far rom char azOption2[];
extern const far rom char azOption3[];
extern const far rom char azOption4[];
//

//1.3: Elevation Menu
extern const rom char elMenu[];
extern const rom char elMenuLcd[];
extern const far rom char elOption1[];
extern const far rom char elOption2[];
extern const far rom char elOption3[];
extern const far rom char elOption4[];
//

//1.4: Range Menu
extern const rom char rngMenu[];
extern const rom char rngMenuLcd[];
extern const far rom char rngOption1[];
extern const far rom char rngOption2[];
extern const far rom char rngOption3[];
extern const far rom char rngOption4[];
extern const far rom char rngOption5[];
extern const far rom char rngOption6[];
extern const far rom char rngOption7[];
//

//1.5: Show Temp
extern const far rom char showTempLCDTitle[];
extern const far rom char showTempLCD[];
extern const far rom char showTemp1[];
extern const far rom char showTemp2[];
//

//1.6: Calibrate Temperature
//

//1.2.1: Go to Azimuth Angle
extern const far rom char gotoAzAngle[];
extern const far rom char gotoAzAngleLCD[];
extern const far rom char gotoElAngle[];
extern const far rom char gotoELAngleLCD[];
extern const far rom char gotoAngle2[];
extern const far rom char angleStr[];
//

//1.2.2: Set Max Azimuth Angle
extern const far rom char maxAzStr[];
extern const far rom char maxAzSetStr[];
extern const far rom char maxAz1[];
extern const far rom char maxAz3[];
//

//1.2.2: Set Min Azimuth Angle
extern const far rom char currentMinAngleStr[];
extern const far rom char minAzStr[];
extern const far rom char minAzSetStr[];
extern const far rom char minAz1[];
extern const far rom char minAz3[];
//

//1.2.3: Calibrate Azimuth / Elevation
extern const far rom char calibrateAngle1[];
//

//1.3.2: Set Max Elevation Angle
extern const far rom char maxElStr[];
extern const far rom char maxElSetStr[];
//extern const far rom char maxEl1[];
extern const far rom char maxEl1[];
extern const far rom char maxEl3[];
//

//1.3.2: Set Min Elevation Angle
extern const far rom char minElStr[];
extern const far rom char minElSetStr[];
//extern const far rom char minEl1[];
extern const far rom char minEl1[];
extern const far rom char minEl3[];
//

//1.4.1 Range Min
extern const far rom char minRngStr[];
extern const far rom char minRngSetStr[];
extern const far rom char minRngSerialStr[];
//

// 1.4.2 Range Max
extern const far rom char maxRngStr[];
extern const far rom char maxRngSetStr[];
extern const far rom char maxRngSerialStr[];
//

extern void initialiseMenu(void);
extern char checkForSerialInput(void);
extern void menuISR(void);
extern void serviceMenu(void);


