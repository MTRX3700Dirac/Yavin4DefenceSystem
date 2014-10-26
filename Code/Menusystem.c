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
#include "Temp.h"
//#include "Menu_Strings.h"

#include "MenuDefs.h"



// Serial Display
//void sendROM(const static rom char *romchar);
static void sendROM(const rom char *romchar);
static void clearScreen(void);
static void sendNewLine(char length);
static void filler(char length);
static void errOutOfRange(int lowerBound, int upperBound);
static char* intToAscii(int num);
static void autodisp(void);

static int parseNumeric(char *input);
static int getSerialNumericInput(void);
static void configureTimer0(void);
static int getLocalInputMenu(int maxStates, int (*function)(int));
static int getLocalPotResult(int min, int max, int interval);

// Confirm Methods
static void setValue(int input);
static void setMenu(struct menuStruct menu);
static void navigateTopMenu(int inputResult);
static void noFunctionNumeric(int input);

// Return Methods
static void noFunction(void);
static void returnToTopMenu(void);
static void returnToAzMenu(void);
static void returnToElMenu(void);
static void returnToRngMenu(void);

// Navigation Methods
static void navigateTopMenu(int inputResult);
static void navigateAzimuthMenu(int inputResult);
static void navigateElevationMenu(int inputResult);
static void navigateRangeMenu(int inputResult);

// Display methods
static void dispTopOptions(void);
static void displayMenuSerial();
static void dispTopOptions(void);
static void dispAzOptions(void);
static void dispElOptions(void);
static void dispRngOptions(void);
static void dispTempSerialMessage(void);
static void dispSerialMessage(void);

/// LCD Display Functions
static void dispLCDTopMenu(int option);
static void dispLCDAzMenu(int option);
static void dispLCDElMenu(int option);
static void dispLCDRngMenu(int option);
static void dispLCDNum(int option);

//// Menus
struct menuStruct topMenu = {TOP_LEVEL, welcome, welcomeLcd,1, 6, 1, dispTopOptions, navigateTopMenu, dispLCDTopMenu, noFunction};
struct menuStruct AzMenu = {AZ_MENU, azMenu, azMenuLcd,1, 6, 1, dispAzOptions, navigateAzimuthMenu, dispLCDAzMenu, returnToTopMenu};
struct menuStruct ElMenu = {EL_MENU, elMenu, elMenuLcd,1, 6, 1, dispElOptions, navigateElevationMenu, dispLCDElMenu, returnToTopMenu};
struct menuStruct RangeMenu = {RANGE_MENU, rngMenu, rngMenuLcd,1, 6, 1, dispRngOptions, navigateRangeMenu, dispLCDRngMenu, returnToTopMenu};

/// Remote/Local Functions
struct menuStruct AzGoto = {AZ_GOTO, gotoAzAngle, gotoAzAngleLCD,MIN_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5,dispSerialMessage, setValue, dispLCDNum, returnToAzMenu};
struct menuStruct ElGoto = {EL_GOTO, gotoElAngle, gotoELAngleLCD,MIN_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5,dispSerialMessage, setValue, dispLCDNum, returnToElMenu};
struct menuStruct AzMin = {AZ_MIN, minAz1, minAzSetStr,MIN_ANGLE_INFIMUM, MIN_ANGLE_SUPREMUM, 5, dispSerialMessage, setValue, dispLCDNum, returnToAzMenu};
struct menuStruct AzMax = {AZ_MAX, maxAz1, maxAzSetStr,MAX_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5, dispSerialMessage, setValue, dispLCDNum, returnToAzMenu};
struct menuStruct ElMin = {EL_MIN, minEl1, minElSetStr,MIN_ANGLE_INFIMUM, MIN_ANGLE_SUPREMUM, 5, dispSerialMessage, setValue, dispLCDNum, returnToElMenu};
struct menuStruct ElMax = {EL_MAX, maxEl1, maxElSetStr,MAX_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5, dispSerialMessage, setValue, dispLCDNum, returnToElMenu};
struct menuStruct RngMin = {RANGE_MIN, minRngSerialStr, minRngSetStr, MIN_RANGE_INFIMUM, MIN_RANGE_SUPREMUM, 50, dispSerialMessage, setValue, dispLCDNum, returnToRngMenu};
struct menuStruct RngMax = {RANGE_MAX, maxRngSerialStr, maxRngSetStr, MAX_RANGE_INFIMUM, MAX_RANGE_SUPREMUM, 50, dispSerialMessage, setValue, dispLCDNum, returnToRngMenu};
struct menuStruct ShowTemp = {SHOW_TEMP, showTempLCDTitle, showTempLCDTitle, 0, 0, 0, dispTempSerialMessage, noFunctionNumeric, noFunctionNumeric, returnToTopMenu};
/*! Global variable with the current menu position */
struct menuStruct m_currentMenu;

