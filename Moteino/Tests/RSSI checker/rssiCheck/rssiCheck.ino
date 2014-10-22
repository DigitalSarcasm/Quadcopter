#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>

#define NODEID 1
#define NETID 100

#define FREQUENCY RF69_915MHZ

#define FLASH_SS 8
#define SERIALBAUD 115200

RFM69 radio;
SPIFlash flash(FLASH_SS, 0xEF30);

void setup(){
	
	Serial.begin(SERIALBAUD);
	delay(10);
	radio.initialize(FREQUENCY, NODEID, NETID);
	radio.encrypt(NULL);
	
	Serial.println("Radio initialized at 915Mhz");
	
	if(flash.initialize()){
		Serial.print("FLASH initialized OK, UNIQUE ID: ");
		flash.readUniqueId();
		for(byte i=0; i<8; i++)
			Serial.println(flash.UNIQUEID[i], HEX);
	}
	else
		Serial.println("FLASH intitialization failure");	
}

int count = 0;
void loop(){
	
	Serial.print("current check: "); Serial.print(count, DEC); Serial.print(": RSSI : ");
	Serial.print(radio.readRSSI(0), DEC);
	Serial.println();
        count++;
	delay(500);
}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
