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

#define diff 8
#define TARGET_RAD 30  //The diameter of the target in mm (slightly larger)
#include <delays.h>
#include <timers.h>

/*! ****************************************************************************
 * typedef of targetStateData struct
 *
 * @brief Stores data about the last target track
 *
 * Description:
 * Stores the number of samples of each type sampled in the previous target track
 *
 * Elements:
 *      -bad_dirs - stores the number of BAD_DIR's sampled - only 3 bits
 *      -out_of_irs - Stores the number of OUT_OF_IR's sampled - only 3 bits
 *      -good_tracks - Stores the number of GOOD_TRACK's sampled - only 3 bits
 ******************************************************************************/
typedef struct
{
    unsigned bad_dirs : 2;
    unsigned out_of_irs : 2;
    unsigned good_tracks : 2;
    unsigned centre : 2;
} TargetStateData;

static char newAngle(char angle, TargetStateData target_data);

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
//
//    //Set up TMR2 for prediction purposes
//    CloseTimer0();
//    OpenTimer0(T0_16BIT & T0_SOURCE_INT & T0_PS_1_256);
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

    for (j = 0; j < 5000; j++);
    //If max azimuth range, increment vertical and change azimuth direction
    //if (dir.azimuth > 40 || dir.azimuth < -40)
    if (dir.azimuth > getMaxAzimuthAngle() || dir.azimuth < getMinAzimuthAngle())
    {
        increment(vertical);                //Move up (or down) vertically 1 degree
        if (dir.azimuth < 0 && dir.azimuth < 0) lateral.azimuth = diff; //Move in the opposite azimuth
        if (dir.azimuth > 0 && dir.azimuth > 0) lateral.azimuth = -diff;
        increment(lateral);
    }
    //If max inclination range, change vertical direction and increment vertical
    //else if (dir.elevation > 10 || dir.elevation < -40)
    else if (dir.elevation > getMaxElevationAngle() || dir.elevation < getMinElevationAngle())
    {
        if (dir.elevation < 0 && dir.elevation < 0) vertical.elevation = diff; //Move in the opposite azimuth
        if (dir.elevation > 0 && dir.elevation > 0) vertical.elevation = -diff;
        increment(vertical);
    }
    //Alse just move in azimuth
    else
    {
        increment(lateral);
    }

    previousState = currentState;
    currentState = readTargetState();

    if (currentState == GOOD_TRACK || currentState == BAD_DIR || currentState == CLOSE_RANGE)
    {
        NEXT_STATE_PTR(TRCK, state);
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
 *************************************************************************/
TrackingData track(systemState *state)
{
#define sampleTargetState weight
    char i, count = 0;
    char weight;
    unsigned int j;
    unsigned int rng;
    Direction centre;
    signed long int inclination = 0;
    signed long int azimuth = 0;
    TrackingData result;
    Direction dir;
    Direction inc[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; //Incremental change in direction NOT IN DEGREES! (much finer increments)
    char angle;
    TargetStateData target_data;

    //angle = 2 * TARGET_RAD * (unsigned int)57 / range();
    rng = range();
    if (rng)
    {
        angle = 13 * (unsigned int)300 / rng + 5;
    }
    else
    {
        angle = 10;
    }

    centre = getDir();

    for (i = 0; i < 4; i++)
    {
        //Calc new direction
        dir.azimuth = centre.azimuth + inc[i].azimuth * angle;
        dir.elevation = centre.elevation + inc[i].elevation * angle;

        //Move to new direction
        move(dir);

        for (j = 0; j < 4000; j++);

        //Get target state (stored in weight temporarily)
        sampleTargetState = readTargetState();

        //Calculate weighting of the sample (1 is the worst, the higher the better)
        weight = (sampleTargetState == GOOD_TRACK) * 5 + (sampleTargetState == BAD_DIR) + (sampleTargetState == OUT_OF_IR) + (sampleTargetState == GOOD_TRACK) * 3;
        
        count += weight;
        azimuth += (int)weight * dir.azimuth;
        inclination += (int)weight * dir.elevation;
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
        centre.elevation = inclination / count;

        move(centre);

        for (j = 0; j < 4000; j++);

        result.range = range();
        result.azimuth = centre.azimuth;
        result.elevation = centre.elevation;
    }

    return result;
#undef sampleTargetState
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
 *************************************************************************/
static Direction prediction(Direction current)
{
#define TIMER   TMR2        //General purpose timer
    static Direction previous = {0, 0};
    static unsigned int prev_time;
    static Direction next_predict;
    return next_predict;
}

/* **********************************************************************
 * Function: newAngle(void)
 *
 * Include: Local to Tracking.c
 *
 * Description: Calculates the new angle offset
 *
 * Arguments: angle - The previous angle
 *
 *            target_data - The data from the last target sample
 *
 * Returns: Angle - The new angle to offset the direction
 *************************************************************************/
static char newAngle(char angle, TargetStateData target_data)
{
    //Target field too narrow, and a little out, so increase range to get some direction data

    if (target_data.centre == 0)
    {
        angle += (target_data.good_tracks > 2) - (target_data.good_tracks == 1 && (target_data.bad_dirs + target_data.out_of_irs == 4));
    }

    if (angle < 1) return 1;
    else return angle;
}