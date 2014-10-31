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
byte SERVERID = -1;
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

void setup(){
        int attempts = 0;
	Serial.begin(SERIALBAUD);
	
	radio.initialize(FREQ, CLIENTID, NETID);
	radio.encrypt(KEY);

	if(flash.initialize())
		Serial.println("Flash initialization: OK");
	else
		Serial.println("Flash initialization: FAILURE");
	
	delay(500);
	//starts handshaking phase
	//tries to handshake HANDSHAKINGATTEMPTS times
        while(attempts<HANDSHAKINGATTEMPTS){
        	if(radio.sendWithRetry(0,"",0, 1, HANDSHAKINGWAIT)){
        		SERVERID = radio.SENDERID;
        		Serial.print("Handshaking successful. Server Id: "); Serial.println(SERVERID, DEC);
                        attempts = HANDSHAKINGATTEMPTS;
        	}
                attempts++;
        }
		
}


void loop(){
	
}

void blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
