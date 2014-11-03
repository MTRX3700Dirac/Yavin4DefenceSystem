/*!******************************************************************************
 * File:   Menusystem.c
 * Author: Bas
 *
 * Description:
 * The codebase for the user interface and menus for both serial and
 * local interaction. This is a tiered menu system, with different
 * menus and setting being accessible from different sub menus. The
 * menu system is also designed to work as a background task, to be
 * serviced as the main program loops through. This was originally designed
 * so that tracking and menu navigation could happen at the same time.
 *
 * Duties:
 * 		- Set up the menus for interaction
 * 		- Service the menu for local or serial input
 *		- Parse the user input from serial
 *		- Navigate between the menus
 *		- Print serial messages and LCD messages to the user
 *		- Call the appropriate function
 *
 * Functions:
 *      Public Interfaces:
 * 		void initialiseMenu(systemState *state);
 *		char checkForSerialInput(void);
 *		void menuISR(void);
 * 		void serviceMenu(void);
 * 		void dispTrack(TrackingData target);
 * 		void dispSearching(void);
 * 		void dispRawRange(void);
 *
 *      Local Functions:
 *              Serial Display Functions
 *                      void sendROM(const rom char *romchar);
 *                      void clearScreen(void);
 *                      void sendNewLine(char length);
 *                      void filler(char length);
 *                       void errOutOfRange(int lowerBound, int upperBound);
 *                       char* intToAscii(int num);
 *                      void autodisp(void);
 *                      
 *              Input Parsing
 *                      int parseNumeric(char *input);
 *                      int getSerialNumericInput(void);
 *                      void configureTimer0(void);
 *                      int getLocalInputMenu(int maxStates, int (*function)(int));
 *
 *              Confirm User Input Functions
 *                       void setValue(int input);
 *                       void setMenu(struct menuStruct menu);
 *                      void navigateTopMenu(int inputResult);
 *                      void noFunctionNumeric(int input);
 *                      void setCalibrateRange(int num);
 * 
 *              Return Functions
 *                      void noFunction(void);
 *                      void returnToTopMenu(void);
 *                      void exitFromTracking(void);
 *                      void returnToAzMenu(void);
 *                      void returnToElMenu(void);
 *                      void returnToRngMenu(void);
 * 
 *              Navigation between sub menus Functions
 *                      void navigateTopMenu(int inputResult);
 *                      void navigateAzimuthMenu(int inputResult);
 *                      void navigateElevationMenu(int inputResult);
 *                      void navigateRangeMenu(int inputResult);
 * 
 *              Display Serial functions
 *                      void dispTopOptions(void);
 *                      void displayMenuSerial();
 *                      void dispTopOptions(void);
 *                      void dispAzOptions(void);
 *                      void dispElOptions(void);
 *                      void dispRngOptions(void);
 *                      void dispTempSerialMessage(void);
 *                      void dispSerialMessage(void);
 *                      void dispSetValueMessage(void);
 * 
 *              LCD Display Functions
 *                      void dispLCDTopMenu(int option);
 *                      void dispLCDAzMenu(int option);
 *                      void dispLCDElMenu(int option);
 *                      void dispLCDRngMenu(int option);
 *                      void dispLCDNum(int option);
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
#include "MenuDefs.h"

/// Serial Display Functions
static void sendROM(const rom char *romchar);
static void clearScreen(void);
static void sendNewLine(char length);
static void filler(char length);
static void errOutOfRange(int lowerBound, int upperBound);
static char* intToAscii(int num);
static void autodisp(void);

/// Input Parsing
int parseNumeric(char *input);
static int getSerialNumericInput(void);
static void configureTimer0(void);
static int getLocalInputMenu(int maxStates, int (*function)(int));

/// Confirm User Input Functions
static void setValue(int input);
static void setMenu(struct menuStruct menu);
static void navigateTopMenu(int inputResult);
static void noFunctionNumeric(int input);
static void setCalibrateRange(int num);

// Return Functions
static void noFunction(void);
static void returnToTopMenu(void);
static void exitFromTracking(void);
static void returnToAzMenu(void);
static void returnToElMenu(void);
static void returnToRngMenu(void);

/// Navigation between sub menus Functions
static void navigateTopMenu(int inputResult);
static void navigateAzimuthMenu(int inputResult);
static void navigateElevationMenu(int inputResult);
static void navigateRangeMenu(int inputResult);

/// Display Serial functions
static void dispTopOptions(void);
static void displayMenuSerial();
static void dispTopOptions(void);
static void dispAzOptions(void);
static void dispElOptions(void);
static void dispRngOptions(void);
static void dispTempSerialMessage(void);
static void dispSerialMessage(void);
static void dispSetValueMessage(void);

/// LCD Display Functions
static void dispLCDTopMenu(int option);
static void dispLCDAzMenu(int option);
static void dispLCDElMenu(int option);
static void dispLCDRngMenu(int option);
static void dispLCDNum(int option);

//// Menus
struct menuStruct topMenu = {TOP_LEVEL, title, welcomeLcd,1, 6, 1, dispTopOptions, navigateTopMenu, /*dispLCDTopMenu*/0, noFunction};
struct menuStruct AzMenu = {AZ_MENU, azMenu, azMenuLcd,1, 6, 1, dispAzOptions, navigateAzimuthMenu, /*dispLCDAzMenu*/0, returnToTopMenu};
struct menuStruct ElMenu = {EL_MENU, elMenu, elMenuLcd,1, 6, 1, dispElOptions, navigateElevationMenu, /*dispLCDElMenu*/0, returnToTopMenu};
struct menuStruct RangeMenu = {RANGE_MENU, rngMenu, rngMenuLcd,1, 6, 1, dispRngOptions, navigateRangeMenu,/*dispLCDRngMenu*/0, returnToTopMenu};

