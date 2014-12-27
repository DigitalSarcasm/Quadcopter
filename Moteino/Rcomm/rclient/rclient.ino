#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include "rutil.h"

#define DEFAULTSERVERID 1
#define PUBLICID 0
#define NETID 100
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200

#define ANT_LED 9
#define FLASH_LED 8

byte SERVIERID = DEFAULTSERVERID;		
byte NODEID = 2;		//this should be provided by the server when there are more than one client

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

byte serverId = DEFAULTSERVERID;
PacketQueue<> queue;
Timer phaset;

void setup(){
	Serial.begin(SERIALBAUD);	//Initialize serial
	
	radio.initialize(FREQ, NODEID, NETID); //initialze rfm69 radio
	radio.setHighPower(true);

	flash.initialize();		//TODO check that this function passes
	
	while(!handshake());
	Serial.println("handshake complete");
}

void loop(){
	
}

//handles handshaking phase
//curently skeletal functionality, can only handles one client
byte handshake(){
	//continuously try to handshake with the server
	radio.promiscuous(true);	//this allows receiving public packets
	while(!radio.receiveDone()); //wait for any message
	if(radio.TARGETID == PUBLICID){	//checks if the received packet is public
		//then checks if its a public handshaking packet (server is allowing client handshaking)
		if(Packet::getPacketType((byte)radio.DATA[0]) == REQPACKET && Packet::getPacketMeta((byte)radio.DATA[0]) == HSREQ){
			byte hsOverhead = Packet::makeOverhead(REQPACKET, HSREQ);
			if(radio.sendWithRetry(serverId, &hsOverhead , 1)){	//send handshaking packet to server
				radio.promiscuous(false);
				return true;
			}
		}
	}
	radio.promiscuous(false);
	return false;
}

void processing(){
	//process any saved data from received packets and incoming data from host
}

byte query(){
	
}

void transmission(){
	
}

void reception(){
	
}

//not tested
bool activity(){
	return (radio.readRSSI() > CSMA_LIMIT);
}