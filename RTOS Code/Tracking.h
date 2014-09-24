/* 
 * File:   Tracking.h
 * Author: Grant
 *
 * Description: Public interface function for the Tracking Module
 *
 * Created on 15 September 2014, 1:41 PM
 */

#define TRACK_INT (CCP2_INT)

//External declarations for the public access functions
extern void configBase(void);
extern void search(void);
extern TrackingData edge(void);
extern void trackingISR(void);

