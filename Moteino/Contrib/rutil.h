#ifndef RUTIL_H
#define RUTIL_H

#include "Arduino.h"
//#include <exception.h>
//#include <StandardCplusplus.h>
//#include <vector>

#define PACKETSIZE 61

#define QUEUESIZE 5
#define LISTSIZE 5
#define TYPES 8
#define METAS 32
#define DATACHECK 10

//packet types
#define EPACKET 0
#define REQPACKET 1
#define DPACKET 2
#define HPACKET 6
#define EMGPACKET 7

//metas
//request packet
#define HSREQ 0	//handshake request
#define REQREQ 1 //request-request
#define TXREQ 2	//transmission request
#define NOREQ 3	//no request
#define DREQ 4	//data request
#define RECREQ 5	//reception request

//data packet
#define DCNTMAX 15 //data counter max value		//not needed anymore as the packets keep track of their own packet number and which ones are the last



////////////Timer object declaration
//timer object, keeps time in MS
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
	byte data[PACKETSIZE];	//data buffer, includes overhead bytes as index 0
	byte dataLength;	//data buffers length, this is not sent as it will already be sent in the RFM69 function
	byte priority;		//priority of packet, currently unused 
public:
	Packet();	//constructor for empty packet
	Packet(const byte& overhead, byte* data, const byte& dataLength, const byte& priority = 0); //constructor for packet knowing the ovehead byte
	Packet(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority);	//constructor for packet knowing type and meta data, priority is mandatory as it can be confused with the previous constructor
	Packet(const Packet& p);
	
	void operator=(const Packet& p);
	bool operator==(const Packet& p);
	
	byte* getData();	//get pointer to data buffer
	byte* getPacket();	//returns databuffer with overhead
	byte getData(byte* buffer, const byte& size);	//not tested //copy data buffer to another buffer
	byte setData(byte* data, const byte& size);	//set data buffer
	
	byte length(){return dataLength;}	//return length of data buffer
	byte plength(){return dataLength+1;}	//returns length of data buffer + overhead
	byte setLength(const byte& len);
	
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
//the packets are stored in the collection in a random order but the lookup table to them can be changed easily (byte array)
//the lookup table on the otherhand is a circular list
//this is because changing the order of packets is heavy compared to changing the order in the lookuptable
template<int arraySize=QUEUESIZE>
class PacketQueue{
protected:
	Packet collection[arraySize];	//collection of packets, order not guarenteed
	byte lookup[arraySize];			//lookup table for packets in collection
	byte size, maxSize;			//size and maxsize of lookup table and collection array
	byte head, tail;			//head and tail of collection
	
	int findEmpty();			//find first empty index in collection array
public:
	PacketQueue();
	PacketQueue(const PacketQueue& pq);
	
	void operator=(const PacketQueue& pq);
	
	byte queue(const Packet& pack);
	Packet* queueDummy();
	byte queue(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority = 0);
	Packet dequeue();
	
	byte length(){return size;}
	byte maxLength(){return maxSize;}
	byte full(){return (size == maxSize);}
	Packet* peek(){return &collection[lookup[head]];}
	Packet* peek(const byte& index);	
	byte rollover();	
	
//	byte consecDataPackets();	
	
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
	byte maxSize, size;
public:
	ClientList();
	
	byte length(){return size;}
	
	byte getClient(const byte& index);
	byte getRequest(const byte& index);
	void toggleRequest(const byte& index);
	
	byte add(const byte& client);
	byte remove(const byte& client);
	int searchClient(const byte& client);
};



///////////////PacketQueue

/*
 * Finds first available spot in the collection. A default packet (overhead = 0) means that the index is empty
 * An default packet is not necessarly empty, just that it has been removed from use (dequeue)
 * returns an int on success
 * else returns -1 for failure
 */
template<int ARRAYSIZE>
int PacketQueue<ARRAYSIZE>::findEmpty(){
	for(byte i=0; i<maxSize; i++){
		if(collection[i].getOverhead() == EPACKET)
			return i;
	}
	return -1;
}


template<int ARRAYSIZE>
PacketQueue<ARRAYSIZE>::PacketQueue(){
	head = tail = 0;
	size = 0;
	maxSize = ARRAYSIZE;
}

//copy constructor should never be used with a packetqueue that has a different arraysize
//not tested
template<int ARRAYSIZE>
PacketQueue<ARRAYSIZE>::PacketQueue(const PacketQueue& pq){
	head = pq.head;
	tail = pq.tail;
	size = pq.size;
	maxSize = pq.maxSize;
	
	for(int i=0; i<maxSize; i++){
		collection[i] = pq.collection[i];
		lookup[i] = pq.lookup[i];
	}
}

//assignment operator should never be used with a packetqueue that has a different arraysize
//not tested
template<int ARRAYSIZE>
void PacketQueue<ARRAYSIZE>::operator=(const PacketQueue& pq){
	head = pq.head;
	tail = pq.tail;
	size = pq.size;
	maxSize = pq.maxSize;
	
	for(int i=0; i<maxSize; i++){
		collection[i] = pq.collection[i];
		lookup[i] = pq.lookup[i];
	}
}


template<int ARRAYSIZE>
byte PacketQueue<ARRAYSIZE>::queue(const Packet& pack){
	if(head == tail && size != 0) //if the lookup table is full
		return 0;

	byte index = findEmpty();	//find empty index in queue
	
	collection[index] = pack;	//copy packet
	lookup[tail] = index;		//add index to lookup table
	tail++;						
	if(tail >= maxSize)			//compute next tail position
		tail = tail % maxSize;
	
	size++;
	return 1;
}

