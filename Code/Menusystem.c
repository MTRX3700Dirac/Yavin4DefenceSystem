/*!******************************************************************************
 * File:   Menusystem.c
 * Author:
 *
 * Description:
 *
 * Duties:
 *
 * Functions:
 *
 * Created on 16 September 2014, 6:47 PM
 *******************************************************************************/

#include "Common.h"
#include "Serial.h"
#include "User_Interface.h"
#include "Menusystem.h"
#include "LCD.h"
#include "Range.h"
#include "PanTilt.h"

#define ERR_NUM_OUT_OF_RANGE -1000
#define ERR_NOT_NUMERIC -2000
#define ERR_NO_NUMBER -3000
#define ESC_PRESSED -4000
#define MINUS_CHAR 0x2D

// The time to check timer 0 against
// 1953 = approx 0.1s on MNML
#define UPDATE_TIME 1953

/*! Global variable with the current menu position */
static menuState m_currentMenu;

/*! Global variable with the current user mode: Local, remote or factory */
static userState m_userMode;


void menu();

//Menus
// UI Menus
void topMenu(void);
void elevationMenu(void);
void azimuthMenu(void);
void rangeMenu(void);

// Functional Menus
void trackingMenu(void);
void gotoElevation(void);
void gotoAzimuth(void);
void setElevationMax(void);
void setElevationMin(void);
void setAzimuthMax(void);
void setAzimuthMin(void);
void setMaxRange(void);
void setMinRange(void);
void showTemp(void);

// Factory Menus
void calibrateTempMenu(void);
void calibrateAzimuth(void);
void calibrateElevation(void);
void usSampleRate(void);
void usSamplesPerAvg(void);
void irSampleRate(void);
void irSamplesPerAvg(void);
void rawRangeMenu(void);

// Mode changes
void changeUserState(userState);

// Serial Display
void topmenudisp(void);
void dispTopOptions(void);
void dispAzOptions(void);
void dispElOptions(void);
void dispRngOptions(void);
void sendROM(const static rom char *romchar);
void clearScreen(void);
void sendNewLine(char length);
void filler(char length);
void errOutOfRange(int lowerBound, int upperBound);
char* intToAscii(int num);
void autodisp(void);

int parseNumeric(char *input);
int waitForNumericInput(void);
void configureTimer0(void);
int waitForLocalInputMenu(int maxStates, int (*function)(int));
int waitForLocalInputValue(int min, int max, int interval);

char* dispLCDTopMenu(int option);
char* dispLCDAzMenu(int option);
char* dispLCDElMenu(int option);
char* dispLCDRngMenu(int option);

// *****************************************************************************
// *********************** MENU STRUCTURE FUNCTIONS ****************************
// *****************************************************************************

/*!
 * Description: General service function used to switch between menus
 */
void menu() {
    m_currentMenu = TOP_LEVEL;

    while (1) {
        switch (m_currentMenu) {
            case TOP_LEVEL:
                topMenu();
                break;
            case TRACKING:
                trackingMenu();
                break;
            case AZ_MENU:
                azimuthMenu();
                break;
            case EL_MENU:
                elevationMenu();
                break;
//            case RANGE_MENU:
//                rangeMenu();
//                break;
            case SHOW_TEMP:
                showTemp();
                break;
            case CALIBRATE_TEMP:
                calibrateTempMenu();
                break;
                // AZIMUTH MENUS
            case AZ_GOTO:
                gotoAzimuth();
                break;
            case AZ_MAX:
                setAzimuthMax();
                break;
            case AZ_MIN:
                setAzimuthMin();
                break;
            case AZ_CALIBRATE:
                calibrateAzimuth();
                break;
                // ELVEVATION MENUS
            case EL_GOTO:
                gotoElevation();
                break;
            case EL_MAX:
                setElevationMax();
                break;
            case EL_MIN:
                setElevationMin();
                break;
            case EL_CALIBRATE:
                calibrateElevation();
                break;
//                // RANGE MENUS
//            case RANGE_MAX:
//                setMaxRange();
//                break;
//            case RANGE_MIN:
//                setMinRange();
//                break;
//            case US_SAMPLE_RATE:
//                usSampleRate();
//                break;
//            case US_SAMPLE_AVG:
//                usSamplesPerAvg();
//                break;
//            case IR_SAMPLE_RATE:
//                irSampleRate();
//                break;
//            case IR_SAMPLE_AVG:
//                irSamplesPerAvg();
//                break;
//            case RANGE_RAW:
//                rawRange();
//                break;
        }
    }
}

