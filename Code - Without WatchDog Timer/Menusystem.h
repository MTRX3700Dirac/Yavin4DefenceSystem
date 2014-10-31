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
extern const rom char inputNumRangeStr[];
extern const rom char and[];
extern const rom char tab[];
extern const rom char hz[];
//

//1: Top
extern const rom char title[];
extern const rom char welcomeLcd[];
extern const rom char topOption1[];
extern const rom char topOption2[];
extern const rom char topOption3[];
extern const rom char topOption4[];
extern const rom char topOption5[];
extern const rom char topOptionCalTemp[];
extern const rom char topOptionLocal[];
extern const rom char topOptionForFactory[];
extern const rom char topOptionRemote[];
extern const rom char topOptionRemoteLCD[];
//

//1.1: Automatic tracking
//extern const rom char automessage[];
//extern const rom char autoinit[];
//extern const rom char autohelp1[];
////extern const rom char autohelp2[];
////extern const rom char autohelp3[];
//extern const rom char autogo[];
//extern const rom char autorange[];
//extern const rom char autoeleva[];
//extern const rom char autoazimu[];
//extern const rom char autostatu[];
//extern const rom char autoend[];
//

//1.2: Azimuth Menu
extern const rom char azMenu[];
extern const rom char azMenuLcd[];
extern const rom char azOption1[];
extern const rom char azOption2[];
extern const rom char azOption3[];
extern const rom char azOption4[];
//

//1.3: Elevation Menu
extern const rom char elMenu[];
extern const rom char elMenuLcd[];
extern const rom char elOption1[];
extern const rom char elOption2[];
extern const rom char elOption3[];
extern const rom char elOption4[];
//

//1.4: Range Menu
extern const rom char rngMenu[];
extern const rom char rngMenuLcd[];
extern const rom char rngOption1[];
extern const rom char rngOption2[];
extern const rom char rngOption3[];
extern const rom char rngOption4[];
extern const rom char rngOption5[];
extern const rom char rngOption6[];
extern const rom char rngOption7[];
//

//1.5: Show Temp
extern const rom char showTempLCDTitle[];
extern const rom char showTempLCD[];
extern const rom char showTemp1[];
extern const rom char showTemp2[];
//

//1.6: Calibrate Temperature
//

//1.2.1: Go to Azimuth Angle
extern const rom char gotoAzAngle[];
extern const rom char gotoAzAngleLCD[];
extern const rom char gotoElAngle[];
extern const rom char gotoELAngleLCD[];
extern const rom char gotoAngle2[];
extern const rom char angleStr[];
//

//1.2.2: Set Max Azimuth Angle
extern const rom char maxAzStr[];
extern const rom char maxAzSetStr[];
extern const rom char maxAz1[];
extern const rom char maxAz3[];
//

//1.2.2: Set Min Azimuth Angle
extern const rom char currentMinAngleStr[];
extern const rom char minAzStr[];
extern const rom char minAzSetStr[];
extern const rom char minAz1[];
extern const rom char minAz3[];
//

//1.2.3: Calibrate Azimuth / Elevation
extern const rom char calibrateAngle1[];
//

//1.3.2: Set Max Elevation Angle
extern const rom char maxElStr[];
extern const rom char maxElSetStr[];
//extern const rom char maxEl1[];
extern const rom char maxEl1[];
extern const rom char maxEl3[];
//

//1.3.2: Set Min Elevation Angle
extern const rom char minElStr[];
extern const rom char minElSetStr[];
//extern const rom char minEl1[];
extern const rom char minEl1[];
extern const rom char minEl3[];
//

//1.4.1 Range Min
extern const rom char minRngStr[];
extern const rom char minRngSetStr[];
extern const rom char minRngSerialStr[];
//

// 1.4.2 Range Max
extern const rom char maxRngStr[];
extern const rom char maxRngSetStr[];
extern const rom char maxRngSerialStr[];
//

extern void initialiseMenu(systemState *state);
extern char checkForSerialInput(void);
extern void menuISR(void);
extern void serviceMenu(void);
extern void dispTrack(TrackingData target);
extern void dispSearching(void);
extern void dispRawRange(void);

