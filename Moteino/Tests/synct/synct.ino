#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>

#define SERIALBAUD 9600


void setup(){
	Serial.begin(SERIALBAUD);	//Initialize serial
	
	Serial.write(1);
}

void loop(){
	if(Serial.available() > 0){
		Serial.read();
		Serial.write(1);
	}
//	delay(100);
}