/*
 * Simple Client. Takes command from Serial and sends to server. Takes command from server and send it to serial.
 * Should handshake with server during setup phase to have server address (sends out its id and asks for server's ID)
 *
 */

#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include <StandardCplusplus.h>
#include <String>

#define CLIENTID 2
byte SERVERID = 0;
#define NETID 100
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200
#define KEY "ABCDEFGHIJKLMNOP"
#define ANT_LED 9
#define FLASH_LED 8

#define SENDPERIOD 500 //send period in ms
#define HANDSHAKINGWAIT 100	//millseconds to wait for handshaking ACK. DEFAULT MAY BE TOO LOW FOR ROUNDTRIP
#define HANDSHAKINGATTEMPTS 10 //number of attempts at handshaking


RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);
byte d[80];

void setup()
{
	unsigned long milstart;
	int attempts = 0;
	int curPeriod = 0;
	Serial.begin(SERIALBAUD);

	radio.initialize(FREQ, CLIENTID, NETID);
	radio.encrypt(KEY);

	if(flash.initialize())
		Serial.println("Flash initialization: OK");
	else
		Serial.println("Flash initialization: FAILURE");

	//promiscuity is not needed
	//radio.promiscuous(true);	//turn on promiscuity because we do not know
	delay(200);                     //have to sync up the client or server or the client might finish
	milstart = millis();              //handshaking before server starts up

	//starts handshaking phase
	//tries to handshake HANDSHAKINGATTEMPTS times
	while(attempts<HANDSHAKINGATTEMPTS) {//as we are trying to handshake with the server, we don't know its address so we send to 0 (server request address)
		//since we don't know the server's id we must handshake manually
		//but sine ACKReceived needs to know who to accept the ack from, we can't use
		//sendWithretry as it needs to know who to take ACK from (ACKReceived)
		radio.send(0, "", 0, true);	//sends without retry and waits for ACK manually

		while((millis()-milstart) < HANDSHAKINGWAIT) {	//waits for ACK
			if(radio.receiveDone()) {
                                //Serial.println(radio.ACK_RECEIVED, DEC);
				if(radio.ACK_RECEIVED) {
					SERVERID = radio.SENDERID;		//Get server's address
					Serial.print("Handshaking successful. Server Id: ");	//servers address
					Serial.println(SERVERID, DEC);
					attempts = HANDSHAKINGATTEMPTS;
				}
			}
		}
                milstart = millis();
		attempts++;
	}
	//radio.promiscuous(false);
	Serial.println(SERVERID, DEC);
        Serial.println("Handshaking complete");

	for(int i=1; i< 80; i++)
		d[i] = i;
}


void loop()
{
	bool reqack = false;

	//Checks for handshake
	if(SERVERID == 0) //handshake has failed
		return;

	//requests transmission

	byte buf[62];
	byte packettype = B01000000; //request transmission (2)
	buf[0] = packettype;
	int psize = sizeof(buf);

	while(1) {
		if(radio.canSend()){
			if(radio.sendWithRetry(SERVERID, &packettype, sizeof(packettype), 4))
			  break;
		}
	}
	Serial.println("Request sent");

	//wait for ack and send large data block bigger than 61 bytes
	bool txend = false;
	while(!txend) {
		while(!radio.receiveDone());
		Serial.println("Received packet");
		//if the received packet is a request packet and it was acknowledged
		
		radio.sendACK();
		
		if(getPacketType(radio.DATA[0]) == 2 && getPacketData(radio.DATA[0]) == 1){
			Serial.println("Sending data");
			d[0] = B01100000;
			radio.sendWithRetry(SERVERID, d, sizeof(d));
			txend = true;
		}
	}

Serial.println("Send complete");
}

byte getPacketType(byte ptype)
{
	byte typeMask = B11100000;	//mask everthing but packet type bits
	byte type = ptype & typeMask;
	type = type >> 5;
	return type;
}

void blink(byte PIN, int DELAY_MS)
{
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN,HIGH);
	delay(DELAY_MS);
	digitalWrite(PIN,LOW);
}

byte getPacketData(byte ptype){
	byte typeMask = B00011111;
	byte data = ptype & typeMask;
	return data;
}
