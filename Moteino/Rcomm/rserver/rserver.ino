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

#define MAXCLIENTS 5

#define HSTIMEOUT 300 //handshaking timeout

byte NODEID = DEFAULTSERVERID;

byte curClientID = 2;	//used to assign unique id's to clients
byte clientIds[MAXCLIENTS];	//holds client id's 

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

PacketQueue<> queue;
ClientList<> clist;
Timer phaset;

void setup(){
	Serial.begin(SERIALBAUD);	//Initialize serial
	
	radio.initialize(FREQ, NODEID, NETID); //initialze rfm69 radio
	radio.setHighPower(true);
	
	flash.initialize();	//		TODO check that this function passes
	
	while(!handshake());
	Serial.println("handshake complete");
}

void loop(){
	
}

//handles handshaking phase
//curently skeletal functionality, can only handles one client
byte handshake(){
	//continuously try to handshake with atleast one client
	Packet req(REQPACKET, HSREQ, 0, 0, 0);		//never forget to add the priority to the packet
	radio.send(PUBLICID, req.getPacket(),1);
	phaset.start();	//start timer
	while(phaset.getTime() < HSTIMEOUT){	//wait for reply
		if(radio.receiveDone()){
			//check if the received packet is a handshaking request
			if(radio.TARGETID == NODEID && Packet::getPacketType((byte)radio.DATA[0]) == REQPACKET && Packet::getPacketMeta((byte)radio.DATA[0]) == HSREQ){
				clist.add((byte)radio.SENDERID);	//needs to be casted as senderid is volatile
				if(radio.ACKRequested())
					radio.sendACK();
				return true;
			}
		}
	}
	return false;
}

//handles request query phase
void query(){
	//query all clients in client list and ask if they have any requests
}

//handles data reception phase
void reception(){
	
}

//handles processing stage
void processing(){
	
}

//handles data transmission phase
void transmission(){
	
}

//not tested
bool activity(){
	return (radio.readRSSI() > CSMA_LIMIT);
}