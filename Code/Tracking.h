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
 * /todo {Prediction algorithm}
 *
 * Created on 15 September 2014, 1:41 PM
 ******************************************************************************/

//Ensure that there is only 1 inclusion of this file in the preprocessor execution
#ifndef TRACK_H

//#define TRACK_INT (CCP2_INT)
#define TRACK_INT 0

//External declarations for the public access functions
extern void configureTracking(void);
extern void search(systemState *state);
extern TrackingData track(systemState *state);
extern void trackingISR(void);

#define TRACK_H
#endif