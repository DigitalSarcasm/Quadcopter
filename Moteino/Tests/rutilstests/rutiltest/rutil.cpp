#ifndef RUTIL_CPP
#define RUTIL_CPP

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
	if(stopTime != startTime)
		return millis() - startTime;
	else
		return stopTime - startTime;
}



//////////////////////Packet Object

//constructor for empty packet object
Packet::Packet(){
	overhead = 0;
//	for(int i=0; i<PACKETSIZE; i++)
//		data[i]=0;
	dataLength = 0;
	priority = 0;
}

//constructor for Packet with prebuilt overhead byte
Packet::Packet(const byte& overhead, byte* data, const byte& dataLength, const byte& priority){
	this->overhead = overhead;
	for(int i=0; i<dataLength; i++)
		this->data[i] = data[i];
	this->dataLength = dataLength;
	this->priority = priority;
}

//constructor for Packet that builds overhead byte
Packet::Packet(const byte& ptype, const byte& meta, byte* data, const byte& dataLength, const byte& priority){
	this->overhead = makeOverhead(ptype, meta);
	for(int i=0; i<dataLength; i++)
		this->data[i] = data[i];
	this->dataLength = dataLength;
	this->priority = priority;
}

//return data array in packet
byte* Packet::getData(){
	return data;
}

//copies data array from packet into another array
//Must state the segment of the original data array to copy, size cannot be larget than original array
byte Packet::getData(byte* buffer, const byte& size){
	if(size > dataLength)
		return 0;
		
	for(int i=0; i<size; i++)
		buffer[i] = data[i];
	return 1;
}

//Sets the data array in packet, changes the size variable
byte Packet::setData(byte* data, const byte& size){
	if(size > dataLength)
		return 0;
	
	for(int i=0; i< size; i++)
		this->data[i] = data[i];
	this->dataLength = size;
	return 1;
}

//returns overhead byte in packet
byte Packet::getOverhead(){
	return overhead;
}

//sets overhead byte in packet using pre-build overhead byte
void Packet::setOverhead(const byte& overhead){
	this->overhead = overhead;
}

//sets overhead byte in packet using type and meta
byte Packet::setOverhead(const byte& ptype, const byte& meta){
	if( (ptype > TYPES -1) || (meta > METAS -1))
		return 0;
		
	this->overhead = makeOverhead(ptype, meta);
	return 1;
}

//returns type of the packet (using the overhead byte)
byte Packet::getType(){
	return getPacketType(overhead);
}

//sets type of the overhead byte, keeps the meta data
byte Packet::setType(byte ptype){
	//check that type only has the first 3 bits set (0->8)
	if(ptype > TYPES-1)
		return 0;
	ptype = ptype << 5;	//new type bits
	overhead = overhead & B00011111; //mask old type bits
	overhead = overhead | ptype;	//add new type bits to ovehead
	return 1;
}

//returns meta of the packet (using the overhead byte)
byte Packet::getMeta(){
	return getPacketMeta(overhead);
}

//sets the meta of the overhead byte, keeps the type data
byte Packet::setMeta(byte meta){
	//check if meta is only the first 5 bits set (0->31)
	if(meta > METAS-1)
		return 0;
	overhead = overhead & B11100000; //mask last meta bits
	overhead = overhead | meta;	//add new meta bits
	return 1;
}

//get priority of packet
byte Packet::getPriority(){
	return priority;
}

//get priority of packet
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




#endif //RUTIL_CPP