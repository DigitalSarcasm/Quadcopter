#ifndef _ULTRASN_CPP
#define _ULTRASN_CPP

#include <wirinPi.h>
#include <sys/time.h>
#include <unistd.h>

timeval TIMEOUT = {0, 1400}; //default timeout is 0.014seconds because the sensor maxs out at 5 meters
int TIMEOUTLIMIT = 3;
int AVGRATE = 3;
int TRIGGER = 4; //default pin is pin16
int ECHO = 5; //default pin is pin18

/*
 * wiringpiSetup should already be run
 *
 */
void setPin(int trig = TRIGGER, int echo = ECHO);


/*
 * wiringpiSetup should already be run
 * 
 */
double getDistance(iint avgRate = AVGRATE, timeval& timeout = TIMEOUT, int timeOutLimit = TIMEOUTLIMIT);

#endif //_ULTRASN_CPP
