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

#define MAXCLIENTS 5

byte NODEID = DEFAULTSERVERID;

byte curClientID = 2;	//used to assign unique id's to clients
byte clientIds[MAXCLIENTS];	//holds client id's 

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

PacketQueue queue;

void setup(){
	Serial.begin(SERIALBAUD);	//Initialize serial
	
	radio.initialize(FREQ, NODEID, NETID); //initialze rfm69 radio
	radio.setHighPower(true);
	
	flash.initialize();	//		TODO check that this function passes
}

void loop(){
	
}

//handles handshaking phase
void handshake(){
	
}

//handles request query phase
void queryRequest(){
	
}

//handles data reception phase
void receiveData(){
	
}

//handles processing stage
void processing(){
	
}

//handles data transmission phase
void transmitData(){
	
}