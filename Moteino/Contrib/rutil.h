#ifndef RUTILS_H
#define RUTILS_H

#include "Arduino.h"
#include <exception.h>
//#include <StandardCplusplus.h>
//#include <vector>

#define PACKETSIZE 60

#define QUEUESIZE 5;
#define TYPES 8
#define METAS 32

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

/*
 * Packet object, holds the packet overhead and the data buffer and its length
 * up to 61 byte packet (overhead (1) + data (MAX 60))
 */
class Packet{
protected:
	byte overhead;		//Overhead byte, includes type and metadata
	byte data[PACKETSIZE];	//data buffer
	byte dataLength;	//data buffers length
	byte priority;		//priority of packet, currently unused 
public:
	Packet();	//cosntructor for empty packet
	Packet(const byte& overhead, byte* data, const byte& dataLength, const byte& priority = 0); //constructor for packet knowing the ovehead byte
	Packet(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority = 0);	//constructor for packet knowing type and meta data

	
	byte* getData();	//get pointer to data buffer
	byte getData(byte* buffer, byte size);	//not tested //copy data buffer to another buffer
	byte setData(byte* data, const byte& size);	//set data buffer
	
	byte length(){return dataLength;}	//return length of data buffer
	
	byte getOverhead();	//get overhead byte
	void setOverhead(const byte& overhead);	//not tested //set overhead byte
	void setOverhead(const byte& ptype, const byte& meta);	//set overhead byte using type and meta
	
	byte getType();
	byte setType(byte ptype);
	byte getMeta();
	byte setMeta(byte meta);
	
	byte getPriority();
	void setPriority(const byte& Priority);
	
	static byte makeOverhead(const byte& ptype, byte meta); //make overhead byte using type and meta
	static byte getPacketType(const byte& overhead); //get packet type of a overhead byte
	static byte getPacketMeta(const byte& overhead); //get packet meta of a overhead byte
};


//PacketQueue
//Array list that behaves like linked list
template<int arraySize=QUEUESIZE>
class PacketQueue{
protected:
	Packet collection[arraySize];	//collection of packets, order not guarenteed
	byte lookup[arraySize];			//lookup table for packets in collection
	byte size = arraySize;			//size of lookup table and collection array
	byte head, tail;				//head and tail of collection
	
	int findEmpty();				//find first empty index in collection array
public:
	PacketQueue();
	
	byte queue(const Packet& pack);
	byte queue(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority = 0);
	Packet dequeue();
	
	//TODO
	//void smartQueue(); //compares packets from multiple clients and arranges the packets as to 
						//allow all clients equal comm. time and base it off 
};


#endif //RUTILS_H