/*!
 * @description: Transmits the given string from ROM over serial
 *
 * @input The string to transmit
 */
void sendROM(const static rom char *romchar) {
    char temp[80] = {0};
    int j;
    strcpypgm2ram(temp, romchar);
//    for (index = 0; *romchar && index < 80; index++) {
//        temp[index] = *romchar;
//        romchar++;
//    }
    transmit(temp);
    for (j = 0; j < 8000; j++);
}

/*!
 * @description: Prints a number of new line (\r\n) characters.
 *
 */
void sendNewLine(char length) {

    while (length) {
        sendROM(newLine);
        length--;
    }
}

/*!
 * Clears the Serial display
 */
void clearScreen()
{
    char index;
    char temp[height + 2] = {0};        // This is two greater for the \r and end message characters
    int j;

    // Fills the buffer with \n characters
    for (index = 0; index<height; index++) {
        temp[index] = newLine[1];
    }
    // End with a line return
    temp[height] = '\r';
    transmit(temp);
    for (j = 0; j < 1000; j++);
}

void filler(char length) {
    char index = 0;
    char temp[81] = {0};
    int j;
    for (; length > 0; length--) {
        temp[index] = fillerChar[0];
        index++;
    }
    //strcpypgm2ram(temp, romchar);
    transmit(temp);
    for (j = 0; j < 1000; j++);
}

/*! **********************************************************************
 * Function: initialiseMenu(void)
 *
 * \brief Initialises the menu system
 *
 * Include: Menusystem.h
 *
 * Description: initialises the menu system so that it is fully operational
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void initialiseMenu(void) {
    m_currentMenu = TOP_LEVEL;
    m_userMode = REMOTE;
    configureSerial();
    lcdInit();
    configUSER();
    configureTimer0();
}

void configureTimer0(void)
{
    T0CON = 0b00000110;     // Select internal clock, 128x prescalar
    T0CONbits.TMR0ON = 1;   // Enable Timer 1;
}

/*! **********************************************************************
 * Function: waitForInput(void)
 *
 * \brief services any user interface with the menu
 *
 * Include:
 *
 * Description: Checks the serial/local buffers for inputs
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void waitForSerialInput(void) {
    char inputReceived = 0;
    while (inputReceived == 0)
    {
        inputReceived = receiveCR() | receiveEsc(); //!Wait until the receive buffer is no longer empty
        //!Indicating that a command has been passed
    }
}

/*! **********************************************************************
 * Function: menuISR(void)
 *
 * \brief ISR function for the menu subsystem
 *
 * Include: Menusystem.h
 *
 * Description: services any interrupts associated with the menu system
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void menuISR(void) {

}

/*! **********************************************************************
 * Function: parseNumeric(char *number)
 *
 * \brief parses user input string into a number
 *
 * Include:
 *
 * Description: Converts ASCOO input to a number, and records an error for
 *              non-numeric input, or if the number is larger than 4 digits.
 *              No number used by the user in this program will be larger
 *              than 4 digits.
 *
 * Arguments: The ASCII string to decode
 *
 * Returns: The integer result of the string
 *          ERR_NOT_NUMERIC for any non-numeric input
 *          ERR_NUM_OUT_OF_RANGE for 0 digits or 5+ digits
 *************************************************************************/
int parseNumeric(char *number)
{
    char digits = 0;
    char index;
    char tempDigits[4] = {0};
    signed char multiplier = 1;

    // Array to hold powers of 10 for multiplication
    int decimalPowers[] = {1, 10, 100, 1000};
    int result = 0;

    // Check if any number was given.
    if (*number == 0x0D) return ERR_NO_NUMBER;

    if (*number == MINUS_CHAR)
    {
        // Negative number, so multiply by -1 and move to the next digit
        multiplier = -1;
        number++;
    }
    // Only need first 4 digits, as the biggest input is 3
    for (; *number != 0x0D; digits++)    //Count number of digits
    {
        // Return error if more than 4 digits were given
        if (digits >= 4) return ERR_NUM_OUT_OF_RANGE;
        if (*number < 0x30 && *number > 0x39) return ERR_NOT_NUMERIC;    // Not a numeric input

        // Store the number in a temporary buffer
        tempDigits[digits] = *number - 0x30;
        number++;
    }

    // Multiply the digits to get the result
    for(index = 0; digits >0; digits--)
    {
        result += ((int) tempDigits[index] * decimalPowers[digits-1]);
        index++;
    }

    return multiplier * result;
}

