/*
 * Simple Server. Takes commands from serial and sends it to Client. Takes commands from client and send it through Serial.
 * Should be able to handles multiple Clients. (PROMISCUITY??)
 * Should handshake in setup phase to have list of clients
 *
 */

#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include <StandardCplusplus.h>
#include <String>
#include "rutil.h"

#define NODEID 1
#define NETID 100
byte CLIENTID = 0;    //avoid using #define for values that will be changed
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200
#define ANT_LED 9
#define FLASH_LED 8
#define KEY "ABCDEFGHIJKLMNOP"

#define HANDSHAKINGATTEMPTS 15
#define HANDSHAKINGWAIT 100

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

void setup()
{
	bool handshaking = true;
	unsigned long milstart = 0;
	byte attempts = 0;
	Serial.begin(SERIALBAUD);

	radio.initialize(FREQ, NODEID, NETID);
	radio.encrypt(KEY);

	if(flash.initialize())
		Serial.println("Flash initialization: OK");
	else
		Serial.println("Flash initialization: FAILURE");

	radio.promiscuous(true);	//sets to promiscuous for handshaking

	milstart = millis();
	//starting handshaking
	while(handshaking) {
		if(radio.receiveDone()) {
			if(radio.TARGETID == 0) {		//have a determined handshaking address that is rare (not 0->25 for safe measure)
				Serial.print(radio.SENDERID, DEC);
				Serial.print(" ");
				Serial.println(radio.PAYLOADLEN, DEC);
				CLIENTID = radio.SENDERID;
				if(radio.ACKRequested())
					radio.sendACK();
				Serial.print("Handshaking Successful. Client ID:");
				Serial.println(CLIENTID, DEC);
			}
		}

		if((millis() - milstart)/HANDSHAKINGWAIT > attempts) {	//checks if handshaking phase is completed
			attempts++;
			Serial.print("Attempt: ");
			Serial.println(attempts, DEC);
			if(attempts >= HANDSHAKINGATTEMPTS)
				handshaking = false;
		}
	}
	radio.promiscuous(false);
	Serial.println("Handshaking complete");
}

byte t = 0;
Timer time;
void loop()
{
	bool reqrec = false;
	//checks for handshake
	if(CLIENTID == 0)
		return;
	Serial.print("Timer start time:");Serial.println(millis(), DEC);;
	time.start();
	//waits for request

	while(!reqrec) {
		if(radio.receiveDone()) {
			Serial.println("Request received");
			byte ptype = getPacketType(radio.DATA[0]);
			byte reqAck = B01000001;

			Serial.print("Packet type: ");
			Serial.print(ptype);
			Serial.print(" payload size: ");
			Serial.println(radio.PAYLOADLEN);

			if(t == 1) {
				for(int i=0; i< radio.PAYLOADLEN; i++) {
					Serial.print(radio.DATA[i], DEC);Serial.print(" ");
				}
				Serial.println();
			}


			radio.sendACK();

			if(ptype == 2) {					//if packet type is data transmission packet
				Serial.println("sending request ACK");
				while(!radio.canSend()) {
					Serial.print("waiting to send ACK: ");
					Serial.print(radio.readRSSI(), DEC);
					Serial.print(" radio mode: ");
					Serial.println(radio._mode, DEC);
					radio.receiveDone();	//A module cannot send when its not in rx_mode. i KNOW THAT'S DUMB
					//TODO: FIX WHEN YOU HAVE TIME OR MAKE A BETTER FUNCTION
				}
				radio.sendWithRetry(CLIENTID, &reqAck, sizeof(reqAck));
				reqrec = true;
				Serial.println("Send request ack");
			}
		}
	}

	// acknowledges requests and receives data
	while(!radio.receiveDone());

	//print our how much data was received
	if(getPacketType(radio.DATA[0]) == 3) { //data packet received
		Serial.println("Packet received");
		Serial.print("Size: ");
		Serial.println(radio.PAYLOADLEN, DEC);
		for(int i=0; i< radio.PAYLOADLEN; i++) {
			Serial.print(radio.DATA[i], DEC);Serial.print(" ");
		}
		Serial.println();
		t = 1;
	}
	
	Serial.print("Timer stop time: ");Serial.print(millis());Serial.print(" : ");Serial.println(time.stop(), DEC);
	
}

void blink(byte PIN, int DELAY_MS)
{
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN,HIGH);
	delay(DELAY_MS);
	digitalWrite(PIN,LOW);
}

byte getPacketType(byte ptype)
{
	byte typeMask = B11100000;
	byte type = ptype & typeMask;
	type = type >> 5;	//c++ does not have built in circular shift, we will use this instead
	return type;
}

byte getPacketData(byte ptype)
{
	byte typeMask = B00011111;
	byte data = ptype & typeMask;
	return data;
}
