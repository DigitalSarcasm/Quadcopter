#ifndef RUTILS_H
#define RUTILS_H

#include "Arduino.h"
#include <exception.h>
#include <StandardCplusplus.h>
#include <vector>

#define PACKETSIZE 60

#define QUEUESIZE 5;

#define EMPTYPACKET 0;

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
	void getData(byte* buffer, byte size);	//not tested
	void setData(byte* data, const byte& size);
	
	byte length(){return dataLength;}
	
	byte getOverhead();
	void setOverhead(const byte& overhead);	//not tested
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


//PacketQueue
//Array list that behaves like linked list
template<int arraySize=QUEUESIZE>
class PacketQueue{
protected:
	Packet collection[arraySize];
	byte lookup[arraySize];			//lookup table
	byte size = arraySize;
	byte head, tail;			//head and tail of collection
	
	int findEmpty();
public:
	PacketQueue();
	
	int queue(const Packet& pack);
	int queue(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority = 0);
	Packet dequeue();
	
	//TODO
	//void smartQueue(); //compares packets from multiple clients and arranges the packets as to 
						//allow all clients equal comm. time
};


#endif //RUTILS_H