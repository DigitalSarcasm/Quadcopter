#include "rutil.h"
#include "Arduino.h"

//Timer object 

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


//Packet Object

//TODO test
byte Packet::makeMeta(const byte& type, byte meta){
	byte nMetaData = B11111111;
	
	nMetaData = nMetaData & type;	//get type bits
	nMetaData = nMetaData << 5;		//shift type bits
	nMetaData = nMetaData | B00011111;	//mask the missing 1 for the last 5 bits
	meta = meta | B11100000;				//mask the first 3 bits of meta
	nMetaData = nMetaData & meta;	//get meta data bits

	return nMetaData;
}