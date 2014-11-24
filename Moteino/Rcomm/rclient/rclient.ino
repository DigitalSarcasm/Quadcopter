#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include "rutil.h"
//#include <avr/pgmspace.h>

#define DEFAULTSERVERID 1
#define NETID 100
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200
#define ANT_LED 9
#define FLASH_LED 8

byte SERVIERID = DEFAULTSERVERID;		
byte NODEID = 0;		//does not know its own id

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

void setup(){
	Serial.begin(SERIALBAUD);	//Initialize serial
	
	radio.initialize(FREQ, NODEID, NETID); //initialze rfm69 radio
	radio.setHighPower(true);

	flash.initialize();		//TODO check that this function passes
	
	while(!handshake());	
}

void loop(){
	
}

//handles handshaking phase
byte handshake(){
	
}

void processing(){
	
}

byte query(){
	
}

void transmitData(){
	
}

void receiveData(){
	
}