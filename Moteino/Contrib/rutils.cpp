#include "rutil.h"
//#include "Arduino.h"

//////////////////////////Timer object 

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



//////////////////////Packet Object

//constructor for empty packet object
Packet::Packet(){
	overhead = 0;
	for(int i=0; i<PACKETSIZE; i++)
		data[i]=0;
	dataLength = 0;
	priority = 0;
}

Packet::Packet(const byte& overhead, byte* data, const byte& dataLength, const byte& priority){
	this->overhead = overhead;
	for(int i=0; i<dataLength; i++)
		this->data[i] = data[i];
	this->dataLength = dataLength;
	this->priority = priority;
}

Packet::Packet(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority){
	this->overhead = makeOverhead(ptype, meta);
	for(int i=0; i<dataLength; i++)
		this->data[i] = data[i];
	this->dataLength = dataLength;
	this->priority = priority;
}


byte* Packet::getData(){
	return data;
}

byte Packet::getData(byte* buffer, byte size){
	if(size > dataLength)
		return 0;
		
	for(int i=0; i<size; i++)
		buffer[i] = data[i];
	return 1;
}

byte Packet::setData(byte* data, const byte& size){
	if(size > dataLength)
		return 0;
	
	for(int i=0; i< size; i++)
		this->data[i] = data[i];
	this->dataLength = size;
	return 1;
}

byte Packet::getOverhead(){
	return overhead;
}

void Packet::setOverhead(const byte& overhead){
	this->overhead = overhead;
}

byte Packet::setOverhead(const byte& ptype, const byte& meta){
	if( (ptype > TYPES -1) || (meta > METAS -1))
		return 0;
		
	this->overhead = makeOverhead(ptype, meta);
	return 1;
}

byte Packet::getType(){
	return getPacketType(overhead);
}

byte Packet::setType(byte ptype){
	//check that type only has the first 3 bits set (0->8)
	if(ptype > TYPES-1)
		return 0;
	ptype = ptype << 5;	//new type bits
	overhead = overhead & B00011111; //mask old type bits
	overhead = overhead | ptype;	//add new type bits to ovehead
	return 1;
}

byte Packet::getMeta(){
	return getPacketMeta(overhead);
}

byte Packet::setMeta(byte meta){
	//check if meta is only the first 5 bits set (0->31)
	if(meta > METAS-1)
		return 0;
	overhead = overhead & B11100000; //mask last meta bits
	overhead = overhead | meta;	//add new meta bits
	return 1;
}

byte Packet::getPriority(){
	return priority;
}

void Packet::setPriority(const byte& priority){
	this->priority = priority;
}

//Makes overhead byte from type and meta bytes. Uses bit masking and adding
//returns EMPTYPACKET for invalid overhead
byte Packet::makeOverhead(const byte& ptype, byte meta){
	byte overhead = B00000000;
	
	if((ptype > TYPES-1) || (meta > METAS-1) )
		return EMPTYPACKET;
	
	overhead = overhead | ptype;	//get type bits
	overhead = overhead << 5;		//shift type bits
	meta = meta & B00011111;		//mask the first 3 bits of meta
	overhead = overhead | meta;	//get meta data bits

	return overhead;
}

//Get type value from a overhead byte
byte Packet::getPacketType(const byte& overhead){
	byte typeMask = B11100000;
	byte ptype = overhead & typeMask;
	ptype = ptype >> 5;	//c++ does not have built in circular shift, we will use this instead
	return ptype;
}

//Gets meta value from a overhead byte
byte Packet::getPacketMeta(const byte& overhead){
	byte typeMask = B00011111;
	byte data = overhead & typeMask;
	return data;
}


///////////////PacketQueue

template<int arraySize>
int PacketQueue<arraySize>::findEmpty(){
	for(byte i<0; i<size; i++){
		if(collection[i].getOverhead() == 0)
			return i;
	}
	else
		return -1;
}


template<int arraySize>
PacketQueue<arraySize>::PacketQueue(){
	head = tail = 0;
}

template<int arraySize>
byte PacketQueue<arraySize>::queue(const Packet& pack){
	if(head == tail)	//if the lookup table is full or empty
		return 0;

	byte index = findEmpty();	//find empty index in queue
	collection[index] = pack;	//copy packet
	if(tail >= size)
		tail = tail % size;
	lookup[tail] = index;
	return 1;
}

template<int arraySize>
byte PacketQueue<arraySize>::queue(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority){
	//TODO should separate the data into multiple packets with proper overhead
	return queue(Packet(ptype, meta, data, dataLength, priority));
}


template<int arraySize>
Packet PacketQueue<arraySize>::dequeue(){
	byte index;
	
	if(head == tail)		//if the lookup table is full or empty
		return Packet();	//return empty packet
	
	if(tail==0 && head!=0)
		index = size-1;
	else
		index = tail-1;
	
	Packet temp = collection[lookup[index]];
	tail = index;
	collection[lookup[index]].setOverhead(EMPTYPACKET);
	
	return temp;
}
