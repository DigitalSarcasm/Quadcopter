#ifndef RUTILS_H
#define RUTILS_H

#include "Arduino.h"
#include <exception.h>

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
	byte overhead;
	byte data[PACKETSIZE];
	byte dataLength;
	byte priority;
public:
	Packet();
	Packet(const byte& overhead, byte* data, const byte& dataLength, const byte& priority = 0);
	Packet(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority = 0);

	
	byte* getData();
	void getData(byte* buffer, byte size);
	void setData(byte* data, const byte& size);
	
	byte length(){return dataLength;}
	
	byte getOverhead();
	void setOverhead(const byte& overhead);
	void setOverhead(const byte& ptype, const byte& meta);
	
	byte getType();
	void setType(byte ptype);
	byte getMeta();
	void setMeta(byte meta);
	
	byte getPriority();
	void setPriority(const byte& Priority);
	
	static byte makeOverhead(const byte& ptype, byte meta);
	static byte getPacketType(const byte& overhead);
	static byte getPacketMeta(const byte& overhead);
};


#endif //RUTILS_H