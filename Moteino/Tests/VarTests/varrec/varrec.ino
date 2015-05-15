#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>

#define NODEID 1
#define TARGETID 2
#define NETID 100
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200
#define FLASH_LED 8
#define ANT_LED 9

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

void setup(){
	Serial.begin(SERIALBAUD);
	delay(10);
	
	radio.initialize(FREQ,NODEID,NETID);
	radio.encrypt(0);
	
	if(flash.initialize())
		Serial.println("Flash initialization: OK");
	else
		Serial.println("Flash initialization: FAILURE");
}

void loop(){
	if(radio.receiveDone()){	//wait for packet
	Serial.print("packetReceived, content of the payload: "); 
	for(int i=0; i<radio.DATALEN; i++)
		Serial.print((char)radio.DATA[i]);
	Serial.println();
	Serial.print("payloadlength: "); Serial.println(radio.DATALEN);
	if(radio.ACKRequested()){
		Serial.print("sending back ACK");
		radio.sendACK();
	}
	Serial.print("content of the payload after send : ");
	for(int i=0; i<radio.DATALEN; i++)
		Serial.print((char)radio.DATA[i]);
	Serial.println();
	Serial.print("payloadlength: "); Serial.println(radio.DATALEN);
	}
}