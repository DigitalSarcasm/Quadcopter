#include "rutil.h"
#include "Arduino.h"

Timer::Timer(){
	startTime = 0;
	stopTime = 0;
}

void Timer::start(){
	startTime = millis();
	stopTime = 0;
}

unsigned long Timer::stop(){
	stopTime = millis();
	return (stopTime - startTime);
}

unsigned long Timer::getTime(){
	if(stopTime == 0)
		return millis() - startTime;
	else
		return stopTime - startTime;
}