void errOutOfRange(int lowerBound, int upperBound)
{
    sendROM(errNumOutOfRange);
    transmit(intToAscii(lowerBound));
    sendROM(and);
    transmit(intToAscii(upperBound));
    sendNewLine(1);
}

/*! **********************************************************************
 * Function: waitForNumericInput
 *
 * \brief Waits for input and parses number
 *
 * Include:
 *
 * Description: Waits in a loop for a user command ended with a new line character.
 *              Once a command is received, it is converted into the appropriate
 *              numeric value that the user has given.
 *
 * Arguments: None
 *
 * Returns: The integer result of the string input
 *          ERR_NOT_NUMERIC for any non-numeric input
 *          ERR_NUM_OUT_OF_RANGE for 0 digits or 5+ digits
 *          ESC_PRESSED if escape was pressed
 *************************************************************************/
int waitForNumericInput()
{
    char userget[80] = {0};
    waitForSerialInput();
    if (receiveEsc())
    {
        popEsc();
        return ESC_PRESSED;
    }
    readString(userget); //!Get the input string and store it in @userget
    return parseNumeric(userget);
}

int waitForLocalInputMenu(int maxStates, int (*function)(int))
{
    int inputResult, adcResult;
    char counter;

    WriteTimer0(0);
    while(userEmpty())       //!Wait until the receive buffer is no longer empty
    {
        // Only refresh the screen every 100ms
        if(ReadTimer0() >= UPDATE_TIME)
        {
            // If a 300 milliseconds has passed
            if(counter >= 3)
            {
                adcResult = readDialForMenu(maxStates);
                sendROM(function(adcResult));
                counter = 0;
            }
            else counter++;
            WriteTimer0(0);
        }
    }

    // Confirm the user's input
    inputResult = userPop();
    if (inputResult == CONFIRM_CHAR)
    {
        return adcResult;
    }
    else
    {
        return ESC_PRESSED;
    }
}

int waitForLocalInputValue(int min, int max, int interval)
{
    int inputResult, adcResult;
    char counter;

    WriteTimer0(0);
    while(userEmpty())       //!Wait until the receive buffer is no longer empty
    {
        // Only refresh the screen every 100ms
        if(ReadTimer0() >= UPDATE_TIME)
        {
            // If a second has passed
            if(counter >= 1)
            {
                adcResult = readDial((max - min)/interval);
                adcResult = min + interval*adcResult;
                transmit(intToAscii(adcResult));
                sendNewLine(1);
                counter = 0;
            }
            else counter++;
            WriteTimer0(0);
        }
    }

    // Confirm the user's input
    inputResult = userPop();
    if (inputResult == CONFIRM_CHAR)
    {
        return adcResult;
    }
    else
    {
        return ESC_PRESSED;
    }
}

/*
 * Can only print numbers under 4 digits
 */
char* intToAscii(int num)
{
    char string[10] = {0};
    itoa(num, string);
    return string;
}

// *****************************************************************************
// **************************** TOP LEVEL MENU *********************************
// *****************************************************************************

void topMenu(void) {

    int inputResult = 0;

    topmenudisp(); //!Display the menu screen via serial
    //!wait for/get serial input
    //!make decision based on input
    while (m_currentMenu == TOP_LEVEL)
    {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            inputResult = waitForNumericInput();
        }
        else
        {
            inputResult = waitForLocalInputMenu(6, dispLCDTopMenu);
        }

        switch (inputResult) {
            case ESC_PRESSED:
                break;
            case ERR_NO_NUMBER:
                break;
            case 1:
                //auto();
                m_currentMenu = TRACKING;
                break;
            case 2:
                // Go to the Azimuth menu
                m_currentMenu = AZ_MENU;
                break;
            case 3:
                // Go to the Elevation Menu
                m_currentMenu = EL_MENU;
                break;
            case 4:
                // Go to Range Menu
                m_currentMenu = RANGE_MENU;
                break;
            case 5:
                // Show Temperature
                m_currentMenu = SHOW_TEMP;
                break;
            case 6:
                // If Factory mode is on, calibrate Temperature
                if (m_userMode == FACTORY) {
                    m_currentMenu = CALIBRATE_TEMP;
                    break;
                }
                else
                {
                    // Switch user mode!
                    if (m_userMode == REMOTE)
                    {
                        m_userMode = LOCAL;
                    }
                    else if (m_userMode == LOCAL)
                    {
                        m_userMode = REMOTE;
                    }
                    break;
                }
            default:
                errOutOfRange(1, 5);
                break;
        }
    }
}