/// Remote/Local Functions
struct menuStruct AzGoto = {AZ_GOTO, gotoAzAngle, gotoAzAngleLCD,MIN_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5,dispSetValueMessage, setValue, /*dispLCDNum*/noFunctionNumeric, returnToAzMenu};
struct menuStruct ElGoto = {EL_GOTO, gotoElAngle, gotoELAngleLCD,MIN_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5,dispSetValueMessage, setValue, /*dispLCDNum*/noFunctionNumeric, returnToElMenu};
struct menuStruct AzMin = {AZ_MIN, minAz1, minAzSetStr,MIN_ANGLE_INFIMUM, MIN_ANGLE_SUPREMUM, 5, dispSetValueMessage, setValue, /*dispLCDNum*/noFunctionNumeric, returnToAzMenu};
struct menuStruct AzMax = {AZ_MAX, maxAz1, maxAzSetStr,MAX_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5, dispSetValueMessage, setValue, /*dispLCDNum*/noFunctionNumeric, returnToAzMenu};
struct menuStruct ElMin = {EL_MIN, minEl1, minElSetStr,MIN_ANGLE_INFIMUM, MIN_ANGLE_SUPREMUM, 5, dispSetValueMessage, setValue, /*dispLCDNum*/noFunctionNumeric, returnToElMenu};
struct menuStruct ElMax = {EL_MAX, maxEl1, maxElSetStr,MAX_ANGLE_INFIMUM, MAX_ANGLE_SUPREMUM, 5, dispSetValueMessage, setValue, /*dispLCDNum*/noFunctionNumeric, returnToElMenu};
struct menuStruct RngMin = {RANGE_MIN, minRngSerialStr, minRngSetStr, MIN_RANGE_INFIMUM, MIN_RANGE_SUPREMUM, 50, dispSetValueMessage, setValue, /*dispLCDNum*/noFunctionNumeric, returnToRngMenu};
struct menuStruct RngMax = {RANGE_MAX, maxRngSerialStr, maxRngSetStr, MAX_RANGE_INFIMUM, MAX_RANGE_SUPREMUM, 50, dispSetValueMessage, setValue, /*dispLCDNum*/noFunctionNumeric, returnToRngMenu};
struct menuStruct ShowTemp = {SHOW_TEMP, showTempLCDTitle, showTempLCDTitle, 0, 0, 0, dispTempSerialMessage, noFunctionNumeric, noFunctionNumeric, returnToTopMenu};
struct menuStruct Tracking = {TRACKING, autoSerialMessage, autoLcdTitle, 0, 0, 0, dispSerialMessage, noFunctionNumeric, noFunctionNumeric, exitFromTracking};
struct menuStruct RawRange;
struct menuStruct NumSamples;
struct menuStruct UsSampleRate;
struct menuStruct calibrateRangeMenu;

/*! Global variable with the current menu position */
struct menuStruct m_currentMenu;

/*! Global variable with the current user mode: Local, remote or factory */
static userState m_userMode;

/*! Global variable with the current tracking state, if the tracker is searching or tracking or neither*/
static systemState *m_trackingState;

// *****************************************************************************
// *********************** MENU STRUCTURE FUNCTIONS ****************************
// *****************************************************************************

/*! **********************************************************************
 * Function: sendROM(void)
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
    for (j = 0; j < 8000; j++); //Some Arbitrary Delay to make sure transmission is not interrupted
}

/*! **********************************************************************
 * Function: sendNewLine(char length)
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
    for (j = 0; j < 2000; j++);     // wait
}

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
    int j;
    char clearScreen[] = CLEAR_SCREEN_STRING;    // Clears the screen and writes from the top
    transmit(clearScreen);

    for (j = 0; j < 1000; j++);                 // Wait
}

/*! **********************************************************************
 * Function: filler(char length)
 *
 * Include: Local to Menusystem.c
 *
 * @description: Transmits a line of filler characters to frame the menu
 *
 * @input The number of characters to transmit
 *
 * Returns: None
 *************************************************************************/
static void filler(char length) {
    char index = 0;
    char temp[81] = {0};
    int j;

    // Add length amount of filler chars to an array
    for (; length > 0; length--) {
        temp[index] = '+';
        index++;
    }

    // Transmit the buffer and wait.
    transmit(temp);
    for (j = 0; j < 3000; j++);
}

/*! **********************************************************************
 * Function: initialiseMenu(void)
 *
 * \brief Initialises the menu system
 *
 * @Include: Menusystem.h
 *
 * @Description: Initialises the menu system so that it is fully operational
 *
 * @Arguments: None
 *
 * @Returns: None
 *************************************************************************/