/*! Global variable with the current user mode: Local, remote or factory */
static userState m_userMode;

// *****************************************************************************
// *********************** MENU STRUCTURE FUNCTIONS ****************************
// *****************************************************************************

/*! **********************************************************************
 * Function: sendROM(void)
 *
 * @brief
 *
 * Include: Local to Menusystem.c
 *
 * @description: Transmits the given string from ROM over serial
 *
 * @input The string to transmit
 *
 * Returns: None
 *************************************************************************/
static void sendROM(const rom char *romchar) {
    char temp[80] = {0};
    int j;

    // Convert the string from ROM to RAM
    strcpypgm2ram(temp, romchar);
    transmit(temp);
    for (j = 0; j < 8000; j++); //Some Arbitrary Delay
}

/*! **********************************************************************
 * Function: sendNewLine(char length)
 *
 * @brief
 *
 * Include: Local to Menusystem.c
 *
 * @description: Prints a number of new line (\r\n) charaters.
 *
 * @input The number of new lines to print
 *
 * Returns: None
 *************************************************************************/
static void sendNewLine(char length)
{
    char index;
    char temp[height + 2] = {0};        // This is two greater for the \r and end message characters
    int j;

    // Fills the buffer with \n characters
    for (index = 0; index<length; index++) {
        temp[index] = '\n';
    }
    // End with a line return
    temp[index] = '\r';
    transmit(temp);
    for (j = 0; j < 2000; j++);
}

/*!
 * Clears the Serial display
 */
/*! **********************************************************************
 * Function: clearScreen(void)
 *
 * @brief Clears the Serial Display
 *
 * Include: Local to Menusystem.c
 *
 * @description: Transmits the given string from ROM over serial
 *
 * @input The string to transmit
 *
 * Returns: None
 *************************************************************************/
static void clearScreen()
{
    char index;
    char temp[height + 2] = {0};        // This is two greater for the \r and end message characters
    int j;

    // Fills the buffer with \n characters
    for (index = 0; index<height; index++) {
        temp[index] = '\n';
    }
    // End with a line return
    temp[height] = '\r';
    transmit(temp);
    for (j = 0; j < 1000; j++);
}