void dispTopOptions(void) {

    sendROM(topOption1);
    sendROM(topOption2);
    sendROM(topOption3);
    sendROM(topOption4);
    sendROM(topOption5);

    if (m_userMode == FACTORY)
    {
        sendROM(topOptionCalTemp);
        sendROM(topOptionRemote);
    }
    else
    {
        sendROM(topOptionLocal);
//        if(factoryEnabled()) send(topOptionFactory);
    }
}

/*!
 * Displays the current potentiometer reading on the LCD
 *
 */
char* dispLCDTopMenu(int option)
{
    char *string;
    switch(option)
    {
        case 1:
            string = topOption1;
            break;
        case 2:
            string = topOption2;
            break;
        case 3:
            string = topOption3;
            break;
        case 4:
            string = topOption4;
            break;
        case 5:
            string = topOption5;
            break;
        case 6:
            string = topOptionRemote;
            break;
        default:
            string = "How did you even?";
    }
    return string;
}

void topmenudisp(void) {
    clearScreen();
    //sendNewLine(height);
    filler(width);
    sendROM(newLine);
    filler(22);
    sendROM(welcome);
    filler(21);
    sendROM(newLine);
    filler(width);
    sendROM(newLine);
    sendNewLine(2);
    dispTopOptions();
    sendNewLine(2);
    sendROM(CHOOSE);
    sendNewLine((height - 16));
    filler(width);
    sendNewLine(1);
}

/*!
 * Displays the current temperature
 */
void showTemp() {
    int userInput;
    unsigned char temp = 25;

    char string[20] = "\n\rSHOW TEMP\r\n";
    transmit(string);

    //@TODO temp = getTemp

    // Display the temperature
    sendROM(showTemp1);
    transmit(intToAscii(temp));
    sendROM(showTemp2);

    while (m_currentMenu == SHOW_TEMP)
    {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            userInput = waitForNumericInput();
        }
        else
        {
            while(userEmpty());       //!Wait until the receive buffer is no longer empty
            // Confirm the user's input
            if (userPop() == BACK_CHAR)
            {
                userInput =  ESC_PRESSED;
            }
        }

        if (userInput == ESC_PRESSED)
        {
            m_currentMenu = TOP_LEVEL;
        }
    }
}

/*!
 * Displays the current temperature
 */
void calibrateTempMenu() {
    int userInput;

    char string[20] = "\n\rCALIBRATE TEMP\r\n";
    transmit(string);

    while (m_currentMenu == CALIBRATE_TEMP) {
        waitForSerialInput();
        readString(&userInput); //!Get the input string and store it in @userget
        m_currentMenu = TOP_LEVEL;
    }
}

// *****************************************************************************
// ***************************** TRACKING MENU *********************************
// *****************************************************************************

/*!
 * Searches and tracks a found object
 */
void trackingMenu() {
    int userInput;
    char counter = 0;

    char string[20] = "\n\rTRACKING\r\n";
    transmit(string);
    // Begin Timer
    WriteTimer0(0);

    while (m_currentMenu == TRACKING) {

        // Only refresh the screen every 100ms
        if(ReadTimer0() >= UPDATE_TIME)
        {
            if(receiveEsc())
            {
                popEsc();
                m_currentMenu = TOP_LEVEL;
            }

            if(counter == 10)
            {
                transmit(string);
                counter = 0;
            }
            else counter++;
            WriteTimer0(0);
        }
    }
}

void autodisp(void) {
    sendNewLine(height);
    filler(width);
    sendROM(newLine);
    filler(23);
    sendROM(automessage);
    filler(23);
    sendROM(newLine);
    filler(width);
    sendROM(newLine);
    sendNewLine(2);
    sendROM(autoinit);
    sendNewLine(2);
    sendROM(autohelp1);
    sendROM(newLine);
    //send(autohelp2);
    //send(autohelp3);
}

// *****************************************************************************
// **************************** AZIMUTH MENUS **********************************
// *****************************************************************************

void azimuthMenu(void) {
    int inputResult;

    sendROM(azMenu);
    dispAzOptions();        // Display the menu options

    while (m_currentMenu == AZ_MENU) {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            inputResult = waitForNumericInput();
        }
        else
        {
            inputResult = waitForLocalInputMenu(3, dispLCDAzMenu);
        }

        switch (inputResult) {
            case ESC_PRESSED:
                m_currentMenu = TOP_LEVEL;
                break;
            case 1:
                // Go to elevation angle
                m_currentMenu = AZ_GOTO;
                break;
            case 2:
                // Set elevation minimum
                m_currentMenu = AZ_MIN;
                break;
            case 3:
                // Set elevation maximum
                m_currentMenu = AZ_MAX;
                break;
            case 4:
                if (m_userMode == FACTORY) {
                    // Calibrate the elevation servo
                    m_currentMenu = AZ_CALIBRATE;
                } else {
                    // Go back one level
                    m_currentMenu = TOP_LEVEL;
                }
                break;
            case 5:
                if (m_userMode == FACTORY) {
                    // Calibrate the elevation servo
                    m_currentMenu = TOP_LEVEL;
                    break;
                }
                // If not in factory mode, this is an error;
            default:
                //@TODO error();
                break;
        }
    }
}
/*!
 * User menu for going to a specific azimuth angle
 */
