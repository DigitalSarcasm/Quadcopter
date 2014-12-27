#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>

#define NODEID 2
#define TARGETID 1
#define NETID 100
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200
#define FLASH_LED 8
#define ANT_LED 9

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);
char* payload = "payload";
byte len = 7;

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
	delay(200);
	//Serial.print("sending message len");Serial.println(len, DEC);
	if(radio.sendWithRetry(TARGETID, payload, len)){
		Serial.print("content of the payload: "); 
		for(int i=0; i<radio.DATALEN; i++)
			Serial.print((char)radio.DATA[i]);
		Serial.println();
		Serial.print("payloadlength: "); Serial.println(radio.DATALEN);
	}
}