/* 
 * File:   Tracking.h
 * Author: Grant
 *
 * Description: Public interface function for the Tracking Module
 *
 * Created on 15 September 2014, 1:41 PM
 */

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