void gotoAzimuth() {
    int userInput;
    Direction dir;

    //@TODO Display message
//    char string[20] = "\n\rGO TO AZIMUTH\r\n";
//    transmit(string);

    sendROM(gotoAzAngle);
    sendROM(gotoAngle2);
    transmit(intToAscii(getMinAzimuthAngle()));
    sendROM(and);
    transmit(intToAscii(getMaxAzimuthAngle()));
    sendNewLine(1);

    while (m_currentMenu == AZ_GOTO) {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            userInput = waitForNumericInput();
        }
        else
        {
            userInput = waitForLocalInputValue(getMinAzimuthAngle(), getMaxAzimuthAngle(), 2);
        }

        if (userInput == ESC_PRESSED)
        {
            m_currentMenu = AZ_MENU;
        }
        else
        {
            if (userInput >= getMinAzimuthAngle() &&
                    userInput <= getMaxAzimuthAngle())
            {
                dir.azimuth = userInput;
                dir.inclination = getDir().inclination;
                move(dir);

                // Display message
                sendROM(gotoAngle3);
                transmit(intToAscii(userInput));
                sendNewLine(1);
            }
            else
            {
                 //Display Error Message
                errOutOfRange(getMinAzimuthAngle(), getMaxAzimuthAngle());
            }
        }
    }
}

/*!
 * User menu for setting the maximum azimuth angle
 */
void setAzimuthMax() {
    int userInput;
    char string[20] = "\n\rSET AZIMUTH MAX\r\n";
    transmit(string);

    while (m_currentMenu == AZ_MAX) {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            userInput = waitForNumericInput();
        }
        else
        {
            userInput = waitForLocalInputValue(MAX_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5);
        }

        if (userInput == ESC_PRESSED)
        {
            m_currentMenu = AZ_MENU;
        }
        else
        {
            //@TODO Check bounds, Display message
            //setMaxAzimuthAngle(userInput);
        }
    }
}

/*!
 * User menu for setting the minimum azimuth angle
 */
void setAzimuthMin() {
    int userInput;
    char string[20] = "\n\rSET AZIMUTH MIN\r\n";
    transmit(string);

    while (m_currentMenu == AZ_MIN) {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            userInput = waitForNumericInput();
        }
        else
        {
            userInput = waitForLocalInputValue(MIN_ANGLE_INFIMUM, MIN_ANGLE_SUPREMUM, 5);
        }

        if (userInput == ESC_PRESSED)
        {
            m_currentMenu = AZ_MENU;
        }
        else
        {
            //@TODO Check bounds, Display Message
            //setMinAzimuthAngle(userInput);
        }
    }
}

/*!
 * User menu for calibrating azimuth angle
 */
void calibrateAzimuth() {
    int userInput;
    char string[30] = "\n\rCALIBRATE AZIMUTH\r\n";
    transmit(string);

    while (m_currentMenu == AZ_CALIBRATE) {
        userInput = waitForNumericInput();

        if (userInput == ESC_PRESSED)
        {
            m_currentMenu = AZ_MENU;
        }
        else
        {
            //@TODO
        }
    }
}

/*!
 * Display the user options for the Azimuth menu
 */
void dispAzOptions()
{
    sendROM(azOption1);
    sendROM(azOption2);
    sendROM(azOption3);
    if (m_userMode == FACTORY)
    {
        sendROM(azOption4);
        sendROM(menuPrefix5);
        sendROM(goUp);
    }
    else
    {
        sendROM(menuPrefix4);
        sendROM(goUp);
    }
}

/*!
 * Displays the current potentiometer reading on the LCD
 *
 */
char* dispLCDAzMenu(int option)
{
    char *string;
    switch(option)
    {
        case 1:
            string = azOption1;
            break;
        case 2:
            string = azOption2;
            break;
        case 3:
            string = azOption3;
            break;
        default:
            string = "How did you even?";
    }
    return string;
}


