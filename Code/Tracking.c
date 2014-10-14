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
//#include <math.h>

//Variable to store where the sensors are currently pointing
//DirectionState current_direction;

/* **********************************************************************
 * Function: configBase(void)
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
    static Direction lateral = {1, 0};
    static Direction vertical = {1, 0};
    Direction dir;
    
    dir = getDir();

    //If max azimuth range, increment vertical and change azimuth direction
    if (dir.azimuth > 30 || dir.azimuth < -30)
    {
        increment(vertical);                //Move up (or down) vertically 1 degree
        if (dir.azimuth < 0 && dir.azimuth < 0) lateral.azimuth = -lateral.azimuth; //Move in the opposite azimuth
        if (dir.azimuth > 0 && dir.azimuth > 0) lateral.azimuth = -lateral.azimuth;
        increment(lateral);
    }
    //If max inclination range, change vertical direction and increment vertical
    else if (dir.inclination > 20 || dir.inclination < -40)
    {
        if (dir.inclination < 0 && dir.inclination < 0) lateral.inclination = -lateral.inclination; //Move in the opposite azimuth
        if (dir.inclination > 0 && dir.inclination > 0) lateral.inclination = -lateral.inclination;
        increment(vertical);
    }
    //Alse just move in azimuth
    else
    {
        increment(lateral);
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
    TrackingData result;
    Direction inc;

    char i;

    inc.azimuth = 5;
    inc.inclination = 0;

    //Check if the target is in range of the IR
    if (rangeIR())
    {
        for (i = 0; i < 2; i++)
        {
            //Find first edge
            while (rangeIR()) increment(inc);

            //Change direction
            inc.azimuth = -inc.azimuth;
            inc.inclination = -inc.inclination;

            //Refind target, and find other edge
            while (!rangeIR()) increment(inc);
            while(rangeIR()) increment(inc);
        }
    }
}