void initialiseMenu(systemState *state) {
    m_userMode = REMOTE;
    configureSerial();
    //@TODO WHILE LOCAL UNPLUGGED configLCD();
    configUSER();
    setMenu(topMenu);
    m_trackingState = state;

    // Running out of RAM, so intiialise some menus here to save on iData.
    // Initialise the Raw Range menu
    RawRange;
    RawRange.confirmFunction = noFunctionNumeric;
            RawRange.menuID = RANGE_RAW;
    RawRange.serialMessage = rawRangeStr;
    RawRange.lcdTitleMessage = rawRangeTitle;
    RawRange.minVal = 0;
    RawRange.maxVal = 0;
    RawRange.increment = 0;
    RawRange.serialDisplayFunction = dispSerialMessage;
    RawRange.returnToPrevious = returnToRngMenu;
    RawRange.lcdDisplayFunction = noFunctionNumeric;

    // Initialise the calibrate range menu
    calibrateRangeMenu.confirmFunction = setCalibrateRange;
    calibrateRangeMenu.menuID = CALIBRATE_RANGE;
    calibrateRangeMenu.serialMessage = calRangeStr;
    calibrateRangeMenu.lcdTitleMessage = calRangeTitle;
    calibrateRangeMenu.minVal = 0;
    calibrateRangeMenu.maxVal = 0;
    calibrateRangeMenu.increment = 0;
    calibrateRangeMenu.serialDisplayFunction = dispSerialMessage;
    calibrateRangeMenu.returnToPrevious = returnToRngMenu;
    calibrateRangeMenu.lcdDisplayFunction = noFunctionNumeric;

    // Initialise the menu which sets the number of US samples used per estimate
    NumSamples.confirmFunction = setValue;
    NumSamples.menuID = US_SAMPLE_AVG;
    NumSamples.serialMessage = numSamplesStr;
    NumSamples.lcdTitleMessage = numSampleTitle;
    NumSamples.minVal = 1;
    NumSamples.maxVal = 3;
    NumSamples.increment = 1;
    NumSamples.serialDisplayFunction = dispSetValueMessage;
    NumSamples.returnToPrevious = returnToRngMenu;
    NumSamples.lcdDisplayFunction = noFunctionNumeric;

    // Initialise the menu which sets the US sample rate
    UsSampleRate.confirmFunction = setValue;
    UsSampleRate.menuID = US_SAMPLE_RATE;
    UsSampleRate.serialMessage = usSampleRateStr;
    UsSampleRate.lcdTitleMessage = usSampleRateTitle;
    UsSampleRate.minVal = 1;
    UsSampleRate.maxVal = 40;
    UsSampleRate.increment = 1;
    UsSampleRate.serialDisplayFunction = dispSetValueMessage;
    UsSampleRate.returnToPrevious = returnToRngMenu;
    UsSampleRate.lcdDisplayFunction = noFunctionNumeric;

}

/*! **********************************************************************
 * Function: waitForInput(void)
 *
 * @Include: Serial.c
 *
 * @Description: Checks the serial/local buffers for inputs
 *
 * @Arguments: None
 *
 * @Returns: 1 if input has been received, 0 otherwise
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
 * @Include:
 *
 * @Description: Converts ASCII input to a number, and records an error for
 *              non-numeric input, or if the number is larger than 4 digits.
 *              No number used by the user in this program will be larger
 *              than 6 digits.
 *
 * @Arguments: The ASCII string to decode
 *
 * @Returns: The integer result of the string
 *          ERR_NOT_NUMERIC for any non-numeric input
 *          ERR_NUM_OUT_OF_RANGE for 0 digits or 6+ digits
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
        if (digits >= 6) return ERR_NUM_OUT_OF_RANGE;
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

/*! **********************************************************************
 * Function: errOutOfRange(int lowerBound, int upperBound)
 *
 * \brief Displays an error message that the number was out of range
 *
 * Include: Local to Menusystem.c
 *
 * @description: Transmits an error message saying that the user has given a
 *               value which is out of the appropriate range for the menu
 *               in which they are currently in. It also informs the user the
 *               bounds for which values should be entered
 *
 * @input lowerBound - The minimal value that the user can correctly enter
 *        upperBound - the maximum value that the user can correctly enter
 *
 * Returns: None
 *************************************************************************/
static void errOutOfRange(int lowerBound, int upperBound)
{
    sendROM(inputNumRangeStr);
    transmit(intToAscii(lowerBound));
    sendROM(and);
    transmit(intToAscii(upperBound));
    sendNewLine(1);
}

/*! **********************************************************************
 * Function: getSerialNumericInput
 *
 * Include: Local to MenuSystem.c
 *
 * Description: Checks the user input for an escape character, and handles
 *              the reception of different serial inputs by either indicating
 *              that esc was pressed, or parsing numeric input and returning
 *              its value.
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
 * Function:    getLocalPotResult
 *
 * @Include:    UserInterface.h
 *
 * @Description: Returns the value of the potentiometer on the user
 *              interface, given a maximum and minimum value, and
 *              the interval between values (eg 10-100 in multiples
 *              of 10).
 *
 * @Arguments:  int min - The minimum value the potentiometer should indicate
 *              int max - the maximum valye the potentiometer should indicate
 *              int interval - The number between successive values  (eg 10 = 10, 20, 30 etc)
 *
 * @Returns:    The resulting value the potentiometer returns given the system bounds
 */
// Commented out as it is unused with the local interface disconnected
//static int getLocalPotResult(int min, int max, int interval)
//{
//    int adcResult = readDial((max - min)/interval);
//    adcResult = min + interval*adcResult;
//    return adcResult;
//}

/*!
 * Function:    intToAscii
 *
 * @Include:    Local to MenuSystem.c
 *
 * @Description: Short wrapper method to convert an int to a string representation
 *               of that number in ASCII
 *
 * @Arguments:  int num - The number to convert
 *
 * @Returns:    A pointer to the resulting
 */