static void filler(char length) {
    char index = 0;
    char temp[81] = {0};
    int j;
    for (; length > 0; length--) {
        temp[index] = '+';
        index++;
    }
    transmit(temp);
    for (j = 0; j < 3000; j++);
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
    m_userMode = REMOTE;
    configureSerial();
    configLCD();
    configUSER();
    setMenu(topMenu);
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
 * Returns: 1 if input has been received, 0 otherwise
 *************************************************************************/
char checkForSerialInput(void)
{
    return receiveCR() | receiveEsc(); //!Wait until the receive buffer is no longer empty
                                       //!Indicating that a command has been passed
}

/*! **********************************************************************
 * Function: parseNumeric(char *number)
 *
 * \brief parses user input string into a number
 *
 * Include:
 *
 * Description: Converts ASCII input to a number, and records an error for
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
static int parseNumeric(char *number)
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

    // Return the positive or negative number
    return multiplier * result;
}

/*!
 * Description: Displays a number out of range error
 */
static void errOutOfRange(int lowerBound, int upperBound)
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
static int getSerialNumericInput()
{
    char userget[80] = {0};
    if (receiveEsc())
    {
        popEsc();
        return ESC_PRESSED;
    }
    readString(userget);    //!Get the input string and store it in @userget
    return parseNumeric(userget);
}

/*!
 * Description: Returns the value of the potentiometer on the user
 *              interface, given a maximum and minimum value, and
 *              the interval between values (eg 10-100 in multiples
 *              of 10).
 */
static int getLocalPotResult(int min, int max, int interval)
{
    int adcResult = readDial((max - min)/interval);
    adcResult = min + interval*adcResult;
    return adcResult;
}

/*!
 * Description: Converts a number to a string
 * Can only print numbers under 8 digits
 */
static char* intToAscii(int num)
{
    char string[10] = {0};
    itoa(num, string);
    return string;
}

/*! **********************************************************************
 * Function: serviceMenu(void)
 *
 * \brief services any user interface with the menu
 *
 * Include:
 *
 * Description: Checks if the user has made any inputs to the system. If not
 *              the function simply returns. If they have then it services
 *              the inputs, displays the correct outputs and performs the
 *              specified actions
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void serviceMenu(void)
{
    char buttonInput;
    char string[50];
    int numericInpt;

    if (m_userMode == REMOTE || m_userMode == FACTORY)
    {
        if (checkForSerialInput())
        {
            // Handle serial input
            numericInpt = getSerialNumericInput();
        }
        else
        {
            return;
        }
    }
    else
    {
        if (userEmpty())
        {
            // Display the current value on the LCD
            // Get the Potentiometer result for the current menu
            numericInpt = getLocalPotResult(m_currentMenu.minVal, m_currentMenu.maxVal, m_currentMenu.increment);
            // Display string on LCD
            m_currentMenu.lcdDisplayFunction(numericInpt);
            return;
        }
        else
        {
            // Confirm the user's input
            buttonInput = userPop();
            if (buttonInput == CONFIRM_CHAR)
            {
                numericInpt = getLocalPotResult(m_currentMenu.minVal, m_currentMenu.maxVal, m_currentMenu.increment);
            }
            else
            {
                // Back was pressed
                numericInpt =  ESC_PRESSED;
            }
        }
    }

    /// If Esc or Back button pressed, return
    if (numericInpt == ESC_PRESSED)
    {
        m_currentMenu.returnToPrevious();
        return;
    }
    else
    {
        /// Otherwise Confirm the selection
        m_currentMenu.confirmFunction(numericInpt);
        return;
    }
}

/*!
 * Description: General funtion for menus which set values
 *              (Such as Set Max Range). This calls the
 *              appropriate function, and transmits user messages.
 */
static void setValue(int input)
{
    char string[20] = " set to \0";
    char stringLcd[20] = {0};
    Direction dir;

    // Sends a new line
    sendNewLine(1);

    // Handle inpropper input values
    if (input < m_currentMenu.minVal || input > m_currentMenu.maxVal)
    {
        errOutOfRange(m_currentMenu.minVal, m_currentMenu.maxVal);
        sendNewLine(1);
        return;
    }

    // Handle Different cases
    // @TODO handle current values
    // @TODO Integrate
    switch (m_currentMenu.menuNum)
    {
        case AZ_GOTO:
            dir.azimuth = input;
            dir.inclination = getDir().inclination;
            move(dir);
            sendROM(angleStr);
            break;
        case EL_GOTO:
            dir.azimuth = getDir().azimuth;
            dir.inclination = input;
            move(dir);
            sendROM(angleStr);
            break;
        case AZ_MIN:
            setMinAzimuthAngle((char) input);
            AzGoto.minVal = input;
            sendROM(angleStr);
            break;
        case AZ_MAX:
            setMaxAzimuthAngle((char) input);
            AzGoto.maxVal = input;
            sendROM(angleStr);
            break;
        case EL_MIN:
            setMinElevationAngle((char) input);
            ElGoto.minVal = input;
            sendROM(angleStr);
            break;
        case EL_MAX:
            setMaxElevationAngle((char) input);
            ElGoto.maxVal = input;
            sendROM(angleStr);
            break;
    }

    // Transmit the final part of the sentence
    transmit(string);
    transmit(intToAscii(input));
    sendNewLine(1);

    lcdWriteString(strcpypgm2ram(stringLcd, "OK!"), 2);
}

static void setMenu(struct menuStruct menu)
{
    char stringLcd[20] = {0};
    m_currentMenu = menu;
    if (m_userMode == REMOTE || m_userMode == FACTORY) displayMenuSerial();
    lcdWriteString(strcpypgm2ram(stringLcd, m_currentMenu.lcdTitleMessage), 1);
}

static void noFunctionNumeric(int input)
{
    return;
}

static void noFunction(void)
{
    return;
}

static void returnToTopMenu(void)
{
    setMenu(topMenu);
}
static void returnToAzMenu(void)
{
    setMenu(AzMenu);
}
static void returnToElMenu(void)
{
    setMenu(ElMenu);
}
static void returnToRngMenu(void)
{
    setMenu(RangeMenu);
}

// *****************************************************************************
// *************************** NAVIGATE MENUS *********************************
// *****************************************************************************

static void navigateTopMenu(int inputResult) {
    switch (inputResult) {
        case 1:
            //auto();;
            break;
        case 2:
            // Go to the Azimuth menu
            setMenu(AzMenu);
            break;
        case 3:
            // Go to the Elevation Menu
            setMenu(ElMenu);
            break;
        case 4:
            // Go to Range Menu
            setMenu(RangeMenu);;
            break;
//        case 5:
//            // Show Temperature
//            m_currentMenu = SHOW_TEMP;
//            break;
//        case 6:
//            // If Factory mode is on, calibrate Temperature
//            if (m_userMode == FACTORY) {
//                m_currentMenu = CALIBRATE_TEMP;
//                break;
//            } else {
//                // Switch user mode!
//                if (m_userMode == REMOTE) {
//                    m_userMode = LOCAL;
//                } else if (m_userMode == LOCAL) {
//                    m_userMode = REMOTE;
//                }
//                break;
//            }
        default:
            errOutOfRange(1, 5);
            break;
    }
}

static void navigateAzimuthMenu(int inputResult) {
    switch (inputResult) {
        case 1:
            // Go to elevation angle
            setMenu(AzGoto);
            break;
        case 2:
            // Set elevation minimum
            setMenu(AzMin);
            break;
        case 3:
            // Set elevation maximum
            setMenu(AzMax);
            break;
        case 4:
            if (m_userMode == FACTORY) {
                // Calibrate the elevation servo
            } else {
                // Go back one level
                m_currentMenu.returnToPrevious();
            }
            break;
        case 5:
            if (m_userMode == FACTORY) {
                // Go back!
                m_currentMenu.returnToPrevious();
                break;
            }
            // If not in factory mode, this is an error;
        default:
            errOutOfRange(1, 4);
            break;
    }
}

static void navigateRangeMenu(int inputResult)
{
    switch (inputResult) {
        case 1:
            // Set the minimum range
            setMenu(RngMin);
            break;
        case 2:
            // Set the maximum range
            setMenu(RngMax);
            break;
        case 3:
            if (m_userMode == FACTORY) {
                // View the raw range data
            } else {
                // Go back one level
                m_currentMenu.returnToPrevious();
            }
            break;
        case 4:
            if (m_userMode == FACTORY) {
                // Set the ultrasound sample rate
            } else {
                errOutOfRange(1, 3); // Display an error
            }
            break;
        case 5:
            if (m_userMode == FACTORY) {
                // Set the number of estimations per sample
            } else {
                errOutOfRange(1, 3); // Display an error
            }
            break;
        case 6:
            if (m_userMode == FACTORY) {
                // Set the IR sample rate
            } else {
                errOutOfRange(1, 3); // Display an error
            }
            break;
        case 7:
            if (m_userMode == FACTORY) {
                // Set the number of estimations per sample
            } else {
                errOutOfRange(1, 3); // Display an error
            }
            break;
        default:
            if (m_userMode == FACTORY) {
                errOutOfRange(1, 7);
            } else {
                errOutOfRange(1, 3); // Display an error
            }
            break;
    }
}

static void navigateElevationMenu(int inputResult)
{
        switch (inputResult) {
        case 1:
            // Go to elevation angle
            setMenu(ElGoto);
            break;
        case 2:
            // Set elevation minimum
            setMenu(ElMin);
            break;
        case 3:
            // Set elevation maximum
            setMenu(ElMax);
            break;
        case 4:
            if (m_userMode == FACTORY) {
                // Calibrate the elevation servo
            } else {
                m_currentMenu.returnToPrevious();
                // Go back one level
            }
            break;
        case 5:
            if (m_userMode == FACTORY) {
                // Calibrate the elevation servo
                break;
            }
            // If not in factory mode, this is an error;
        default:
            if (m_userMode == FACTORY) errOutOfRange(1, 5);
            else errOutOfRange(1, 4);
            break;
    }
}

// *****************************************************************************
// *************************** SERIAL DISPLAY **********************************
// *****************************************************************************

/*!
 * Display the current menu Title and other information over serial
 */
static void displayMenuSerial()
{
    int j;
    sendNewLine(7);
    filler(width);
    sendNewLine(1);
    transChar('\t');
    sendROM(m_currentMenu.lcdTitleMessage);
    sendNewLine(1);
    filler(width);
    sendNewLine(2);
    m_currentMenu.serialDisplayFunction();
    sendNewLine(2);
    filler(width);
    for (j=0;j<1000;j++);
    sendNewLine(1);
}

/*!
 * Display the user options for the top level home menu
 */
static void dispTopOptions(void) {

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

    sendROM(CHOOSE);
}

/*!
 * Display the user options for the Azimuth menu
 */
static void dispAzOptions()
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
    sendROM(CHOOSE);
}

