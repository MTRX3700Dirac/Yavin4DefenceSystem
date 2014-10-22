/*! ****************************************************************************
 * File:   Tracking.c
 * Author: Grant
 *
 * Description:
 * Contains all the functionality for the Tracking Module. This module contains the
 * functionality and algorithms used to search for, and track the target. This
 * module makes use of PanTilt, Range and Temp modules, and configures them
 * automatically from a call to configureTrack().
 *
 * Duties:
 *      -Control and coordinate Pan Tilt and range sensors
 *      -Implement searching and tracking algorithms
 *      -Predict next position of target???
 *
 * Functions:
 * 
 *
 * Created on 15 September 2014, 1:42 PM
 ******************************************************************************/

#include "Common.h"
#include "Range.h"
#include "PanTilt.h"

#define diff 5
#define TARGET_RAD 30  //The diameter of the target in mm (slightly larger)
#include <delays.h>

/* **********************************************************************
 * Function: configureTracking(void)
 *
 * Include: Tracking.h
 *
 * Description: Configures the System to begin tracking/searching
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void configureTracking(void)
{
    configureBase();
    configureRange();
}

/* **********************************************************************
 * Function: search(void)
 *
 * Include: Tracking.h
 *
 * Description: Performs an incrimental change in position. Local variables
 *              store previous movements to create a search pattern
 *
 * Arguments: None
 *
 * Returns: None
 *
 * @todo Possibly better searchin algorithm? Tune parameters etc.
 * @todo Coordinate sampling rate with searching
 *************************************************************************/
void search(systemState *state)
{
    unsigned int j;
    //Vertical and laterial incremental movements
    static Direction lateral = {diff, 0};
    static Direction vertical = {0, diff};
    static TargetState previousState;
    TargetState currentState;
    Direction dir;

    dir = getDir();

    for (j = 0; j < 10000; j++);
    //If max azimuth range, increment vertical and change azimuth direction
    if (dir.azimuth > 40 || dir.azimuth < -40)
    {
        increment(vertical);                //Move up (or down) vertically 1 degree
        if (dir.azimuth < 0 && dir.azimuth < 0) lateral.azimuth = diff; //Move in the opposite azimuth
        if (dir.azimuth > 0 && dir.azimuth > 0) lateral.azimuth = -diff;
        increment(lateral);
    }
    //If max inclination range, change vertical direction and increment vertical
    else if (dir.inclination > 10 || dir.inclination < -40)
    {
        if (dir.inclination < 0 && dir.inclination < 0) vertical.inclination = diff; //Move in the opposite azimuth
        if (dir.inclination > 0 && dir.inclination > 0) vertical.inclination = -diff;
        increment(vertical);
    }
    //Alse just move in azimuth
    else
    {
        increment(lateral);
    }

    previousState = currentState;
    currentState = readTargetState();
    switch (currentState)
    {
        case GOOD_TRACK:
            NEXT_STATE_PTR(TRCK, state);
            break;
        case BAD_DIR:
            //In the correct vicinity, but not exact
            NEXT_STATE_PTR(TRCK, state);
            break;
        default:
            break;
    }
}

/* **********************************************************************
 * Function: trackingISR(void)
 *
 * Include: Tracking.h
 *
 * Description: Acts as the Interrupt Service Routine for the Tracking module
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
void trackingISR(void)
{
    
}

/* **********************************************************************
 * Function: track(void)
 *
 * Include: Tracking.h
 *
 * Description: Finds the Edge of the target in both the azimuth and inclination
 *              and uses this to find (and move to) the center of the target.
 *
 * Arguments: None
 *
 * Returns: TargetData - The current target information (Azimuth, inclination
 *                       and range to the target). This information is then used
 *                       for the Display in the User interface module.
 *
 * @todo Incorperate prediction, and calculate offset angle based on distance, and known accuracy
 * @todo Include a sampling rate into tracking
 *************************************************************************/
TrackingData track(systemState *state)
{
    char i, count = 0;
    char weight;
    unsigned int j;
    Direction centre;
    signed long int inclination = 0;
    signed long int azimuth = 0;
    TrackingData result;
    Direction dir;
    Direction inc[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; //Incremental change in direction NOT IN DEGREES! (much finer increments)
    char angle;

    //angle = TARGET_RAD * (unsigned int)57 / range();
    angle = 8;

    centre = getDir();

    for (i = 0; i < 4; i++)
    {
        //Calc new direction
        dir.azimuth = centre.azimuth + inc[i].azimuth * angle;
        dir.inclination = centre.inclination + inc[i].inclination * angle;

        //Move to new direction
        move(dir);

        //Get target state (stored in weight temporarily)
        weight = readTargetState();

        //Calculate weighting of that sample
        weight = (weight == GOOD_TRACK) * 4 + (weight == BAD_DIR);
        
        count += weight;
        azimuth += (int)weight * dir.azimuth;
        inclination += (int)weight * dir.inclination;
    }

    //Go back to searching if there is not a good track, else stay in track
    if (count == 0)
    {
        NEXT_STATE_PTR(SRCH, state);
    }
    else
    {
        //Calculate weighted average of the results
        centre.azimuth = azimuth / count;
        centre.inclination = inclination / count;

        move(centre);

        result.distance = range();
        result.azimuth = centre.azimuth;
        result.inclination = centre.inclination;
    }

    return result;
}

/* **********************************************************************
 * Function: prediction(Direction current)
 *
 * Include: Local to Tracking.c
 *
 * Description: Predicts where the object is likely to be found based on previous
 *              movement and prediction algorithms
 *
 * Arguments: current - The current position of the target
 *
 * Returns: Direction - The Predicted likely location
 *
 * @todo Finish and test this function, incorperate it into tracking
 *************************************************************************/
static Direction prediction(Direction current)
{
#define TIMER   TMR2        //General purpose timer
    static Direction previous = {0, 0};
    static unsigned int prev_time;
    static Direction next_predict;
    return next_predict;
}