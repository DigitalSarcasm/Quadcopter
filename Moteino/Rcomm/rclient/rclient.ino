#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include "rutil.h"
//#include <cstdlib>	//for random functions

#define DEFAULTSERVERID 1
#define PUBLICID 0
#define NETID 100
#define FREQ RF69_915MHZ
#define SERIALBAUD 9600

#define ANT_LED 9
#define FLASH_LED 8

#define OUTQUEUE 8
#define INQUEUE 8

//Processing
#define PROCTIME 500
#define SERIALWAIT 100
#define SERIALQ 20
#define OKTOSEND 1
#define RESENDMAX 400
//Query
#define QUERYTIME 500
//Transmission
#define	TRANSMAX 5
#define ACKTIMEOUT 80
#define TRANSRETRY 2
//Reception
#define RECEPTIMEOUT 200
#define RECEPRETRY 2


//byte handshake();
//void processing();
//byte query();
//byte transmission(Packet req);
//void reception(Packet req);
//bool activity();
//void printPacket(Packet p);

byte SERVERID = DEFAULTSERVERID;		
byte NODEID = 2;		//this should be provided by the server when there are more than one client

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

byte serverId = DEFAULTSERVERID;
PacketQueue<OUTQUEUE> outq;
PacketQueue<INQUEUE> inq;

Timer phaset;

boolean serialSent = false;	//has the client informed the host that the serial buffer is empty
Timer resend;

void setup(){
	Serial.begin(SERIALBAUD);	//Initialize serial
	
	radio.initialize(FREQ, NODEID, NETID); //initialze rfm69 radio
	radio.setHighPower(true);
	radio.encrypt(0);

	flash.initialize();		//TODO check that this function passes
	
	while(!handshake());
//	Serial.println("handshake complete");	//TODEL
}

void loop(){
	processing();
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

//Sends data to the client as batches of packets. Receives one packet at a time.
//For receiving, checks if buffer is empty, if not, than a packet must be incoming.
//if so, wait till the packet is completely sent (With timeout)
//when packet is completely received, make packet object and add to queue. 
void processing(){
	//process any saved data from received packets and incoming data from host
	
	phaset.start();	//start phase timer
	
	//TODO: FIND WAY OF INTERRUPTING HOST TO HAVE SYNCED UP PROCESSING
	//should find way of making sure that the serial buffer on the other side is not full
	while(phaset.getTime() < PROCTIME){
		//send any data received from the server
//		if(inq.length()>0){
//			Packet outputPacket = inq.dequeue();
//
//			for(int i=0; i<outputPacket.plength(); i++)
//				Serial.write(outputPacket.getPacket()[i]);
//		}
		//simply remove the data from the queue
		if(inq.length() > 0){
			inq.dequeue();
		}

		//getting data from host is currently not implemented
		//currently a stub function that rolls dice to see if the fake host has data to send to server
	/*	if(!outq.full()){
			//roll to see if the host has data
			byte chance = 2000;
			byte roll = rand() % chance;
			//if success, roll for type and data
			if(roll == 1){
				//then add to the outq
				Packet* p = outq.queueDummy();
				p->setType(DPACKET);
				p->setMeta(0);
				for(int i=0; i<30; i++)
					p->getData()[i] = i;
				p->setLength(30);
			}
		} */
		
		bool packetQueuing = true;	//always assume there is a packet queueing and check the serial buffer
		//ugly way of doing this, but i'm tired
		while(!outq.full() && packetQueuing){
			Timer serialWait;
			
			if(!serialSent){
				Serial.write(OKTOSEND);
				serialSent = true;
			}
			
			//check serial for any buffered data
			if(Serial.available() > 0){
				//if data is >0, then a packet is currently being written 
				serialWait.start();
				while(serialWait.getTime() < SERIALWAIT){	//wait for data to be written With timeout
					if(Serial.available() >= PACKETSIZE){
						byte buffer[PACKETSIZE];
						Serial.readBytes((char*)buffer, PACKETSIZE);	//get data from serial buffer
						Packet* p = outq.queueDummy();	//make packet
						p->setPacket(buffer, PACKETSIZE); //fill packet
						serialSent = false;
					}
				}
				
				if(!serialSent){	//the data has been read and buffer space is available
					delay(100);
					Serial.write(OKTOSEND);
					Serial.flush();
					serialSent = true;
					
					packetQueuing = false;	//assume the packet does not queue in time limit
					serialWait.start();	//start timer and check if a packet starts being sent (buffer != 0)
					
					while(serialWait.getTime() < SERIALQ){
						if(Serial.available() > 0){
							packetQueuing = true;	//if packet queues up
							break;
						}
					}
					
				}
			}
			else{
				packetQueuing = false;	//no packet queuing, so exit loop
				
//				if(!resend.running())
//					resend.start();
//				else if(resend.getTime() > RESENDMAX){	//in case the host misses the OK bit
//					serialSent = false;
//					resend.stop();
//				}
			}
			
		}
		
	}
}

//handles queries from the server. The server may query for requests from the client,
	//may request data from the host or start transmitting data to client.
void query(){
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
					if(outq.length() > 0){//currently doesn't check the number of packets needed to be sent as the consecutive packets are not created from large blocks of data
						byte data[2];
						data[0] = NODEID; //add node id as data to the packet
						if(outq.length() > TRANSMAX)	//set the number of requested packets
							data[1] = TRANSMAX;
						else
							data[1] = outq.length();
						Packet reqp(REQPACKET, TXREQ, data,2,0);
						//send tx request
						radio.sendWithRetry(SERVERID, reqp.getPacket(), reqp.plength());
					}
				}
				//TODO data request packet, this will be sent to the host
				else if(p.getMeta() == DREQ){
					//if the packet type is a data-request, create packet in inqueue
					//Serial.println("wrong meta in query");	//TODEL
				}
				//data transmission packet, the server is allowing transmissions to it 
				else if(p.getMeta() == TXREQ){
					//request acknowlegement
					//send packet to transmission function
					byte sent = transmission(p);
					//dequeue all sent packets
					for(int i=0; i<sent; i++)
						outq.dequeue();		
				}
				//reception request packet, the server wants to transmit packets to the client
				else if(p.getMeta() == RECREQ){	
					//if the packet is a reception request, send it to the reception function
					reception(p);
				}
			
			}
			else{
				//Serial.println("UNRECOGNIZED PACKET RECEIVED IN QUERY(), overhead: "); Serial.println(radio.DATA[0]);//TODEL
			}
		}
	}
}