/*!
 * Display the user options for the Azimuth menu
 */
static void dispElOptions()
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
    sendROM(CHOOSE);
}

/*!
 * Display the user options for the Azimuth menu
 */
static void dispRngOptions()
{
    sendROM(rngOption1);
    sendROM(rngOption2);
    if (m_userMode == FACTORY)
    {
        sendROM(rngOption3);
        sendROM(rngOption4);
        sendROM(rngOption5);
        sendROM(rngOption6);
        sendROM(rngOption7);
        sendROM(menuPrefix8);
        sendROM(goUp);
    }
    else
    {
        sendROM(menuPrefix3);
        sendROM(goUp);
    }
    sendROM(CHOOSE);
}

/*!
 * Display the Show Temperature serial message
 */
static void dispTempSerialMessage(void)
{
    char temp = readTemp();
    sendROM(showTemp1);
    transmit(intToAscii((int) temp));
    sendROM(showTemp2);
}

/*!
 * Display the menu serial message
 */
static void dispSerialMessage(void)
{
    sendROM(m_currentMenu.serialMessage);
}

// *****************************************************************************
// ****************************** LCD FUNCTIONS **********************************
// *****************************************************************************

/*!
 * Displays the current potentiometer reading on the LCD based on the
 * menu options contextualised by the Home menu.
 */
