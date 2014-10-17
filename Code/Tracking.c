/*
 * File:   Tracking.c
 * Author: Grant
 *
 * Description: Contains all the functionality for the Tracking Module
 *
 * Created on 15 September 2014, 1:42 PM
 */

#include "Common.h"
#include "Range.h"
#include "PanTilt.h"

#define diff 5
#include <delays.h>

//Variable to store where the sensors are currently pointing
//DirectionState current_direction;

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
void search(void)
{
    //Vertical and laterial incremental movements
    static Direction lateral = {diff, 0};
    static Direction vertical = {0, diff};
    Direction dir;
    
    dir = getDir();

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
}

/* **********************************************************************
 * Function: search2(void)
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
TargetState search2(void)
{
    unsigned int delay = 60000;
    signed int diff = 1;
    int i;
    //Vertical and laterial incremental movements
    static Direction lateral = {1, 0};
    static Direction vertical = {0, 1};
    static TargetState previousState;
    TargetState currentState;
    Direction dir;

    dir = getDir();

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
    for (i = 0; i < 10000; i++);    //Arbitrary delay

    currentState = readTargetState();
    previousState = readTargetState();
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
 * Function: edge(void)
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
TrackingData edge(void)
{
    char i, j;
    unsigned int k;
    unsigned int delay = 0;       //Delay time in x10us between each range reading
    Direction centre;
    TrackingData result;
    Direction edge1, edge2;
    Direction inc = {1, 0}; //Incremental change in direction NOT IN DEGREES! (much finer increments)

    

    //Check if the target is in range of the IR
    if (readTargetState() == GOOD_TRACK)
    {
        for (i = 0; i < 2; i++)
        {
            //Find first edge
            for (j = 0; readTargetState() == GOOD_TRACK && j <= 10;j++)
            //while (readTargetState() == GOOD_TRACK)
            {
                increment(inc);
                for (delay = 0; delay<25000;delay++);
            }
            edge1 = getDir();       //Stores the first edge

            //Change direction
            inc.azimuth = -inc.azimuth;
            inc.inclination = -inc.inclination;

            //Refind target, and find other edge
            for (j = 0; readTargetState() != GOOD_TRACK && j <= 10;j++)
            //while (readTargetState() != GOOD_TRACK)
            {
                increment(inc);
            }
            for(j=0; readTargetState() == GOOD_TRACK && j <= 10; j++)
            //while (readTargetState() == GOOD_TRACK)
            {
                increment(inc);
            }
            edge2 = getDir();       //Stores the second edge

            centre.azimuth = (edge1.azimuth + edge2.azimuth)/2;
            centre.inclination = (edge1.inclination + edge2.inclination)/2;

            move(centre);   //Go back to the centre of the target
            for (k = 0; k < 20000; k++);
            SWAP(inc.azimuth, inc.inclination);     //Test the other degree of freedom
        }
    }

    result.distance = range();
    result.azimuth = centre.azimuth;
    result.inclination = centre.inclination;

    return result;
}