// *****************************************************************************
// *************************** ELEVATION MENUS *********************************
// *****************************************************************************

void elevationMenu(void) {
    int inputResult;

    sendROM(elMenu);
    dispElOptions();      //!Display the menu screen via serial

    while (m_currentMenu == EL_MENU) {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            inputResult = waitForNumericInput();
        }
        else
        {
            inputResult = waitForLocalInputMenu(3, dispLCDElMenu);
        }

        switch (inputResult) {
            case ESC_PRESSED:
                m_currentMenu = TOP_LEVEL;
                break;
            case 1:
                // Go to elevation angle
                m_currentMenu = EL_GOTO;
                break;
            case 2:
                // Set elevation minimum
                m_currentMenu = EL_MIN;
                break;
            case 3:
                // Set elevation maximum
                m_currentMenu = EL_MAX;
                break;
            case 4:
                if (m_userMode == FACTORY) {
                    // Calibrate the elevation servo
                    m_currentMenu = EL_CALIBRATE;
                } else {
                    // Go back one level
                    m_currentMenu = TOP_LEVEL;
                }
                break;
            case 5:
                if (m_userMode == FACTORY) {
                    // Calibrate the elevation servo
                    m_currentMenu = TOP_LEVEL;
                    break;
                }
                // If not in factory mode, this is an error;
            default:
                if (m_userMode == FACTORY) errOutOfRange(1, 5);
                else errOutOfRange(1, 4);
                break;
        }
    }
}

/*!
 * User menu for going to a specific elevation angle
 */
void gotoElevation() {
    int userInput;
    Direction dir;

    char string[30] = "\n\rGO TO ELEVATION\r\n";
    transmit(string);

    while (m_currentMenu == EL_GOTO) {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            userInput = waitForNumericInput();
        }
        else
        {
            userInput = waitForLocalInputValue(getMinElevationAngle(), getMaxElevationAngle(), 2);
        }

        if (userInput == ESC_PRESSED)
        {
            m_currentMenu = EL_MENU;
        }
        else
        {
            if (userInput >= getMinElevationAngle() &&
                    userInput <= getMaxElevationAngle())
            {
                dir.azimuth = getDir().azimuth;
                dir.inclination = userInput;
                move(dir);
                // @TODO Display Message
            }
            else; //@TODO Display Message
        }
    }
}

/*!
 * User menu for setting the maximum elevation angle
 */
void setElevationMax() {
    int userInput;
    char string[30] = "\n\rSET ELEVATION MAX\r\n";
    transmit(string);

    while (m_currentMenu == EL_MAX) {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            userInput = waitForNumericInput();
        }
        else
        {
            userInput = waitForLocalInputValue(MAX_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5);
        }

        if (userInput == ESC_PRESSED)
        {
            m_currentMenu = EL_MENU;
        }
        else
        {
                // @TODO Display Message
        }
    }
}

/*!
 * User menu for setting the minimum elevation angle
 */
void setElevationMin() {
    int userInput;
    char string[30] = "\n\rSET ELEVATION MIN\r\n";
    transmit(string);

    while (m_currentMenu == EL_MIN) {
        if (m_userMode == REMOTE || m_userMode == FACTORY)
        {
            userInput = waitForNumericInput();
        }
        else
        {
            userInput = waitForLocalInputValue(MIN_ANGLE_INFIMUM, MIN_ANGLE_SUPREMUM, 5);
        }

        if (userInput == ESC_PRESSED)
        {
            m_currentMenu = EL_MENU;
        }
        else
        {
                // @TODO Display Message
        }
    }
}

/*!
 * User menu for calibrating elevation angle
 */
void calibrateElevation() {
    int userInput;
    char string[30] = "\n\rCALIBRATE ELEVATION\r\n";
    transmit(string);

    while (m_currentMenu == EL_CALIBRATE) {
        userInput = waitForNumericInput();

        if (userInput == ESC_PRESSED)
        {
            m_currentMenu = EL_MENU;
        }
        else
        {
                // @TODO Display Message
        }
    }
}

/*!
 * Display the user options for the Azimuth menu
 */
void dispElOptions()
{
    sendROM(elOption1);
    sendROM(elOption2);
    sendROM(elOption3);
    if (m_userMode == FACTORY)
    {
        sendROM(elOption4);
        sendROM(menuPrefix5);
        sendROM(goUp);
    }
    else
    {
        sendROM(menuPrefix4);
        sendROM(goUp);
    }
}

/*!
 * Displays the current potentiometer reading on the LCD
 *
 */
