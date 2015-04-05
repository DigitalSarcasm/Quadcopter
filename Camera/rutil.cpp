#ifndef RUTIL_CPP
#define RUTIL_CPP

#include "rutil.h"
//#include "Arduino.h"

//////////////////////////Timer object 

Timer::Timer(){

    startCount.tv_sec = startCount.tv_usec = 0;
    endCount.tv_sec = endCount.tv_usec = 0;

    stopped = 0;
    startTimeInMicroSec = 0;
    endTimeInMicroSec = 0;
}

void Timer::start()
{
    stopped = 0; // reset stop flag
    gettimeofday(&startCount, 0);
}

void Timer::stop()
{
    stopped = 1; // set timer stopped flag
    gettimeofday(&endCount, 0);
}

double Timer::getElapsedTimeInMicroSec()
{
    if(!stopped)
        gettimeofday(&endCount, 0);

    startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
    endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
    return endTimeInMicroSec - startTimeInMicroSec;
}

double Timer::getElapsedTimeInMilliSec()
{
    return this->getElapsedTimeInMicroSec() * 0.001;
}

double Timer::getElapsedTimeInSec()
{
    return this->getElapsedTimeInMicroSec() * 0.000001;
}

double Timer::getElapsedTime()
{
    return this->getElapsedTimeInSec();
}


//////////////////////Packet Object

//constructor for empty packet object
Packet::Packet(){
//	for(int i=0; i<PACKETSIZE; i++)
//		data[i]=0;
	data[0] = 0;	//overhead
	dataLength = 0;
	priority = 0;
}

//constructor for Packet with prebuilt overhead byte
Packet::Packet(const byte& overhead, byte* cdata, const byte& dataLength, const byte& priority){
	data[0] = overhead;
	for(int i=1; i<=dataLength; i++) //copy into data packet index 1 to 60 (60bytes)
		this->data[i] = cdata[i-1];
	this->dataLength = dataLength;	//including overhead
	this->priority = priority;
}

//constructor for Packet that builds overhead byte
Packet::Packet(const byte& ptype, const byte& meta, byte* cdata, const byte& dataLength, const byte& priority){
	data[0] = makeOverhead(ptype, meta);
	for(int i=1; i<=dataLength; i++) 
		this->data[i] = cdata[i-1];
	this->dataLength = dataLength;
	this->priority = priority;
}

//copy constructor
Packet::Packet(const Packet& p){
	dataLength = p.dataLength;
	priority = p.priority;
	//copy all data, including overhead
	for(int i=0; i<dataLength+1; i++)	//as the overhead is not accounted for in the datalength
		data[i] = p.data[i];
}

void Packet::operator=(const Packet& p){
	if(this == &p)
		return;
	
	dataLength = p.dataLength;
	priority = p.priority;
	
	for(int i=0; i<dataLength+1; i++)
		data[i] = p.data[i];
}

bool Packet::operator==(const Packet& p){
	if(this == &p)
		return true;
	
	//specical case, the packet is removed from use and its overhead is set to 0 but its other data is not changed
	//this packet is now a empty packet and must only check the overhead
	if(data[0] == 0 && p.data[0] == 0)
		return true;
	
	if(data[0] != p.data[0] || dataLength != p.dataLength || priority != p.priority)
		return false;
	
	//checks the first x amount of bytes in the data to see if the data is the same
	for(int i=1; i< DATACHECK; i++){
		if(data[i] != p.data[i])
			return false;
	}
	
	return true;
}

//return data array in packet
byte* Packet::getData(){
	return data+1;
}

//returns databuffer with overhead
byte* Packet::getPacket(){
	return data;
}

//copies data array from packet into another array    	NOT TESTED
//Must state the segment of the original data array to copy, size cannot be larget than original array
byte Packet::getData(byte* buffer, const byte& size){
	if(size > dataLength)
		return 0;
		
	for(int i=0; i<size; i++)
		buffer[i] = data[i];
	return 1;
}

//Sets the data array in packet, sets the packet size as well
byte Packet::setData(byte* cdata, const byte& size){
	if(size > PACKETSIZE-1)
		return 0;
	
	for(int i=1; i<=size; i++)
		this->data[i] = cdata[i-1];
	this->dataLength = size;
	return 1;
}

byte Packet::setLength(const byte& len){
	if(len > PACKETSIZE-1)
		return 0;
	this->dataLength = len;
}

//returns overhead byte in packet
byte Packet::getOverhead(){
	return data[0];
}

//sets overhead byte in packet using pre-build overhead byte
void Packet::setOverhead(const byte& overhead){
	data[0] = overhead;
}

//sets overhead byte in packet using type and meta
byte Packet::setOverhead(const byte& ptype, const byte& meta){
	if( (ptype > TYPES -1) || (meta > METAS -1))
		return 0;
		
	data[0] = makeOverhead(ptype, meta);
	return 1;
}

//returns type of the packet (using the overhead byte)
byte Packet::getType(){
	return getPacketType(data[0]);
}

//sets type of the overhead byte, keeps the meta data
byte Packet::setType(byte ptype){
	//check that type only has the first 3 bits set (0->8)
	if(ptype > TYPES-1)
		return 0;
	ptype = ptype << 5;	//new type bits
	data[0] = data[0] & 31; //B00011111 //mask old type bits
	data[0] = data[0] | ptype;	//add new type bits to ovehead
	return 1;
}

//returns meta of the packet (using the overhead byte)
byte Packet::getMeta(){
	return getPacketMeta(data[0]);
}

//sets the meta of the overhead byte, keeps the type data
byte Packet::setMeta(byte meta){
	//check if meta is only the first 5 bits set (0->31)
	if(meta > METAS-1)
		return 0;
	data[0] = data[0] & 224; //B11100000; //mask last meta bits
	data[0] = data[0] | meta;	//add new meta bits
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

//pads the packet with 0 values up to PACKETSIZE
void Packet::pad(){
	if(dataLength < PACKETSIZE){
		for(int i=dataLength+1; i<PACKETSIZE; i++){
			data[i] = 0;
		}
		dataLength = PACKETSIZE - 1;
	}
}

//Makes overhead byte from type and meta bytes. Uses bit masking and adding
//returns EMPTYPACKET for invalid overhead
byte Packet::makeOverhead(const byte& ptype, byte meta){
	byte overhead = 0; //B00000000
	
	if((ptype > TYPES-1) || (meta > METAS-1) )
		return EPACKET;
	
	overhead = overhead | ptype;	//get type bits
	overhead = overhead << 5;		//shift type bits
	meta = meta & 31; //B00011111		//mask the first 3 bits of meta
	overhead = overhead | meta;	//get meta data bits

	return overhead;
}

//Get type value from a overhead byte
byte Packet::getPacketType(const byte& overhead){
	byte typeMask = 224; //B11100000
	byte ptype = overhead & typeMask;
	ptype = ptype >> 5;	//c++ does not have built in circular shift, we will use this instead
	return ptype;
}

//Gets meta value from a overhead byte
byte Packet::getPacketMeta(const byte& overhead){
	byte typeMask = 31; //B00011111
	byte data = overhead & typeMask;
	return data;
}




#endif //RUTIL_CPP