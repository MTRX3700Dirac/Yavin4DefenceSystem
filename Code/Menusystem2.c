#include "Common.h"
#include "Serial.h"
#include "User_Interface.h"
#include "LCD.h"
#include "PanTilt.h"

#define MAX_SER_MSG_LEN 30
#define MAX_LCD_MSG_LEN 20
#define MAX_NUM_OPTIONS 5

typedef struct
{
    char serialMessage[MAX_SER_MSG_LEN];    //Serial Message to be displayed on entering the state
    char lcdMessage[MAX_LCD_MSG_LEN];       //LCD Message to be displayed on entering the state
    char serialOptions[MAX_NUM_OPTIONS];    //The serial options available in this state
    char inptOptions[MAX_NUM_OPTIONS];      //The user input options available in this state

    SubMenu *subMenues[MAX_NUM_OPTIONS];    //Pointers to Available sub menues
    void (*numericFunction)(int);
    void (*defaultFunction)(void);
} SubMenu;

typedef enum{ROOT, SUB, FUNC} MenuLevel;


//Sub menu objects:
static SubMenu Min = { "Set Minimum", "Set Min", {}, {}, {}, setMinAzimuthAngle, 0};
static SubMenu Max = { "Set Maximum", "Set Max", {}, {}, {}, setMaxAzimuthAngle, 0};

static SubMenu AutoTrack = {"Auto Tracking", "Auto Tracking", {}, {}, {}, 0, 0};
static SubMenu ManTrack;
static SubMenu Az;
static SubMenu Elev;

static SubMenu Root = { "Welcome to Yavin IV Defence System", "Welcome", { '1', '2', '3', '4' }, { &AutoTrack, &ManTrack, &Az, &Elev }, 0, 0 };


static MenuLevel level = ROOT;
static SubMenu menus[3] = { Root, AutoTrack, Min };


static void parseInput(char input);
static int parseNumeric(char *input);
static void stateEntry(void);

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
void initialiseMenu(void)
{
    configureSerial();
    //configLCD();
    configUSER();

    
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
    char input;
    char string[50];
    int numericInpt;

    //Return if there is no user input
    if (receiveEmpty() && userEmpty()) return;

    //If state takes numeric value, and carriage return has been entered, parse string
    if (menus[level].numericFunction && receiveCR())
    {
        readString(string);
        numericInpt = parseNumeric(string);

        //Call the numeric function defined in the state object
        menus[level].numericFunction(numericInpt);
        return;
    }

    //Get a character from the buffer
    input = receivePop();
    parseInput(input);
    
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
void menuISR(void)
{
    
}

/*! **********************************************************************
 * Function: parseInput(char input)
 *
 * \brief parse the user input
 *
 * Include: Menusystem.h
 *
 * Description: services any interrupts associated with the menu system
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
static void parseInput(char input)
{
    char i = 0;

    //A null input may match uninitialised input options, calling a null function pointer and breaking the program
    if (!input) return;

    for (i = 0; i < MAX_NUM_OPTIONS; i++)
    {
        //Check if input character matches one of the input options
        if (input == menus[level].inptOptions[i])
        {
            //Go down a menu state and set the sub menu to the option chosen
            level++;
            menus[level] = menus[level - 1].subMenues[i];
        }
    }
}

/*! **********************************************************************
 * Function: parseNumeric(char *number)
 *
 * \brief parses user input string into a number
 *
 * Include: 
 *
 * Description: Calls the function which matches the user input
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
static int parseNumeric(char *number)
{
    
}

/*! **********************************************************************
 * Function: stateEntry(void)
 *
 * \brief Performs default actions on first entering the state
 *
 * Include:
 *
 * Description: 
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
static void stateEntry(void)
{
    //If this state has a default function, call it
    if (menus[level].defaultFunction)
    {
        menus[level].defaultFunction();
    }

    //Display the state message
    transmit(menus[level].serialMessage);
    displayLCD(menus[level].lcdMessage);
}