char* dispLCDElMenu(int option)
{
    char *string;
    switch(option)
    {
        case 1:
            string = elOption1;
            break;
        case 2:
            string = elOption2;
            break;
        case 3:
            string = elOption3;
            break;
        default:
            string = "How did you even?";
    }
    return string;
}

//// *****************************************************************************
//// ****************************** RANGE MENUS **********************************
//// *****************************************************************************
//
//void rangeMenu(void) {
//    int inputResult;
//    sendROM(rngMenu);
//    dispRngOptions();
//
//    while (m_currentMenu == RANGE_MENU) {
//        if (m_userMode == REMOTE || m_userMode == FACTORY)
//        {
//            inputResult = waitForNumericInput();
//        }
//        else
//        {
//            inputResult = waitForLocalInputMenu(2, dispLCDRngMenu);
//        }
//        switch (inputResult) {
//            case ESC_PRESSED:
//                m_currentMenu = TOP_LEVEL;
//                break;
//            case 1:
//                // Set the minimum range
//                m_currentMenu = RANGE_MIN;
//                break;
//            case 2:
//                // Set the maximum range
//                m_currentMenu = RANGE_MAX;
//                break;
//            case 3:
//                if (m_userMode == FACTORY) {
//                    // View the raw range data
//                    m_currentMenu = RANGE_RAW;
//                } else {
//                    // Go back one level
//                    m_currentMenu = TOP_LEVEL;
//                }
//                break;
//            case 4:
//                if (m_userMode == FACTORY) {
//                    // Set the ultrasound sample rate
//                    m_currentMenu = US_SAMPLE_RATE;
//                } else {
//                    errOutOfRange(1, 3);    // Display an error
//                }
//                break;
//            case 5:
//                if (m_userMode == FACTORY) {
//                    // Set the number of estimations per sample
//                    m_currentMenu = US_SAMPLE_AVG;
//                }
//                else {
//                    errOutOfRange(1, 3);    // Display an error
//                }
//                break;
//            case 6:
//                if (m_userMode == FACTORY) {
//                    // Set the IR sample rate
//                    m_currentMenu = IR_SAMPLE_RATE;
//                }
//                else {
//                    errOutOfRange(1, 3);    // Display an error
//                }
//                break;
//            case 7:
//                if (m_userMode == FACTORY) {
//                    // Set the number of estimations per sample
//                    m_currentMenu = IR_SAMPLE_AVG;
//                }
//                else {
//                    errOutOfRange(1, 3);    // Display an error
//                }
//                break;
//            default:
//                if (m_userMode == FACTORY) {
//                    // Set the number of estimations per sample
//                    errOutOfRange(1,7);
//                }
//                else {
//                    errOutOfRange(1, 3);    // Display an error
//                }
//                break;
//        }
//    }
//}
//
///*!
// * User menu for setting the minimum range of the system
// */
//void setMinRange() {
//    int userInput;
//    char string[30] = "\n\rSET MIN RANGE\r\n";
//    transmit(string);
//
//    while (m_currentMenu == RANGE_MIN) {
//        if (m_userMode == REMOTE || m_userMode == FACTORY)
//        {
//            userInput = waitForNumericInput();
//        }
//        else
//        {
//            userInput = waitForLocalInputValue(MIN_RANGE_INFIMUM, MIN_RANGE_SUPREMUM, 50);
//        }
//
//        if (userInput == ESC_PRESSED)
//        {
//            m_currentMenu = RANGE_MENU;
//        }
//        else
//        {
//                // @TODO Display Message
//        }
//    }
//}
//
///*!
// * User menu for setting the maximum range for the system
// */
//void setMaxRange() {
//    int userInput;
//
//    char string[30] = "\n\rSET MAX RANGE\r\n";
//    transmit(string);
//
//    while (m_currentMenu == RANGE_MAX) {
//        if (m_userMode == REMOTE || m_userMode == FACTORY)
//        {
//            userInput = waitForNumericInput();
//        }
//        else
//        {
//            userInput = waitForLocalInputValue(MAX_RANGE_INFIMUM, MAX_RANGE_SUPREMUM, 100);
//        }
//
//        if (userInput == ESC_PRESSED)
//        {
//            m_currentMenu = RANGE_MENU;
//        }
//        else
//        {
//                // @TODO Display Message
//        }
//    }
//}
//
///*!
// * User menu viewing raw IR and US data
// */
//void rawRangeMenu() {
//    char counter;
//    char string[30] = "\n\rVIEW RAW RANGE DATA\r\n";
//    transmit(string);
//
//    WriteTimer0(0);
//
//    while (m_currentMenu == RANGE_RAW) {
//        // Only refresh the screen every 100ms
//        if(ReadTimer0() >= UPDATE_TIME)
//        {
//            if(receiveEsc())
//            {
//                popEsc();
//                m_currentMenu = RANGE_MENU;
//            }
//
//            if(counter == 10)
//            {
//                transmit(string);
//                counter = 0;
//            }
//            else counter++;
//            WriteTimer0(0);
//        }
//    }
//}
//
///*!
// * User menu for setting Ultrasound sample rate
// */
//void usSampleRate() {
//    int userInput;
//    char string[30] = "\n\rSET US SAMPLE RATE\r\n";
//    transmit(string);
//
//    while (m_currentMenu == US_SAMPLE_RATE) {
//        if (m_userMode == REMOTE || m_userMode == FACTORY)
//        {
//            userInput = waitForNumericInput();
//        }
//        else
//        {
//            //@TODO userInput = waitForLocalInputValue(SOMETHING, SOMETHING_ELSE, 5);
//        }
//
//        if (userInput == ESC_PRESSED)
//        {
//            m_currentMenu = RANGE_MENU;
//        }
//        else
//        {
//                // @TODO Display Message
//        }
//    }
//}
//
///*!
// * User menu for setting Ultrasound samples per average
// */
//void usSamplesPerAvg() {
//    int userInput;
//    char string[30] = "\n\rSET US SAMPLES PER AVG\r\n";
//    transmit(string);
//
//    while (m_currentMenu == US_SAMPLE_AVG) {
//        if (m_userMode == REMOTE || m_userMode == FACTORY)
//        {
//            userInput = waitForNumericInput();
//        }
//        else
//        {
//            userInput = waitForLocalInputValue(SAMPLE_PER_AVG_MIN, SAMPLE_PER_AVG_MAX, 1);
//        }
//
//        if (userInput == ESC_PRESSED)
//        {
//            m_currentMenu = RANGE_MENU;
//        }
//        else
//        {
//                // @TODO Display Message
//        }
//    }
//}
//
///*!
// * User menu for setting Infrared sample rate
// */
//void irSampleRate() {
//    int userInput;
//    char string[30] = "\n\rSET IR SAMPLE RATE\r\n";
//    transmit(string);
//
//    while (m_currentMenu == IR_SAMPLE_RATE) {
//        if (m_userMode == REMOTE || m_userMode == FACTORY)
//        {
//            userInput = waitForNumericInput();
//        }
//        else
//        {
//            //@TODO userInput = waitForLocalInputValue(SOMETHING, SOMETHING_ELSE, 5);
//        };
//
//        if (userInput == ESC_PRESSED)
//        {
//            m_currentMenu = RANGE_MENU;
//        }
//        else
//        {
//                // @TODO Display Message
//        }
//    }
//}
//
///*!
// * User menu for setting IR samples per average
// */
//void irSamplesPerAvg() {
//    int userInput;
//    char string[30] = "\n\rSET IR SAMPLES PER AVG\r\n";
//    transmit(string);
//
//    while (m_currentMenu == IR_SAMPLE_AVG) {
//        if (m_userMode == REMOTE || m_userMode == FACTORY)
//        {
//            userInput = waitForNumericInput();
//        }
//        else
//        {
//            userInput = waitForLocalInputValue(SAMPLE_PER_AVG_MIN, SAMPLE_PER_AVG_MAX, 1);
//        }
//
//        if (userInput == ESC_PRESSED)
//        {
//            m_currentMenu = RANGE_MENU;
//        }
//        else
//        {
//                // @TODO Display Message
//        }
//    }
//}
//
///*!
// * Display the user options for the Azimuth menu
// */
//void dispRngOptions()
//{
//    sendROM(rngOption1);
//    sendROM(rngOption2);
//    if (m_userMode == FACTORY)
//    {
//        sendROM(rngOption3);
//        sendROM(rngOption4);
//        sendROM(rngOption5);
//        sendROM(rngOption6);
//        sendROM(rngOption7);
//        sendROM(menuPrefix8);
//        sendROM(goUp);
//    }
//    else
//    {
//        sendROM(menuPrefix3);
//        sendROM(goUp);
//    }
//}
///*!
// * Displays the current potentiometer reading on the LCD
// *
// */
//char* dispLCDRngMenu(int option)
//{
//    char *string;
//    switch(option)
//    {
//        case 1:
//            string = rngOption1;
//            break;
//        case 2:
//            string = rngOption2;
//            break;
//        default:
//            string = "How did you even?";
//    }
//    return string;
//}