/*
 * The transmission functions handles the transmission of X amount of packets from the Output queue
 * The function is called from the query function when the client receives the TX request back from the server when it is in its reception function
 * The function receives the request from the query function which holds the allowed number of functions to send to the server
 * The function has X amount of retries to send a packet. The function only sends the next packet if the last packet was ACked
 * The function might not send all the packets requested due to failures.
 * 
 * Returns: number of packets sent
 */
byte transmission(Packet req){
	Timer ackTimer;
	byte packNum = 0;	//packet number generator
	byte tries = 0;		//number of tries
	
	//use peek(with int) function to get packet as we will make sure to save packets if there are retries
	Packet* p = outq.peek(packNum);

	//check how much packets is allowed to be sent
	while(packNum < req.getData()[1] && tries < (req.getData()[1]+TRANSRETRY)){	//limits the loop to the number of packets allowed (or the number + retries if some are failures)
		p->setMeta(packNum);	//set packet number
		
		radio.send(SERVERID, p->getPacket(), p->plength());
		ackTimer.start();
		
		//possibly delay here
		
		//wait for reply and check the acked packet number before sending next one
		while(ackTimer.getTime() < ACKTIMEOUT){	//wait for ACK
			if(radio.ACKReceived(SERVERID)){
				if(radio.DATA[0] == 1){	//the packet was received and the packet number was valid
					packNum++;
					p = outq.peek(packNum);
					delay(10);	//delay as the server must save the packet
				}
				else if(radio.DATA[0] == 0){ //failure, sent wrong packet. Most likely missed an Ack, change Packet Number
					packNum = radio.DATA[1];	//set packet number
					p = outq.peek(packNum);
				}
				break;	//leave waiting loop as reponse was received
			}
		}
		tries++;	//keeping track of transmission tries
	}
	
	return packNum;
}

void reception(Packet req){
	byte packNum = 0;
	byte tries = 0;
	Timer time;
	
	//check the request and trim the packet number of there is no space in the input queue
	if(req.getData()[1] > (inq.maxLength() - inq.length()))
		req.getData()[1] = (inq.maxLength() - inq.length());
		
	
	while(packNum < req.getData()[1] && tries < (req.getData()[1] + RECEPRETRY)){
		//if its the first packet, send the ACK for the request. This allows the client to send back the request
		//if the server missed the first ACK
		if(packNum == 0){
			//send back the request in an Ack
			radio.sendACK(req.getPacket(), req.plength());
		}
		
		time.start();
		
		//wait to receive the data packets
		while(time.getTime() < RECEPTIMEOUT){
			if(radio.receiveDone()){
				if(Packet::getPacketType((byte)radio.DATA[0]) == DPACKET){
					//temporarily save received packet
					Packet recPacket((byte)radio.DATA[0], (byte*)radio.DATA+1, (byte)radio.DATALEN);
					
					//if the packet is valid, send ACK with accept byte positive
					if(recPacket.getMeta() == packNum){
						byte ackData[1] = {1};
						radio.sendACK(ackData, sizeof(ackData));
						inq.queue(recPacket);
						packNum++;
						delay(10);	//wait for next packet to be built
					}
					else{//else the packet is not valid and the requested packetnumber is sent
						byte ackData[2] = {0, packNum};
						radio.sendACK(ackData, sizeof(ackData));
					}
					break;	//leave waiting loop as reponse was received
				}
			}
		}
		tries++;
	}
//	delay(20);		//TODEL
}

//not tested
bool activity(){
	return (radio.readRSSI() > CSMA_LIMIT);
}

//for testing
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