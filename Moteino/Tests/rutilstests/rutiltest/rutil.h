#ifndef RUTIL_H
#define RUTIL_H

#include "Arduino.h"
//#include <exception.h>
//#include <StandardCplusplus.h>
//#include <vector>

#define PACKETSIZE 60

#define QUEUESIZE 5
#define LISTSIZE 5
#define TYPES 8
#define METAS 32

#define EMPTYPACKET 0

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
	byte dataLength;	//data buffers length, this is not sent as it will already be sent in the RFM69 function
	byte priority;		//priority of packet, currently unused 
public:
	Packet();	//cosntructor for empty packet
	Packet(const byte& overhead, byte* data, const byte& dataLength, const byte& priority = 0); //constructor for packet knowing the ovehead byte
	Packet(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority = 0);	//constructor for packet knowing type and meta data

	
	byte* getData();	//get pointer to data buffer
	byte getData(byte* buffer, const byte& size);	//not tested //copy data buffer to another buffer
	byte setData(byte* data, const byte& size);	//set data buffer
	
	byte length(){return dataLength;}	//return length of data buffer
	
	byte getOverhead();	//get overhead byte
	void setOverhead(const byte& overhead);	//not tested //set overhead byte
	byte setOverhead(const byte& ptype, const byte& meta);	//set overhead byte using type and meta
	
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
	byte size;			//size of lookup table and collection array
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

//holds list of clients and whether or not they have a requested data transmission
template<int ARRAYSIZE = LISTSIZE>
class ClientList{
protected:
	byte clientList[ARRAYSIZE];
	bool hasRequest[ARRAYSIZE];	//hash table instead of list
	byte maxSize;
	byte size;
public:
	ClientList();
	byte add(byte client);
	byte remove(byte client);
	bool getRequest(byte client);
	void toggleRequest(byte client);
};





///////////////PacketQueue

//template<int ARRAYSIZE>
//int PacketQueue<ARRAYSIZE>::findEmpty(){
//	for(byte i=0; i<size; i++){
//		if(collection[i].getOverhead() == 0)
//			return i;
//	}
//	return -1;
//}
//
//
//template<int ARRAYSIZE>
//PacketQueue<ARRAYSIZE>::PacketQueue(){
//	head = tail = 0;
//	size = ARRAYSIZE;
//}
//
//template<int ARRAYSIZE>
//byte PacketQueue<ARRAYSIZE>::queue(const Packet& pack){
//	if(head == tail)	//if the lookup table is full or empty
//		return 0;
//
//	byte index = findEmpty();	//find empty index in queue
//	collection[index] = pack;	//copy packet
//	if(tail >= size)
//		tail = tail % size;
//	lookup[tail] = index;
//	return 1;
//}
//
//template<int ARRAYSIZE>
//byte PacketQueue<ARRAYSIZE>::queue(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority){
//	//TODO should separate the data into multiple packets with proper overhead
//	return queue(Packet(ptype, meta, data, dataLength, priority));
//}
//
//
//template<int ARRAYSIZE>
//Packet PacketQueue<ARRAYSIZE>::dequeue(){
//	byte index;
//	
//	if(head == tail)		//if the lookup table is full or empty
//		return Packet();	//return empty packet
//	
//	if(tail==0 && head!=0)
//		index = size-1;
//	else
//		index = tail-1;
//	
//	Packet temp = collection[lookup[index]];
//	tail = index;
//	collection[lookup[index]].setOverhead(EMPTYPACKET);
//	
//	return temp;
//}
//
//////////////ClientList
//
//template<int ARRAYSIZE>
//ClientList<ARRAYSIZE>::ClientList(){
//	size = ARRAYSIZE;
//}
//
//template<int ARRAYSIZE>
//byte ClientList<ARRAYSIZE>::add(byte client){
//	//test if the client is already added
//	for(int i=0; i<size; i++){
//		if(clientList[i] == client)
//			return 0;
//	}
//	
//	clientList[size] = client;
//	hasRequest[client] = false;
//	size++;
//}
//
//template<int ARRAYSIZE>
//byte ClientList<ARRAYSIZE>::remove(byte client){
//	for(int i=0; i<size; i++){		//find client in list
//		if(clientList[i] == client){	//if client found
//			for(int j=i; j<size-1; j++){	//move every client back one index
//				clientList[j] = clientList[j+1];
////				hasRequest[j] = hasRequest[j+1];
//			}
//			size--;					
//			return 1;
//		}
//	}
//	return 0;	//client was not found in list
//}
//
//
//template<int ARRAYSIZE>
//bool ClientList<ARRAYSIZE>::getRequest(byte client){
//	return hasRequest[client];
//}
//
//template<int ARRAYSIZE>
//bool ClientList<ARRAYSIZE>::toggleRequest(byte client){
//	hasRequest[client] = !hasRequest[client];	//toggle request
//}

//#include "rutil.cpp"
#endif //RUTIL_H