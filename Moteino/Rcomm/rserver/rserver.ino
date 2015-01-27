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

//handshaking
#define HSTIMEOUT 300 //handshaking timeout
//Query
#define QUERYTIMEOUT 80 //query timeout
#define QUERYRETRY 2	//number of query attempts
//Reception
#define RECEPRETRY 2
#define RECEPTIMEOUT 80
//Transmission
#define	TRANSMAX 5
#define TRANSRETRY 2
#define TRANSTIMEOUT 80

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
	radio.encrypt(0);
	
	flash.initialize();	//		TODO check that this function passes
	
	while(!handshake());
	Serial.println("handshake complete");	//TODEL
	clist.add(DEFAULTCLIENT);
}

void loop(){
	query();
	reception();
	processing();
//	transmission();
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
//this phase queries all clients whether they have any data to send and queues up transmission requests from said clients.
//this functions also confirms that all the clients in the client list are still reachable
//TODO: handle client that do not reply
void query(){
	//query every client in the client list. For every query, wait x amount of time for reply to query
	//the query must receive a request packet in the timeout time. The client may be queried more than once
	//the client can also send an NOREQUEST packet to signify that it does not have requests
	
	for(int i=0; i<clist.length(); i++){	//for every client
		Packet request(REQPACKET, REQREQ, 0,0,0);
		Timer timer;
		bool replied = false;
		//TODO: CHECK INQ/OUTQ CAPACITY		//SUPER IMPORTANT
		for(int j=0; j<QUERYRETRY; j++){
			//send request-request packet
			radio.send(clist.getClient(i), request.getPacket(), request.plength());
			timer.start();	//start query timer
			
			//wait for a request or an empty packet as reply, try RETRY amount of times
			//if no reply is given, then the client is added to list for connection re-confirmation
			while(timer.getTime() < QUERYTIMEOUT && !replied){
				if(radio.receiveDone()){
					//check packet type
					if(Packet::getPacketType((byte)radio.DATA[0]) == REQPACKET){
						//check packet meta
						//if the request packet is a transmission packet
						if(Packet::getPacketMeta((byte)radio.DATA[0]) == TXREQ){	//TODO check if the address of the client is the right client
							//add reply to output-queue as it is a request
							Packet* p = outq.queueDummy();	//create dummy packet
							p->setOverhead((byte)radio.DATA[0]);	//set its overhead
							p->setData((byte*)radio.DATA+1, (byte)(radio.DATALEN-1));	//set data without overhead and substract the overhead from the datalen. also this sets the datalength of the packet
							if(radio.ACKRequested())	//send ack if requested
								radio.sendACK();
							replied = true;	//the client has a request
						}
						//if the request packet is a norequest packet
						else if(Packet::getPacketMeta((byte)radio.DATA[0]) == NOREQ){
							if(radio.ACKRequested())
								radio.sendACK();
							replied = true;	//the client has replied and has no request
						}
					}
					else{
						Serial.print("UNRECOGNIZED PACKET RECEIVED IN QUERY(), overhead: "); Serial.println(radio.DATA[0]);	//TODEL
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
//currently only receives one packet at a time from a client, should implement the multiple packet method
/*void reception(){
//	//cycle through requests while there are requests in the output queue and there is space in the input queue for data
//	for(int i=0; (i<outq.length() && !inq.full()); i++){
//		Packet* p = outq.peek();
//		Timer receptimer;
//		//bool replied = false;
//		byte replied = 0;
//		
//		if(p->getData()[1] > (inq.maxLength() - inq.length()))	//check there is space for the number of request transmissions, if not, trim the number
//			p->getData()[1] = (inq.maxLength() - inq.length())	//if there isn't, trim the number of allowed packets
//		
//		for(int j=0; (j<RECEPRETRY && replied != p->getData()[1]); j++){	//retry request if the number of packets have not been sent. This loop runs once if all the packets have been received else, it tries RECEPRETRY time to receive the remaining packets
//			//send back TXrequest to client
//			byte left = p->getData()[1] - replied;	//check for any sent packets (if this is a retry)
//			radio.send(p->getData()[0],p->getPacket(), p->plength());
//			receptimer.start();
//			
//			//allow all packets to be sent (by multiplying 1 packet recept time * # of packets remaining)
//			while(receptimer.getTime()  < (RECEPTIMEOUT * left) && replied != p->getData()[1]){	//wait all replies reply
//			//if received, add data packet to input queue
//				if(radio.receiveDone()){
//					Packet* p = inq.queueDummy();
//					p->setOverhead((byte)radio.DATA[0]);
//					p->setData((byte*)radio.DATA+1, (byte)radio.DATALEN-1);
//					
//					if(radio.ACKRequested())
//						radio.sendACK();
//					
//					replied++;
//					//outq.dequeue();	//remove txrequest from the outq
//				}
//			}
//		}
//		//if all the packets were not received, rollover the packet
//		if(replied < p->getData()[1]){
//			outq.rollover();	//rollover the txrequest. 
//		}
//	}
}*/

//sends the request and wait for the packets to be sent. The packets use packet numbers in their meta to keep track of which is being received
//At this point, the output is full of requests
//the number of packets that can be received is based off the allowed max as well as the space in the input queue
//the number of packets to be received will be kept track of, not all may be received due to desync of server and client
//the function is limited by tries, where each try waits for the client to send the data, else a try is lost
//If the packet number does not match the packet number expected, a negative Ack is sent
//the request is sent back if the client does not reply with the first packet (number 0)
void reception(){
	//cycle through requests while there are requests in the output queue and there is space in the input queue for data
	while(outq.length() > 0 && !inq.full()){
		Packet* req = outq.peek();
		byte packNum = 0;	//used to check packet number
		byte tries = 0;
		Timer time;
		
		if(req->getData()[1] > (inq.maxLength() - inq.length()))	//check there is space for the number of request transmissions, if not, trim the number
			req->getData()[1] = (inq.maxLength() - inq.length());	//if there isn't, trim the number of allowed packets
		
		while(packNum <= req->getData()[1] && tries <= (req->getData()[1] + RECEPRETRY)){
			//send tx request
			if(packNum == 0){	//only send request first time, in case its missed, will resend
				radio.send(req->getData()[0], req->getPacket(), req->plength());
				//Serial.println("request sent");	//TODEL
			}//TODEL
				
			time.start();
			
			//wait for reply. The reply's packet number must match the counter
			//wait x amount of time for reply or failure
			while(time.getTime() < RECEPTIMEOUT){
				if(radio.receiveDone()){
					//Serial.println("received packet"); //TODEL
					//temporarily save packet and check its validity
					Packet recPacket((byte)radio.DATA[0], (byte*)radio.DATA+1, (byte)radio.DATALEN-1);
					
					//if the packet is valid, send ack with acceptance byte
					if(recPacket.getMeta() == packNum){
						//Serial.println("packnumber matches, saving");	//TODEL
						byte ackData[1] = {1};
						radio.sendACK(ackData, sizeof(ackData));
						inq.queue(recPacket);
						packNum++;
					}
					//else, send ACK with denial byte and the packet number needed
					else{
						//Serial.println("packnumber does not matche, not saving");	//TODEL
						byte ackData[2] = {0, packNum};
						radio.sendACK(ackData, sizeof(ackData));
					}
				}
			}
			tries++;
		}
		outq.dequeue();	//dequeue request, even if non of the packets were received
	}
}

//handles processing stage (stub function)
//check outq for any remaining txrequests, try to re-handshake those clients and dequeue the requests (they will be requeued during the next query phase)
void processing(){
	//currently the processing function just dequeues the packets and prints them
	while(inq.length() > 0){
		printPacket(inq.dequeue());
		//inq.dequeue();
	}
	
	//TODO check outq for any remaining requests. There might still be some as the inq might be full
	while(outq.length() > 0)
		printPacket(outq.dequeue());
		
	//create packets to send to clients in the outq
}

//handles data transmission phase
void transmission(){
	PacketQueue outq;	//DETLETE
	RFM69 radio;	//DELETE
	
	//loop though output queue until there are no more packets in the queue
	while(outq.length() > 0){
		byte currentClient = (*outq.peek()).getData()[0];	//current client id
		byte consec = 0;	//number of consecutive packets to the same client
		
		Packet req(REQPACKET, RECREQ, 0, 0, 0);	//create reception request for specific client
		
		byte packNum = 0;	//used to check packet number
		byte tries = 0;		//number of transmision tries
		Timer ackTimer;
		
		bool responded = false;
		
		//loop though output queue and check how much consecutive packets can be sent to the same client
		for(int i=0; (i<outq.length() && consec <= TRANSMAX); i++){	//limit the number to the max transmission number
			if(outq.peek()[0] != currentClient)
				consec++;
		}
		
		{	//set the requested packet number and node id
			byte data[2] = {NODEID, consec};
			req.setData(data, 2);
		}
		
		//Main transmission loop
		while(packNum < req.getData()[1]  && packNum < (req.getData()[1] + TRANSRETRY)){
			//before the first packet is sent the request must be sent
			//send request and wait for ACK
			if(!responded){
				radio.send(currentClient, req.getPacket(), req.plength());
				
				ackTimer.start();	//start timer
				
				//wait for ACK
				while(ackTimer.getTime() < TRANSTIMEOUT){
					if(radio.ACKReceived(currentClient)){
						req.getData()[1] = radio.DATA[1];	//get new allowed number of packets from ACK packet
						responded = true;
					}
				}
			}
			//if the client has already responded to the request, received data packets
			//send the specific amount of packets the request states (could be zero)
			else{
				Packet* p = outq.peek(packNum);	//get packet to send
				p.setMeta(packNum);		//set packetNumber
				
				radio.send(currentClient, p->getPacket(), p->plength());	//send packet
				ackTimer.start();	//start timer
				
				while(ackTimer.getTime() < TRANSTIMEOUT){
					if(radio.ACKReceived(currentClient)){
						if(radio.DATA[0] == 1){	//the packet was received and the packet number was valid
							packNum++;
							delay(10);	//delay as the server must save the packet
						}
						else if(radio.DATA[0] == 0){ //failure, sent wrong packet. Most likely missed an Ack, change Packet Number
							packNum = radio.DATA[1];	//set packet number
						}
						
					}
				}
			}
			tries++;
		}
		
		//dequeue all sent packets
		for(int i=0; i<packNum; i++)
			outq.dequeue();
		
	}
	
}

//not tested
bool activity(){
	return (radio.readRSSI() > CSMA_LIMIT);
}

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