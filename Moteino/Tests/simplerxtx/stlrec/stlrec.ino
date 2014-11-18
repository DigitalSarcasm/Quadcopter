#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include <StandardCplusplus.h>
#include <String>

#define NODEID 1
#define NETID 100
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200
#define ANT_LED 9
#define FLASH_LED 8
#define KEY "ABCDEFGHIJKLMNOP"

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);

void setup(){
	Serial.begin(SERIALBAUD);
	
	radio.initialize(FREQ, NODEID, NETID);
	radio.encrypt(KEY);
	
	if(flash.initialize())
		Serial.println("Flash initialization: OK");
	else
		Serial.println("Flash initialization: FAILURE");
}

void loop(){
	std::string payload;
	
	if(radio.receiveDone()){
		
		payload = std::string((char*)radio.DATA);	//Since we know that the payload is a char array
		
		Serial.print("Message Received. Payload length: "); Serial.print(radio.PAYLOADLEN, DEC); Serial.println();
		Serial.print("Payload: "); Serial.println(payload.c_str());
		
		if(radio.ACKRequested())
			radio.sendACK();
		blink(ANT_LED, 3);
	}
}

void blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
