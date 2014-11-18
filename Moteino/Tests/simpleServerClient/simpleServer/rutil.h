#ifndef RUTILS_H
#define RUTILS_H
//Timer object

#include "Arduino.h"

class Timer{
private:
	unsigned long startTime;
	unsigned long stopTime;
	byte t;
	
protected:

public:
	Timer();	
	void start();
	unsigned long stop();
	unsigned long getTime();
	
};

#endif //RUTILS_H