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

void Packet::getData(byte* buffer, byte size){
	for(int i=0; i<size; i++)
		buffer[i] = data[i];
}

void Packet::setData(byte* data, const byte& size){
	for(int i=0; i< size; i++)
		this->data[i] = data[i];
	this->dataLength = size;
}

byte Packet::getOverhead(){
	return overhead;
}

void Packet::setOverhead(const byte& overhead){
	this->overhead = overhead;
}

void Packet::setOverhead(const byte& ptype, const byte& meta){
	this->overhead = makeOverhead(ptype, meta);
}

byte Packet::getType(){
	return getPacketType(overhead);
}

void Packet::setType(byte ptype){
	//check that type only has the first 3 bits set (0->8)
	ptype = ptype << 5;	//new type bits
	overhead = overhead & B00011111; //mask old type bits
	overhead = overhead | ptype;	//add new type bits to ovehead
}

byte Packet::getMeta(){
	return getPacketMeta(overhead);
}

void Packet::setMeta(byte meta){
	//check if meta is only the first 5 bits set (0->31)
	overhead = overhead & B11100000; //mask last meta bits
	overhead = overhead | meta;	//add new meta bits
}

byte Packet::getPriority(){
	return priority;
}

void Packet::setPriority(const byte& priority){
	this->priority = priority;
}

//Makes overhead byte from type and meta bytes. Uses bit masking and adding
byte Packet::makeOverhead(const byte& ptype, byte meta){
	byte overhead = B00000000;
	
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