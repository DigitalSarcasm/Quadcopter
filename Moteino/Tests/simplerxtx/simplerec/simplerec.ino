#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>

#define NODEID 1
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
	
	radio.initialize(FREQ, NODEID, NETID);
	radio.encrypt(0);
	
	if(flash.initialize())
		Serial.println("Flash initialization: OK");
	else
		Serial.println("Flash initialization: FAILURE");
}

void loop(){
	if(radio.receiveDone()){
		Serial.print("Message receivd: ");
		
		Serial.print("FROM: "); Serial.println(radio.SENDERID, DEC);	
		Serial.print("  Datalen: "); Serial.print(radio.DATALEN, DEC);
			Serial.print("  ");
		for(int i=0; i<radio.DATALEN; i++)
			Serial.print((char)radio.DATA[i]);
		Serial.println();
		
		if(radio.ACKRequested())	//WARNING, AVOID USING FRM69 FUNCTIONS BEFORE EXTRACTING DATA, WILL CHANGE VARIABLES INCLUDING DATA AND DATALEN
			radio.sendACK();
		
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