static char* intToAscii(int num)
{
    char string[10] = {0};
    sprintf(string, "%d", num);
    return string;
}

/*! **********************************************************************
 * Function: serviceMenu(void)
 *
 * \brief services any user interface with the menu
 *
 * Include:Local to Menu/system.c
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

    // Go to factory mode if the key is turned
    if (FACTORY_SWITCH == 1 && m_userMode == REMOTE)
    {
        m_userMode = FACTORY;
        setMenu(m_currentMenu);
    }
    // Rest back to serial mode if the key is removed
    else if(FACTORY_SWITCH == 0 && m_userMode == FACTORY)
    {
        m_userMode = REMOTE;
        setMenu(topMenu);
    }

    // Service serial
    if (m_userMode == REMOTE || m_userMode == FACTORY)
    {
        // Check for serial input
        if (checkForSerialInput())
        {
            // Handle serial input
            numericInpt = getSerialNumericInput();
            sendNewLine(1);
            sendROM("DEBUG: Value entered = ");     //Debugging statement due to serial issue.
            transmit(intToAscii(numericInpt));
            sendNewLine(1);
            clearReceive();
        }
        else
        {
            return;
        }
    }
/// COMMENTED OUT DUE TO DISCONNECTION OF LOCAL INTERFACE
//    else
//    {
//        if (userEmpty())
//        {
//            // Display the current value on the LCD
//            // Get the Potentiometer result for the current menu
//            numericInpt = getLocalPotResult(m_currentMenu.minVal, m_currentMenu.maxVal, m_currentMenu.increment);
//            // Display string on LCD
//            m_currentMenu.lcdDisplayFunction(numericInpt);
//            return;
//        }
//        else
//        {
//            // Confirm the user's input
//            buttonInput = userPop();
//            if (buttonInput == CONFIRM_CHAR)
//            {
//                numericInpt = getLocalPotResult(m_currentMenu.minVal, m_currentMenu.maxVal, m_currentMenu.increment);
//            }
//            else
//            {
//                // Back was pressed
//                numericInpt =  ESC_PRESSED;
//            }
//        }
//    }

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


/*! **********************************************************************
 * Function: setCalibrateRange
 *
 * Include:Range.c
 *
 * Description: Displays the message for Calibrating the rangefinders, and
 *              calls the appropriate function.
 *
 * Arguments: int num - unused, but needed to fit the function pointer prototype
 *
 * Returns: None
 *************************************************************************/
static void setCalibrateRange(int num)
{
    calibrateRange(500);
    sendROM(tab);
    sendROM(calRangeConfirm);
    sendNewLine(1);
}

/*!
 * Function: setValue
 *
 * @Include Range.c, PanTilt.c
 *
 * @Description: General funtion for menus which set values
 *              (Such as Set Max Range). This calls the
 *              appropriate function, and transmits user messages.
 *
 * @Arguments: int input - The value the user has given
 *
 * @Returns:    N/A
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

    // Handle Different cases, call functions and print messages
    switch (m_currentMenu.menuID)
    {
        case AZ_GOTO:
            dir.azimuth = input;
            dir.elevation = getDir().elevation;
            move(dir);
            sendROM(angleStr);
            break;
        case EL_GOTO:
            dir.azimuth = getDir().azimuth;
            dir.elevation = input;
            move(dir);
            sendROM(angleStr);
            break;
        case AZ_MIN:
            setMinAzimuthAngle((char) input);
            AzGoto.minVal = input;              // Make sure to update the new min/max values
            sendROM(angleStr);
            break;
        case AZ_MAX:
            setMaxAzimuthAngle((char) input);
            AzGoto.maxVal = input;              // Make sure to update the new min/max values
            sendROM(angleStr);
            break;
        case EL_MIN:
            setMinElevationAngle((char) input);
            ElGoto.minVal = input;              // Make sure to update the new min/max values
            sendROM(angleStr);
            break;
        case EL_MAX:
            setMaxElevationAngle((char) input);
            ElGoto.maxVal = input;              // Make sure to update the new min/max values
            sendROM(angleStr);
            break;
        case RANGE_MIN:
            setMinRange(input);
            sendROM(mmStr);
            break;
        case RANGE_MAX:
            setMaxRange(input);
            sendROM(mmStr);
            break;
        case US_SAMPLE_RATE:
            setUsSampleRate(input);
            sendROM(sampleRate);
            break;
        case US_SAMPLE_AVG:
            setNumSamples(input);
            sendROM(numPerSample);
            break;
    }

    // Transmit the final part of the sentence
    transmit(string);
    transmit(intToAscii(input));
    sendNewLine(1);

    // COMMENTED OUT DUE TO DISCONNECTION OF LOCAL INTERFACE
    //lcdWriteString(strcpypgm2ram(stringLcd, "OK!"), 2);
}

/*!
 * Function: setMenu
 *
 * @Include Local to MenuSystem.c
 *
 * @Description: General funtion for navigating between menus. This changes
 *               the current menu, and displays the heading message for the
 *               new menu.
 *
 * @Arguments: menuStruct menu - The new menu to go to
 *
 * @Returns:    N/A
 */