//queues empty packet and returns a reference to it
//this leaves the responsibility of filling up the packet to the user
//this allows to queue up packets without the need for temporary packet objects
//returns 1 for success, else it returns 0
template<int ARRAYSIZE>
Packet* PacketQueue<ARRAYSIZE>::queueDummy(){
	if(head == tail && size != 0) //if the lookup table is full
		return 0;

	byte index = findEmpty();	//find empty index in queue
	
	collection[index] = Packet(0,1,0,0,0);	//copy in packet with a 1 overhead
	lookup[tail] = index;		//add index to lookup table
	tail++;						
	if(tail >= maxSize)			//compute next tail position
		tail = tail % maxSize;
	
	size++;
	return &collection[index]; //return pointer to dummy
}

template<int ARRAYSIZE>
byte PacketQueue<ARRAYSIZE>::queue(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority){
	//TODO should separate the data into multiple packets with proper overhead when the datalenght is bigger PACKETSIZE
	return queue(Packet(ptype, meta, data, dataLength, priority));
}


template<int ARRAYSIZE>
Packet PacketQueue<ARRAYSIZE>::dequeue(){
	if(head == tail && size == 0)		//if the lookup table is empty
		return Packet();			//return default packet
	
	Packet temp = collection[lookup[head]];
	collection[lookup[head]].setOverhead(EPACKET);
	
	head++;
	if(head >= maxSize)			//compute next tail position
		head = head % maxSize;
		
	size--;
	return temp;
}

//peeks the Nth item in the queue, returns Empty Packet if the index is bigger than the size of the queue
template<int ARRAYSIZE>
Packet* PacketQueue<ARRAYSIZE>::peek(const byte& index){
	if(index > size || size == 0)
		return 0;
		
	return &collection[lookup[(head+index)%maxSize]];
}

template<int ARRAYSIZE>
byte PacketQueue<ARRAYSIZE>::rollover(){
	if(size == 0)
		return 0;
		
	byte index = lookup[head];
	head++;
	if(head >= maxSize)
		head = head % maxSize;
	lookup[tail] = index;
	tail++;
	if(tail >= maxSize)
		tail = tail % maxSize;
	return 1;
}

//counts the number of consecutive data packets, these is data that has been separated into multiple packets
//returns 0 if the queue is empty, if the head of the queue is not a data packet
//else returns the number of consecutive data Packets
//template<int ARRAYSIZE>
//byte PacketQueue<ARRAYSIZE>::consecDataPackets(){
//	int csize = 1;
//	if(size == 0)
//		return 0;
//	
//	if(collection[lookup[head]].getType() != DPACKET)
//		return 0;
//		
//	//start at 1 as the head of the queue has already been checked 
//	for(int i=1; i<size; i++){
//		Packet* p = collection[lookup[head+i]];
//		//looks for last packet meta. if one is found, the number of packets to it is returned
//		//else if none is found, then the packet of the group has not been processed yet and 
//		if(p->getType() == DPACKET){
//			if(p->getMeta() > DCNTMAX)
//				break;
//				
//		}
//		else
//			break;
//			
//		csize++;
//	}
//	return csize;
//}

////////////////////////////////ClientList

template<int ARRAYSIZE>
ClientList<ARRAYSIZE>::ClientList(){
	size = 0;
	maxSize = ARRAYSIZE;
}

template<int ARRAYSIZE>
byte ClientList<ARRAYSIZE>::getClient(const byte& index){
	return clientList[index];
}


template<int ARRAYSIZE>
byte ClientList<ARRAYSIZE>::getRequest(const byte& index){
	return hasRequest[index];
}

//toggles request for that index
template<int ARRAYSIZE>
void ClientList<ARRAYSIZE>::toggleRequest(const byte& index){
	hasRequest[index] = !hasRequest[index];	//toggle request
}

//returns 1 if successful, else returns 0 if the client is already in list or the list is full
template<int ARRAYSIZE>
byte ClientList<ARRAYSIZE>::add(const byte& client){
	if(size == maxSize)	//list is full
		return 0;
	
	//test if the client is already added
	for(int i=0; i<size; i++){
		if(clientList[i] == client)
			return 0;
	}
	
	clientList[size] = client;
	hasRequest[size] = false;
	size++;
	return 1;
}

//returns 1 if the client was removed, else returns 0 if not found
template<int ARRAYSIZE>
byte ClientList<ARRAYSIZE>::remove(const byte& client){
	
	if(size == 0)	//list is empty
		return 0;
	
	for(int i=0; i<size; i++){		//find client in list
		if(clientList[i] == client){	//if client found
			for(int j=i; j<size-1; j++){	//move every client back one index
				clientList[j] = clientList[j+1];
				hasRequest[j] = hasRequest[j+1];
			}
			size--;					
			return 1;
		}
	}
	return 0;	//client was not found in list
}


template<int ARRAYSIZE>
int ClientList<ARRAYSIZE>::searchClient(const byte& client){
	if(size == 0)
		return -1;
		
	for(int i=0; i<size; i++){
		if(clientList[i] == client)
			return i;
	}
	
	return -1;
}



//#include "rutil.cpp"
#endif //RUTIL_H