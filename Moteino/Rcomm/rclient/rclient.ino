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

//Processing
#define PROCTIME 500
//Query
#define QUERYTIME 500
//Transmission
#define	TRANSMAX 5
#define ACKTIMEOUT 80
#define TRANSRETRY 2
//Reception
#define RECEPTIMEOUT 80
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

void setup(){
	Serial.begin(SERIALBAUD);	//Initialize serial
	
	radio.initialize(FREQ, NODEID, NETID); //initialze rfm69 radio
	radio.setHighPower(true);
	radio.encrypt(0);

	flash.initialize();		//TODO check that this function passes
	
	while(!handshake());
	Serial.println("handshake complete");	//TODEL
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
				p->setType(DPACKET);
				p->setMeta(0);
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
					Serial.println("wrong meta in query");	//TODEL
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
			
			}
			//reception request packet, the server wants to transmit packets to the client
			else if(p.getType() == RECREQ){	
				//data reception:
				//if the packet is a reception request, send it to the reception function
				reception(p);
			}
			else{
				Serial.println("UNRECOGNIZED PACKET RECEIVED IN QUERY(), overhead: "); Serial.println(radio.DATA[0]);//TODEL
			}
		}
	}
}

/*
byte transmission(Packet req){
	RFM69 radio; //DELETE
	Packet req;	//DELETE
	PacketQueue outq;//DELETE
	byte counter = 0;
	
	//construct packet to be transmitted using the request
	for(int i=0; i<req.getData()[1]; i++){	//get number of packets to send from the request packet
		//send the allowed amount of packets
		if(radio.sendWithRetry(SERVERID, outq.peek()->getPacket(),outq.peek()->plength(), TRANSRETRY,TRANSTIMEOUT)){
			outq.dequeue();
			counter++;
		}
		delay(10);	//allow some delay for the server to prepare to receive next packet
	}
	
	//return the number of packets sent
	return counter;
}*/

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
	//PacketQueue outq;	//TODEL
	//RFM69 radio;		//TODEL
	//Packet req;		//TODEL
	Timer ackTimer;
	byte packNum = 0;	//packet number generator
	byte tries = 0;		//number of tries
	
	//use peek(with int) function to get packet as we will make sure to save packets if there are retries
	Packet* p = outq.peek(packNum);
	
	//check how much packets is allowed to be sent
	while(packNum <= req.getData()[1] && tries <= (req.getData()[0]+TRANSRETRY)){	//limits the loop to the number of packets allowed (or the number + retries if some are failures)
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
				
			}
		}
		tries++;	//keeping track of transmission tries
	}
	
	return packNum;
}

void reception(Packet req){
	Packet req;		//DELETE
	PacketQueue outq;
	PacketQueue inq;
	RFM69 radio;
	
	byte packNum = 0;
	byte tries = 0;
	Timer time;
	
	//check the request and trim the packet number of there is no space in the input queue
	if(req.getData()[1] > inq.length())
		req.getData()[1] = (inq.maxLength() - inq.length());
	
	while(packNum < req.getData()[1] && packNum < (req.getData()[1] + RECEPRETRY)){
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
				
				//temporarily save packet
				Packet recPacket((byte)radio.DATA[0], (byte*)radio.DATA+1, (byte)radio.DATALEN);
				
				//if the packet is valid, send ACK with accept byte positive
				if(recPacket.getMeta() == packNum){
					byte ackData[1] = {1};
					radio.sendACK(ackData, sizeof(ackData));
					inq.queue(recPacket);
					packNum++;
				}
				//else the packet is not valid and the requested packetnumber is sent
				else{
					byte ackData[2] = {0, packNum};
					radio.sendACK(ackData, sizeof(ackData));
				}
				
			}
		}
		tries++;
	}
	
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