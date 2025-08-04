//=========================================================================
// commands.h
// 
// An interface for the RM3100 3-axis magnetometer from PNI Sensor Corp.
// 
// Author:      David Witten, KD0EAG
// Date:        May 27,2025
// License:     GPL 3.0
// Note:        
//              
//              
//=========================================================================
#ifndef SWXCOMMANDS_h
#define SWXCOMMANDS_h

#include "main.h"

#define USE_RGPIO       FALSE
#define USE_LGPIO       TRUE
#define USE_PIGPIO      FALSE
#define USE_PIGPIO_IF2  FALSE
#define USE_I2CFILES    FALSE

#define PI_INPUT        0
#define PI_OUTPUT       1

// #if USE_I2C
    #if(USE_PIGPIO)
        #include <pigpio.h>
    #elif(USE_PIGPIO_IF2)
        #include <pigpiod_if2.h>
        int  init_IO();
        void terminate_IO(volatile ctlList *p);
        void verifySensor(volatile ctlList *p);
        int  readSensor(volatile ctlList *ctl);
        char *formatOutput(volatile ctlList *, char *outBuf);
        int  waitForRequest(volatile ctlList *);
    #elif(USE_RGPIO)
        #include <rgpio.h>
    #elif(USE_I2CFILES)
        #warning Using Linux FILE functionality for I2C/GPIO.
    #else
        #warning NO I2C/GPIO library defined!
    #endif // USE_I2CFILES
// #endif

#endif //SWXCOMMANDS_h            

