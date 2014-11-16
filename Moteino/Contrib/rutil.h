#ifndef RUTILS_H
#define RUTILS_H

#include "Arduino.h"

#define PACKETSIZE 60

//Timer object declaration

class Timer{
protected:
	unsigned long startTime;
	unsigned long stopTime;
public:
	Timer();	
	void start();
	unsigned long stop();
	unsigned long getTime();
};


//Packet object declaration

class Packet{
protected:
	byte metaData;
	byte data[PACKETSIZE];
	byte dataLength;
	byte priority;
public:
	Packet();
	Packet(const byte& packetType, byte* data, const& byte dataLength, const byte& priority = 0);
	
	byte* getData();
	void setData(void* nData, const int& size);
	byte getMeta();
	void setMeta(const byte& nMeta);
	void setMeta(const byte& type, const byte& meta);
	byte getPriority();
	void setPriority(const byte& nPriority);
	
	byte makeMeta(const byte& type, byte meta);
};


byte getPacketType(const byte& ptype)
{
	byte typeMask = B11100000;
	byte type = ptype & typeMask;
	type = type >> 5;	//c++ does not have built in circular shift, we will use this instead
	return type;
}

byte getPacketData(const byte& ptype)
{
	byte typeMask = B00011111;
	byte data = ptype & typeMask;
	return data;
}

#endif //RUTILS_H