#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include "rutil.h"
#include <cstdlib.h>

#define DEFAULTSERVERID 1
#define PUBLICID 0
#define NETID 100
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200

#define ANT_LED 9
#define FLASH_LED 8

#define OUTQUEUE 8
#define INQUEUE 8

#define PROCTIME 500
#define QUERYTIME 500

byte SERVERID = DEFAULTSERVERID;		
byte NODEID = 2;		//this should be provided by the server when there are more than one client

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

byte serverId = DEFAULTSERVERID;
PacketQueue<OUTQUEUE> outq;
PacketQueue<INQUEUE> inq;

Timer phaset;

void setup(){
	Serial.begin(SERIALBAUD);	//Initialize serial
	
	radio.initialize(FREQ, NODEID, NETID); //initialze rfm69 radio
	radio.setHighPower(true);

	flash.initialize();		//TODO check that this function passes
	
	while(!handshake());
	Serial.println("handshake complete");	//TODEL
}

void loop(){
	processing();

//	if(radio.receiveDone()){
//		Packet p((byte)radio.DATA[0], (byte*)radio.DATA+1, (byte)radio.DATALEN-1);
//		printPacket(p);
//	}
	query();
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
	
	phaset.start();	//start phase timer
	
	//TODO: FIND WAY OF INTERRUPTING HOST TO HAVE SYNCED UP PROCESSING
	//should find way of makign sure that the serial buffer on the other side is not full
	while(phaset.getTime() < PROCTIME){
		//send any data received from the server
		if(inq.length()>0){
			//currently prints the received packets
			printPacket(inq.dequeue());
		}
		
		//queue up packets from host to send (if the queue is not full)
/*		if(!outq.full() && Serial.available() > 0){
//			//currently the packets are made in this function. They should be made by the host
//			char c [] = {Serial.read(), '\0'};
//			int psize = atoi(c);	//the first byte is the size of the incoming packet
//			Serial.println(psize);
//			while(Serial.available() < psize)Serial.println(Serial.available());
//			Packet* p;
//			outq.queueDummy();	//create dummy packet and make real packet
//			p->setOverhead(Serial.read());	//set overhead for packet
//			psize--;//overhead was read
//			Serial.println(Serial.readBytes((char*)(p->getData()), psize));	//get data for packet
//			p->setLength(psize);
//			Serial.println("read");
		}*/
		
		//getting data from host is currently not implemented
		//currently a stub function that rolls dice to see if the fake host has data to send to server
		if(!outq.full()){
			//roll to see if the host has data
			byte chance = 2000;
			byte roll = rand() % chance;
			//if success, roll for type and data
			if(roll == 1){
				//then add to the outq
				Packet* p = outq.queueDummy();
				p->setOverhead(DPACKET);
				for(int i=0; i<30; i++)
					p->getData()[i] = i;
				p->setLength(30);
			}
		}
	}
}

//handles queries from the server. The server may query for requests from the client,
	//may request data from the host or start transmitting data to client.
byte query(){
	//make sure that the client is always on rx mode unless it is transmitting
	phaset.start();
	while(phaset.getTime() < QUERYTIME){
		//check for received packet
		if(radio.receiveDone()){
			//check packet type
			Packet p((byte)radio.DATA[0], (byte*)radio.DATA+1, (byte)radio.DATALEN-1);	//make packet
			
			//requests:
			if(p.getType() == REQPACKET){
				//if the packet type is a request-request, check outqueue for any packets to send.
				if(p.getMeta() == REQREQ){
					//if so, create a request packet for the packet (as it may be multiple data consecutive packets)
					if(outq.length() > 0){//currently doesn't check the number of packets needed to be sent as the consecutive packets are not created con
						Packet p(REQPACKET, TXREQ, 0,0,0);
						p.setData(&NODEID, 1);	//add node id as data to the packet
						//send tx request
						radio.sendWithRetry(SERVERID, p.getPacket(), p.plength());
					}
				}
				//data request packet, this will be sent to the host
				else if(p.getMeta() == DREQ){
					//if the packet type is a data-request, create packet in inqueue
				}
				//data transmission packet, the server is allowing transmissions to it 
				else if(p.getMeta() == TXREQ){
					//request acknowlegement
					//send packet to transmission function
				}
			
			}
			//data packet, the server is transmitting packets to the client
			else if(p.getType() == DPACKET){
				//data reception:
				//if the packet is a data transmission, send it to the reception function
			}
			else{
				Serial.println("UNRECOGNIZED PACKET RECEIVED IN QUERY(), overhead: "); Serial.println(radio.DATA[0]);//TODEL
			}
		}
	}
	
}

void transmission(){
	
}

void reception(){
	
}

//not tested
bool activity(){
	return (radio.readRSSI() > CSMA_LIMIT);
}

//testing
void printPacket(Packet p){
	Serial.println();
	Serial.print("overhead:"); Serial.println(p.getOverhead(), BIN);
	Serial.print("data length: "); Serial.print(p.length()); Serial.print(" data: ");
	for(int i=0; i<p.length(); i++)
		Serial.print(p.getData()[i], DEC);Serial.print(" ");
	Serial.println();
//	Serial.print("priority: "); Serial.println(p.getPriority());
//	Serial.println();
}