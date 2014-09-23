/* 
 * File:   PanTilt.h
 * Author: Grant
 *
 * Description: This file contains the public interface for the PanTile module
 *
 * Created on 16 September 2014, 6:33 PM
 */

//True if Pan ISR concerns pan tilt module
#define PAN_TILT_ISR    0

//External declarations of public access functions
extern void move(Direction destination);
extern Direction getDir(void);
extern void calibratePanTilt(Direction reference);
extern Direction rawDir(void);