static void setMenu(struct menuStruct menu)
{
    char stringLcd[20] = {0};
    m_currentMenu = menu;
    if (m_userMode == REMOTE || m_userMode == FACTORY) displayMenuSerial();
    // COMMENTED OUT DUE TO DISCONNECT OF LOCAL INTERFACT
    //lcdWriteString(strcpypgm2ram(stringLcd, m_currentMenu.lcdTitleMessage), 1);
}

/*!
 * Function: noFunctionNumeric
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Does nothing, used for when nothing happens when the user
 *               enters a number.
 *
 * @Arguments: int input - unused.
 *
 * @Returns:    N/A
 */
static void noFunctionNumeric(int input)
{
    return;
}

/*!
 * Function: noFunction
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Does nothing, used for testing and for the highest level menu.
 *
 * @Arguments: N/A
 *
 * @Returns:    N/A
 */
static void noFunction(void)
{
    return;
}

/*!
 * Function: returnToTopMenu
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Returns to the top level of the menu system and prints the heading
 *
 * @Arguments: N/A
 *
 * @Returns:    N/A
 */
static void returnToTopMenu(void)
{
    setMenu(topMenu);
}

/*!
 * Function: exitFromTracking
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Returns to the top level menu, and stops the system from trying to
 *               search or track the object.
 *
 * @Arguments: N/A
 *
 * @Returns:    N/A
 */
static void exitFromTracking(void)
{
    m_trackingState->previous = m_trackingState->current;
    m_trackingState->current = MENU;
    setMenu(topMenu);
}

/*!
 * Function: returnToAzMenu
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Returns the user to the Azimuth menu
 *
 * @Arguments: N/A
 *
 * @Returns:    N/A
 */
static void returnToAzMenu(void)
{
    setMenu(AzMenu);
}

/*!
 * Function: returnToElMenu
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Returns the user to the Elevation menu
 *
 * @Arguments: N/A
 *
 * @Returns:    N/A
 */
static void returnToElMenu(void)
{
    setMenu(ElMenu);
}

/*!
 * Function: returnToRngMenu
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Returns the user to the Range menu
 *
 * @Arguments: N/A
 *
 * @Returns:    N/A
 */
static void returnToRngMenu(void)
{
    setMenu(RangeMenu);
}

// *****************************************************************************
// *************************** NAVIGATE MENUS *********************************
// *****************************************************************************

/*!
 * Function: navigateTopMenu
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Once a user has given an input, handle the appropriate responce
 *               in the top level menu by navigating to the correct submenu.
 *
 * @Arguments: int inputResult - The value that the user has entered.
 *
 * @Returns:    N/A
 */
static void navigateTopMenu(int inputResult) {
    switch (inputResult) {
        case 1:
            //auto();
            setMenu(Tracking);
            if (m_trackingState->current = MENU)
            {
                m_trackingState->previous = m_trackingState->current;
                m_trackingState->current = SRCH;
            }
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
            setMenu(RangeMenu);
            break;
        case 5:
            // Show Temperature
            setMenu(ShowTemp);
            break;
        case 6:
            // If Factory mode is on, calibrate Temperature
            if (m_userMode == FACTORY) {
                //setMenu(Calibrate);
                break;
            } 
            else
            {
                // COMMENTED OUT DUE TO DISCONNECTION OF LOCAL INTERFACE
                // Switch user mode!
//                if (m_userMode == REMOTE) {
//                    m_userMode = LOCAL;
//                } else if (m_userMode == LOCAL) {
//                    m_userMode = REMOTE;
//                }
//                setMenu(topMenu);
                break;
            }
        default:
            errOutOfRange(1, 5);
            break;
    }
}

/*!
 * Function: navigateAzimuthMenu
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Once a user has given an input, handle the appropriate responce
 *               in the Azimuth menu by navigating to the correct function menu.
 *
 * @Arguments: int inputResult - The value that the user has entered.
 *
 * @Returns:    N/A
 */
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

