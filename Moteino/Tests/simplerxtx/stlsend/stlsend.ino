#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include <StandardCplusplus.h>
#include <String>

#define NODEID 2
#define TARGETID 1
#define NETID 100
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200
#define KEY "ABCDEFGHIJKLMNOP"
#define ANT_LED 9
#define FLASH_LED 8
#define SENDPERIOD 500 //send period in ms



RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);
std::string payload = "payload";

void setup(){
	Serial.begin(SERIALBAUD);
	
	radio.initialize(FREQ, NODEID, NETID);
	radio.encrypt(KEY);

	if(flash.initialize())
		Serial.println("Flash initialization: OK");
	else
		Serial.println("Flash initialization: FAILURE");
}


int lastPeriod = 0;
void loop(){
	int curPeriod = millis()/SENDPERIOD;
	if(curPeriod > lastPeriod){
		lastPeriod = curPeriod;
		
		Serial.print("sending payload: "); Serial.print(payload.c_str());
		Serial.print(" size: "); Serial.print(payload.length()); Serial.println();
		if(radio.sendWithRetry(TARGETID, payload.c_str(), payload.length()))
			Serial.print("Ack Received from:"); Serial.print(radio.SENDERID, DEC); Serial.println();
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
