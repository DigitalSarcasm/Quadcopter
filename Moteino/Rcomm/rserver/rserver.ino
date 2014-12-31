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

#define OUTQUEUE 8
#define INQUEUE 8

#define HSTIMEOUT 300 //handshaking timeout
#define QUERYTIMEOUT 80 //query timeout
#define QUERYRETRY 2	//number of query attempts

#define DEFAULTCLIENT 2

byte NODEID = DEFAULTSERVERID;

byte curClientID = 2;	//used to assign unique id's to clients
byte clientIds[MAXCLIENTS];	//holds client id's 

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

PacketQueue<OUTQUEUE> outq;	//output packets. to be sent to clients
PacketQueue<INQUEUE> inq; //input packets. received from clients
ClientList<> clist;
Timer phaset;

void setup(){
	Serial.begin(SERIALBAUD);	//Initialize serial
	
	radio.initialize(FREQ, NODEID, NETID); //initialze rfm69 radio
	radio.setHighPower(true);
	
	flash.initialize();	//		TODO check that this function passes
	
	while(!handshake());
	Serial.println("handshake complete");	//TODEL
	clist.add(DEFAULTCLIENT);
}

void loop(){
	query();
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
	//query every client in the client list. For every query, wait x amount of time for reply to query
	//the query must receive a request packet in the timeout time. The client may be queried more than once
	//the client can also send an NOREQUEST packet to signify that it does not have requests
	
	for(int i=0; i<clist.length(); i++){	//for every client
		Packet request(REQPACKET, REQREQ, 0,0,0);
		Timer timer;
		bool replied = false;
		
		for(int j=0; j<QUERYRETRY; j++){
			//send request-request packet
			radio.send(clist.getClient(i), request.getPacket(), request.plength());
			timer.start();	//start query timer
			
			//wait for a request or an empty packet as reply, try RETRY amount of times
			//if no reply is given, then the client is added to list for connection confirmation
			while(timer.getTime() < QUERYTIMEOUT){
				if(radio.receiveDone()){
					//check packet type
					if(Packet::getPacketType((byte)radio.DATA[0]) == REQPACKET){
						//check packet meta
						if(Packet::getPacketMeta((byte)radio.DATA[0]) == REQREQ){	//TODO check if the address of the client is the right client
							//add reply to input-queue is a request
							Packet* p = inq.queueDummy();
							p->setOverhead((byte)radio.DATA[0]);
							p->setData((byte*)radio.DATA+1, (byte)(radio.DATALEN-1));	//get data without overhead and substract the overhead from the datalen. also this sets the datalength
							if(radio.ACKRequested())
								radio.sendACK();
							replied = true;	//the client has a request
						}
						else if(Packet::getPacketMeta((byte)radio.DATA[0]) == NOREQ){
							if(radio.ACKRequested())
								radio.sendACK();
							replied = true;	//the client has a request
							Serial.println("working");
						}
					}
					else{
						Serial.print("received unexpected Packet, overhead: "); Serial.println(radio.DATA[0]);	//TODEL
					}
				}
			}
			if(replied)	//if the client replied, no need to retry
				break;
		}
		
		if(!replied){	//if the client has not replied
			//mark the client, if the client does not reply x times, then remove client from clientlist
		}
	}
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