#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include <string>

#define NODEID 2
#define NETID 100
#define TARGET 1
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200
#define FLASH_LED 8
#define ANT_LED 9

#define SENDPERIOD 500 //period to send message

RFM69 radio;
SPIFlash flash(FLASH_LED, 0xEF30);
int lastPeriod=0;
char payload [] = "payload";
byte len = sizeof(payload)/sizeof(char);

void setup(){
	Serial.begin(SERIALBAUD);
	delay(10);
	
	radio.initialize(FREQ, NODEID, NETID);
	radio.encrypt(0);
	
	if(flash.initialize())
		Serial.println("Flash initialization: OK");
	else
		Serial.println("Flash initialization: FAILURE");
}


void loop(){
	int curPeriod = millis()/SENDPERIOD;
	if( curPeriod > lastPeriod){	//used instead of a delay, this allows for other things to happen outside the sending section (checking serial inputs)
		lastPeriod = curPeriod;
		Serial.print("Sending: "); Serial.println(payload);
			Serial.print("Datalen: "); Serial.println(sizeof(payload), DEC);
		if(radio.sendWithRetry(TARGET, payload, len))
			Serial.println("sent");
		blink(ANT_LED, 5);
	}
}

void blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
