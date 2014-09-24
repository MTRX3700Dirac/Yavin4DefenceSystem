/* 
 * File:   newmain.c
 * Author: Grant
 *
 * Description: Controls the main system state of the product based on a state
 *              transition type template
 *
 * Created on 7 September 2014, 4:12 PM
 */

#include <p18f452.h>

//Hack to get salvo thing working

#define OSMAKE_LIBRARY                  TRUE
#define OSLIBRARY_TYPE  OSF
#define OSLIBRARY_CONFIG OSS
#define OSLIBRARY_GLOBALS OSF

#include "Common.h"
#include "Tracking.h"
#include "Range.h"
#include "User_Interface.h"
#include "Serial.h"

#include "PanTilt.h"
#include "Temp.h"

#include "salvo.h"



//Define Macros to change the state of the system
#define NEXT_STATE(s) state.previous = state.current; state.current = s
#define NEXT_STATE_PTR(s) state->previous = state->current; state->current = s

//Define the enum and struct to store the current system state
typedef enum{UNDEF, INIT, CHANGE, MEAS, EDGE} possible_states;
typedef struct {
    possible_states current;
    possible_states previous;
} systemState;

//Function Prototypes:
void initialization(systemState *state);
void check_target(systemState *state);
void change_direction(systemState *state);
void measure_distance(systemState *state, TrackingData *target);
void find_edge(systemState *state, TrackingData *target);
void post_edge(TrackingData *target);

void lowISR(void);
void highISR(void);

//Task declarations:
void TempTask(void);
void TrackingTask(void);
void UserInputTask(void);
void RangeMeasTask(void);
void SerialRCTask(void);
void SerialTXTask(void);


/* **********************************************************************
 * Function: main(void)
 *
 * Include: 
 *
 * Description: stores the current system state and manages all transitions
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void main() {
    //Initialise Salvo
    OSInit();

    //Define task functions as tasks
    OSCreateTask(TempTask, OSTCBP(1), 10);
    OSCreateTask(TrackingTask, OSTCBP(1), 10);
    OSCreateTask(UserInputTask, OSTCBP(1), 10);
    OSCreateTask(RangeMeasTask, OSTCBP(1), 10);
    OSCreateTask(SerialRCTask, OSTCBP(1), 10);
    OSCreateTask(SerialTXTask, OSTCBP(1), 10);

    //Repeatedly call the scheduler
    for (;;)
    {
        OSSched();
    }

}

/* **********************************************************************
 * Function: TempTask(void)
 *
 * Include: <salvo.h>
 *
 * Description: Temperature Task to read the temperature at regular intervals
 *
 * Arguments: None
 *************************************************************************/
void TempTask(void)
{
    for (;;)
    {
        readTemp();
        OSDelay(TEMP_SAMPLE_PERIOD);
    }
}

/* **********************************************************************
 * Function: TrackingTask(void)
 *
 * Include: <salvo.h>
 *
 * Description: Tracking Task to search/track the target at regular intervals
 *
 * Arguments: None
 *************************************************************************/
void TrackingTask(void)
{
    for (;;)
    {
        //This function will also have the targeting in it, which will be taken care of in the module
        search();
        OSDelay(TRACK_SAMPLE_PERIOD);
    }
}

/* **********************************************************************
 * Function: UserInputTask(void)
 *
 * Include: <salvo.h>
 *
 * Description: User input Task to read input from the user interface
 *
 * Arguments: None
 *************************************************************************/
void UserInputTask(void)
{
    
}

/* **********************************************************************
 * Function: RangeMeasTask(void)
 *
 * Include: <salvo.h>
 *
 * Description: Range Measurement Task to read the range at regular intervals
 *
 * Arguments: None
 *************************************************************************/
void RangeMeasTask(void)
{

}

/* **********************************************************************
 * Function: SerialRCTask(void)
 *
 * Include: <salvo.h>
 *
 * Description: Serial Receive Task to handle any serial inputs (remove large
 *              computation from the ISR)
 *
 * Arguments: None
 *************************************************************************/
void SerialRCTask(void)
{

}

/* **********************************************************************
 * Function: SerialTXTask(void)
 *
 * Include: <salvo.h>
 *
 * Description: Serial Transmit Task to handle access to the circular transmit
 *              buffer
 *
 * Arguments: None
 *************************************************************************/
void SerialTXTask(void)
{

}