/*!
 * Function: navigateRangeMenu
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Once a user has given an input, handle the appropriate responce
 *               in the Range menu by navigating to the correct function menu.
 *
 * @Arguments: int inputResult - The value that the user has entered.
 *
 * @Returns:    N/A
 */
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
                setMenu(RawRange);
                m_trackingState->previous = m_trackingState->current;
                m_trackingState->current = RAW_RANGE_STATE;
            } else {
                // Go back one level
                m_currentMenu.returnToPrevious();
            }
            break;
        case 4:
            if (m_userMode == FACTORY) {
                // Set the ultrasound sample rate
                setMenu(UsSampleRate);
            } else {
                errOutOfRange(1, 3); // Display an error
            }
            break;
        case 5:
            if (m_userMode == FACTORY) {
                // Set the number of US estimations per sample
                setMenu(NumSamples);
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
                // Calibrate Range
                setMenu(calibrateRangeMenu);
            } else {
                errOutOfRange(1, 3); // Display an error
            }
            break;
        case 8:
            if (m_userMode == FACTORY) {
                m_currentMenu.returnToPrevious();
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

/*!
 * Function: navigateElevationMenu
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Once a user has given an input, handle the appropriate responce
 *               in the Elevation menu by navigating to the correct function menu.
 *
 * @Arguments: int inputResult - The value that the user has entered.
 *
 * @Returns:    N/A
 */
static void navigateElevationMenu(int inputResult)
{
        switch (inputResult) {
        case 1:
            // Go to elevation angle
            setMenu(ElGoto);
            break;
        case 2:
            // Set elevation ,minimum
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
v * Function: displayMenuSerial
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Generic method for displaying the current menu Title and border
 *               over serial. It also calls the current menu's display Serial
 *               function for other messages which need to be printed
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
static void displayMenuSerial()
{
    int j;

    // Clear screen and print border
    sendNewLine(1);
    clearScreen();
    filler(width);
    sendNewLine(1);

    // Print menu title
    transChar('\t');
    sendROM(m_currentMenu.lcdTitleMessage);
    sendNewLine(1);
    filler(width);

    // Print this function's Serial message
    sendNewLine(2);
    m_currentMenu.serialDisplayFunction();

    // Pront final border
    sendNewLine(2);
    filler(width);
    for (j=0;j<1000;j++);
    sendNewLine(1);
}

/*!
 * Function: dispTopOptions
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Displays the strings for the different options the user can
 *               choose whilst in the top level menu. It also accounts for
 *               Factory mode by printing extra messages the user can choose.
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
static void dispTopOptions(void) {

    // Print the Remote level options
    sendROM("\t");
    sendROM(m_currentMenu.serialMessage);
    sendNewLine(2);
    sendROM(topOption1);
    sendNewLine(1);
    sendROM(topOption2);
    sendNewLine(1);
    sendROM(topOption3);
    sendNewLine(1);
    sendROM(topOption4);
    sendNewLine(1);
    sendROM(topOption5);
    sendNewLine(1);

    // Print the FACTORY options
    if (m_userMode == FACTORY)
    {
        sendROM(topOptionCalTemp);
        sendNewLine(1);

        // @TODO Remove and test now that they key switches between modes
        sendROM(topOptionForFactory);
    }
    else
    {
        // Print the switch to Local option
        sendROM(topOptionLocal);
    }

    // Print text which teaches the user how to navigate menus
    sendNewLine(2);
    sendROM(CHOOSE);
    sendNewLine(1);
    sendROM(CHOOSE2);
}

/*!
 * Function: dispAzOptions
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Displays the strings for the different options the user can
 *               choose whilst in the Azimuth menu. It also accounts for
 *               Factory mode by printing extra messages the user can choose.
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
static void dispAzOptions()
{
    // Print the Remote level options
    sendROM(azOption1);
    sendNewLine(1);
    sendROM(azOption2);
    sendNewLine(1);
    sendROM(azOption3);
    sendNewLine(1);

    // Print the FACTORY options
    if (m_userMode == FACTORY)
    {
        sendROM(azOption4);
        sendNewLine(1);
        transChar('\t');
        sendROM(menuPrefix5);
        transChar('\t');
        sendROM(goUp);
    }
    else
    {
        // Print the Return option
        transChar('\t');
        sendROM(menuPrefix4);
        transChar('\t');
        sendROM(goUp);
    }

    // Print lines to help the user navigate
    sendNewLine(2);
    sendROM(CHOOSE);
    sendNewLine(1);
    sendROM(CHOOSE2);
}

/*!
 * Function: dispElOptions
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Displays the strings for the different options the user can
 *               choose whilst in the Elevation menu. It also accounts for
 *               Factory mode by printing extra messages the user can choose.
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
static void dispElOptions()
{
    // Print REMOTE options
    sendROM(elOption1);
    sendNewLine(1);
    sendROM(elOption2);
    sendNewLine(1);
    sendROM(elOption3);
    sendNewLine(1);

    // Print FACTORY options
    if (m_userMode == FACTORY)
    {
        sendROM(elOption4);
        sendNewLine(1);
        transChar('\t');
        sendROM(menuPrefix5);
        transChar('\t');
        sendROM(goUp);
    }
    // Print the Return option in REMOTE
    else
    {
        transChar('\t');
        sendROM(menuPrefix4);
        transChar('\t');
        sendROM(goUp);
    }

    // Print messages to help the user navigate
    sendNewLine(2);
    sendROM(CHOOSE);
    sendNewLine(1);
    sendROM(CHOOSE2);
}

/*!
 * Function: dispRngOptions
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Displays the strings for the different options the user can
 *               choose whilst in the Range menu. It also accounts for
 *               Factory mode by printing extra messages the user can choose.
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
static void dispRngOptions()
{
    // Print the REMOTE options
    sendROM(rngOption1);
    sendNewLine(1);
    sendROM(rngOption2);
    sendNewLine(1);

    // Print the FACTORY options
    if (m_userMode == FACTORY)
    {
        sendROM(rngOption3);
        sendNewLine(1);
        sendROM(rngOption4);
        sendNewLine(1);
        sendROM(rngOption5);
        sendNewLine(1);
        sendROM(rngOption7);
        sendNewLine(1);
        sendROM(rngOption8);
        sendNewLine(1);
        transChar('\t');
        sendROM(menuPrefix8);
        transChar('\t');
        sendROM(goUp);
    }
    // Otherwise print the Return option
    else
    {
        transChar('\t');
        sendROM(menuPrefix3);
        transChar('\t');
        sendROM(goUp);
    }

    // Print messages to help the user navigate
    sendNewLine(2);
    sendROM(CHOOSE);
    sendNewLine(1);
    sendROM(CHOOSE2);
}

/*!
 * Function: dispTempSerialMessage
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Prints the serial message for the temperature sensor. This needed
 *               its own function as it needs to read the temperature and convert
 *               the temp reading to ASCII.
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
static void dispTempSerialMessage(void)
{
    int temp = readTemp();
    sendROM("\t");
    sendROM(showTemp1);
    transmit(intToAscii(temp));
    sendROM(showTemp2);
}

/*!
 * Function: dispSerialMessage
 *
 * @Include Local to menuSystem.c
 *
 * @Description: Generic function used to display the serial message for the
 *               current menu.
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
static void dispSerialMessage(void)
{
    sendROM("\t");
    sendROM(m_currentMenu.serialMessage);
}

/*!
 * Function: dispSetValueMEssage
 *
 * @Include Range.c, PanTilt.c
 *
 * @Description: Display the menu serial message with the maximum, minimum
 *               and current values so that the user knows what to input. This
 *               function also retrieves the current values from their corresponding
 *               classes.
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
static void dispSetValueMessage(void)
{
    int num = 0;
    Direction dir;

    sendROM("\t");
    sendROM(m_currentMenu.serialMessage);
    sendNewLine(1);

    // Enter a value between x and y
    sendROM("\t");
    sendROM(inputNumRangeStr);
    transmit(intToAscii(m_currentMenu.minVal));
    sendROM(and);
    transmit(intToAscii(m_currentMenu.maxVal));
    sendNewLine(1);

    // The current value is:
    sendROM("\t");
    sendROM(currentValueStr);

    // Get the current value
    switch (m_currentMenu.menuID)
    {
        case AZ_GOTO:
            dir = getDir();
            num = (int) dir.azimuth;
            break;
        case EL_GOTO:
            dir = getDir();
            num = (int) dir.elevation;
            break;
        case AZ_MIN:
            num = getMinAzimuthAngle();
            break;
        case AZ_MAX:
            num = getMaxAzimuthAngle();
            break;
        case EL_MIN:
            num = getMaxAzimuthAngle();
            break;
        case EL_MAX:
            num = getMaxAzimuthAngle();
            break;
        case RANGE_MIN:
            num = getMinRange();
            break;
        case RANGE_MAX:
            num = getMaxRange();
            break;
        case US_SAMPLE_RATE:
            num = getUsSampleRate();
            break;
        case US_SAMPLE_AVG:
            num = getNumSamples();
            break;
    }
    transmit(intToAscii(num));
    sendNewLine(1);
}

/*!
 * Function: dispTrack
 *
 * @Include Local to MenuSystem.c
 *
 * @Description: Displays the tracking data (Range, Azimuth and Elevation) over
 *               serial on one line, by clearing the line between prints.
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
void dispTrack(TrackingData target)
{
    unsigned int j;

    // Strings not in ROM
    const char rng_string[] = "Range: ";
    const char inc_string[] = "Elevation: ";
    const char az_string[] = "Azimuth: ";
    const char separator[] = "\t";
    char unitsR[] = "mm";
    char unitsD[] = "deg";
    char num[5];

    // Error checking for bad values
    if (target.azimuth > 100 || target.azimuth < -100) return;

    // If in tracking mode, Display the Azimuth, Elevation and Range
    if (m_currentMenu.menuID == TRACKING && transmitComplete())
    {
        // Clear the line
        sendROM(CLEAR_LINE_STRING);
        transChar('\r');

        // Display range data
        transmit(rng_string);
        sprintf(num, "%d", target.range);
        transmit(num);
        transmit(unitsR);
        transmit(separator);

        // Display Azimuth data
        transmit(az_string);
        sprintf(num, "%d", target.azimuth);
        transmit(num);
        transmit(unitsD);
        transmit(separator);

        // Display Elevation Data
        transmit(inc_string);
        sprintf(num, "%d", target.elevation);
        transmit(num);
        transmit(unitsD);
        transmit(separator);
    }
}

/*!
 * Displays the Tracking data over serial
 */
/*!
 * Function: dispRawRange
 *
 * @Include Range.c
 *
 * @Description: Displays the raw IR and US data after being converted to mm,
 *               before any calibration and merging of values.
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
void dispRawRange()
{
    unsigned int j;

    // Strings not stored in ROM
    const char us_rng_string[] = "US Range: ";
    const char ir_string[] = "IR Range: ";
    const char separator[] = "\t";
    char unitsR[] = "mm";
    char num[5];

    unsigned int irRange = rawRangeIR();
    unsigned int usRange = rawRangeUS();

    // If in tracking mode, Display the Azimuth, Elevation and Range
    if (m_currentMenu.menuID == RANGE_RAW && transmitComplete())
    {
        sendROM(CLEAR_LINE_STRING);
        transChar('\r');
        transmit(us_rng_string);
        sprintf(num, "%u", usRange);
        transmit(num);
        transmit(unitsR);
        transmit(separator);

        transmit(ir_string);
        sprintf(num, "%u", irRange);
        transmit(num);
        transmit(unitsR);
    }
}

/*!
 * Function: dispSearching
 *
 * @Include Local to MenuSystem.c
 *
 * @Description: Displays the searching message in tracking mode
 *
 * @Arguments:  N/A
 *
 * @Returns:    N/A
 */
void dispSearching()
{
    // Clear display and search!
    if (m_currentMenu.menuID == TRACKING && transmitComplete())
    {
        // Transmit the buffer to clear the extra chars
        transChar('\r');
        transmit(CLEAR_LINE_STRING);
        transChar('\r');
        sendROM(autoSearching);
    }
}

// *****************************************************************************
// ****************************** LCD FUNCTIONS **********************************
// *****************************************************************************

/*!
 * Function: dispLCDTopMenu
 *
 * @Include Range.c, PanTilt.c
 *
 * @Description: Display a message on the LCD display depending on what
 *               the value that the potentiometer is reading based on the
 *               menu options contextualised by the the Top level menu.
 *
 * @Arguments:  int option - The value that the potentiometer has read, scaled
 *                           to within the bounds of this menu.
 *
 * @Returns:    N/A
 */
// COMMENTED OUT DUE TO LOCAL INTERFACE ISSUES
//static void dispLCDTopMenu(int option)
//{
//    char string[20] = {0};
//    switch(option)
//    {
//        case 1:
//            //Automatic Tracking;
//            strcpypgm2ram(string, Tracking.lcdTitleMessage);
//            break;
//        case 2:
//            // Azimuth Menu
//            strcpypgm2ram(string, AzMenu.lcdTitleMessage);
//            break;
//        case 3:
//            // Elevation Menu
//            strcpypgm2ram(string, ElMenu.lcdTitleMessage);
//            break;
//        case 4:
//            // Range Menu
//            strcpypgm2ram(string, RangeMenu.lcdTitleMessage);
//            break;
//        case 5:
//            // Show Temp
//            strcpypgm2ram(string, ShowTemp.lcdTitleMessage);
//            break;
//        case 6:
//            // Switch to Remote
//            strcpypgm2ram(string, topOptionRemoteLCD);
//            break;
//        default:
//            strcpypgm2ram(string, "ERROR");
//    }
//    lcdWriteString(string, 2);
//}


/*!
 * Function: dispLCDAzMenu
 *
 * @Include Range.c, PanTilt.c
 *
 * @Description: Display a message on the LCD display depending on what
 *               the value that the potentiometer is reading based on the
 *               menu options contextualised by the the Azimuth menu.
 *
 * @Arguments:  int option - The value that the potentiometer has read, scaled
 *                           to within the bounds of this menu.
 *
 * @Returns:    N/A
 */
// COMMENTED OUT DUE TO LOCAL INTERFACE ISSUES
//static void dispLCDAzMenu(int option)
//{
//    char string[20] = {0};
//    switch(option)
//    {
//        case 1:
//            // Go to Azimuth
//            strcpypgm2ram(string, AzGoto.lcdTitleMessage);
//            break;
//        case 2:
//            // Set Min Azimuth
//            strcpypgm2ram(string, AzMin.lcdTitleMessage);
//            break;
//        case 3:
//            // Set Max Azimuth
//            strcpypgm2ram(string, AzMax.lcdTitleMessage);
//            break;
//        default:
//            strcpypgm2ram(string, "ERROR");
//    }
//    lcdWriteString(string, 2);
//}


/*!
 * Function: dispLCDElMenu
 *
 * @Include Range.c, PanTilt.c
 *
 * @Description: Display a message on the LCD display depending on what
 *               the value that the potentiometer is reading based on the
 *               menu options contextualised by the the Elevation menu.
 *
 * @Arguments:  int option - The value that the potentiometer has read, scaled
 *                           to within the bounds of this menu.
 *
 * @Returns:    N/A
 */
// COMMENTED OUT DUE TO LOCAL INTERFACE ISSUES
//static void dispLCDElMenu(int option)
//{
//    char string[20] = {0};
//    switch(option)
//    {
//        case 1:
//            // Go to Elevation
//            strcpypgm2ram(string,  ElGoto.lcdTitleMessage);
//            break;
//        case 2:
//            // Set Min Elevation
//            strcpypgm2ram(string, ElMin.lcdTitleMessage);
//            break;
//        case 3:
//            // Set Max Elevation
//            strcpypgm2ram(string, ElMax.lcdTitleMessage);
//            break;
//        default:
//            strcpypgm2ram(string, "ERROR");
//    }
//   lcdWriteString(string, 2);
//}


/*!
 * Function: dispLCDRngMenu
 *
 * @Include Range.c, PanTilt.c
 *
 * @Description: Display a message on the LCD display depending on what
 *               the value that the potentiometer is reading based on the
 *               menu options contextualised by the the Range menu.
 *
 * @Arguments:  int option - The value that the potentiometer has read, scaled
 *                           to within the bounds of this menu.
 *
 * @Returns:    N/A
 */
// COMMENTED OUT DUE TO LOCAL INTERFACE ISSUES
//static void dispLCDRngMenu(int option)
//{
//    char string[20] = {0};
//    switch(option)
//    {
//        case 1:
//            // Set Min Range
//            strcpypgm2ram(string, RngMin.lcdTitleMessage);
//            break;
//        case 3:
//            // Set Max Range
//            strcpypgm2ram(string, RngMax.lcdTitleMessage);
//            break;
//        default:
//            strcpypgm2ram(string, "ERROR");
//    }
//    lcdWriteString(string, 2);
//}


/*!
 * Function: dispLCDNum
 *
 * @Include Range.c, PanTilt.c
 *
 * @Description: Display a number on the LCD display depending on what
 *               the value that the potentiometer is reading based on the
 *               max/min/interval of the current menu.
 *
 * @Arguments:  int option - The value that the potentiometer has read, scaled
 *                           to within the bounds of this menu.
 *
 * @Returns:    N/A
 */
// COMMENTED OUT DUE TO LOCAL INTERFACE ISSUES
//static void dispLCDNum(int option)
//{
//    char *string = intToAscii(option);
//    lcdWriteString(string, 2);
//}



