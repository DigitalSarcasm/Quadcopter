#ifndef _ULTRASN_H
#define _ULTRASN_H

#include <wiringPi.h>
#include <sys/time.h>
#include <unistd.h>

extern timeval TIMEOUT;
extern int TIMEOUTLIMIT ;
extern int AVGRATE;
extern int TRIGGER;
extern int ECHO;

/*
 * wiringpiSetup should already be run
 *
 */
void setPin(int trig = TRIGGER, int echo = ECHO);


/*
 * wiringpiSetup should already be run
 * 
 */
double getDistance(int avgRate = AVGRATE, timeval& timeout = TIMEOUT, int timeOutLimit = TIMEOUTLIMIT);

#endif //_ULTRASN_H
