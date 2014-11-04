/*! ****************************************************************************
 * File:   Tracking.h
 * Author: Grant
 *
 * Description:
 * Public interface function for the Tracking Module. This module contains the
 * functionality and algorithms used to search for, and track the target. This
 * module makes use of PanTilt, Range and Temp modules, and configures them
 * automatically from a call to configureTrack().
 *
 * Contains:
 *      -Configure tracking
 *      -Searching algorithm
 *      -Track algorithm
 *
 * Created on 15 September 2014, 1:41 PM
 ******************************************************************************/

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef TRACK_H

//#define TRACK_INT (CCP2_INT)
#define TRACK_INT 0

/*============================================================================*/
//External declarations for the public access functions
/*============================================================================*/

/*! **********************************************************************
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
extern void configureTracking(void);

/*! **********************************************************************
 * Function: search(void)
 *
 * Include: Tracking.h
 *
 * Description: Performs an incrimental change in position. Local variables
 *              store previous movements to create a raster-like search pattern.
 *              Then samples the range sensors and determines the next system
 *              state.
 *
 * Arguments: state - a pointer to the current system state
 *
 * Returns: None
 *************************************************************************/
extern void search(systemState *state);

/*! **********************************************************************
 * Function: track(void)
 *
 * Include: Tracking.h
 *
 * Description: Takes a number of samples at the previous target location, and
 *              several descrete locations around the target location and takes
 *              a weighted average based on the sampled signal return
 *
 * Arguments: state - A pointer to the current system state
 *
 * Returns: TargetData - The current target information (Azimuth, inclination
 *                       and range to the target). This information is then used
 *                       for the Display in the User interface module.
 *************************************************************************/
extern TrackingData track(systemState *state);

/*! **********************************************************************
 * Function: trackingISR(void)
 *
 * Include: Tracking.h
 *
 * Description: Acts as the Interrupt Service Routine for the Tracking module
 *              Not currently implemented
 *
 * Arguments: None
 *
 * Returns: None
 *************************************************************************/
extern void trackingISR(void);

#define TRACK_H
#endif