static void dispLCDTopMenu(int option)
{
    char string[20] = {0};
    switch(option)
    {
        case 1:
            //Automatic Tracking;
            break;
        case 2:
            // Azimuth Menu
            strcpypgm2ram(string, AzMenu.lcdTitleMessage);
            break;
        case 3:
            // Elevation Menu
            strcpypgm2ram(string, ElMenu.lcdTitleMessage);
            break;
        case 4:
            // Range Menu
            strcpypgm2ram(string, RangeMenu.lcdTitleMessage);
            break;
        case 5:
            // Show Temp
            strcpypgm2ram(string, ShowTemp.lcdTitleMessage);
            break;
        case 6:
            // Switch to Remote
            strcpypgm2ram(string, topOptionRemoteLCD);
            break;
        default:
            strcpypgm2ram(string, "ERROR");
    }
    lcdWriteString(string, 2);
}
/*!
 * Displays the current potentiometer reading on the LCD based on the
 * menu options contextualised by the Azimuth menu.
 */
static void dispLCDAzMenu(int option)
{
    char string[20] = {0};
    switch(option)
    {
        case 1:
            // Go to Azimuth
            strcpypgm2ram(string, AzGoto.lcdTitleMessage);
            break;
        case 2:
            // Set Min Azimuth
            strcpypgm2ram(string, AzMin.lcdTitleMessage);
            break;
        case 3:
            // Set Max Azimuth
            strcpypgm2ram(string, AzMax.lcdTitleMessage);
            break;
        default:
            strcpypgm2ram(string, "ERROR");
    }
    lcdWriteString(string, 2);
}
/*!
 * Displays the current potentiometer reading on the LCD based on the
 * menu options contextualised by the Elevation menu.
 */
static void dispLCDElMenu(int option)
{
    char string[20] = {0};
    switch(option)
    {
        case 1:
            // Go to Elevation
            strcpypgm2ram(string,  ElGoto.lcdTitleMessage);
            break;
        case 2:
            // Set Min Elevation
            strcpypgm2ram(string, ElMin.lcdTitleMessage);
            break;
        case 3:
            // Set Max Elevation
            strcpypgm2ram(string, ElMax.lcdTitleMessage);
            break;
        default:
            strcpypgm2ram(string, "ERROR");
    }
    lcdWriteString(string, 2);
}

/*!
 * Displays the current potentiometer reading on the LCD based on the
 * menu options contextualised by the Range menu.
 */
static void dispLCDRngMenu(int option)
{
    char string[20] = {0};
    switch(option)
    {
        case 1:
            // Set Min Range
            strcpypgm2ram(string, RngMin.lcdTitleMessage);
            break;
        case 3:
            // Set Max Range
            strcpypgm2ram(string, RngMax.lcdTitleMessage);
            break;
        default:
            strcpypgm2ram(string, "ERROR");
    }
    lcdWriteString(string, 2);
}

/*!
 * Description: Displays the current converted value from the potentiometer
 *              onto the LCD display
 *
 * Arguments: The integer converted from the ADC
 */
static void dispLCDNum(int option)
{
    char *string = intToAscii(option);
    lcdWriteString(string, 2);
}



