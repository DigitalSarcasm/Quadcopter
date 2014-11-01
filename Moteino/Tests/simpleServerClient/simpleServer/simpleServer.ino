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

#define NODEID 1
#define NETID 100
byte CLIENTID = 0;    //avoid using #define for values that will be changed
#define FREQ RF69_915MHZ
#define SERIALBAUD 115200
#define ANT_LED 9
#define FLASH_LED 8
#define KEY "ABCDEFGHIJKLMNOP"

#define HANDSHAKINGATTEMPTS 30
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
			Serial.print(radio.SENDERID, DEC);
			Serial.print(" ");
			Serial.println(radio.PAYLOADLEN, DEC);
			if(radio.TARGETID == 0) {		//have a determined handshaking address that is rare (not 0->25 for safe measure)
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

void loop()
{


}

void blink(byte PIN, int DELAY_MS)
{
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN,HIGH);
	delay(DELAY_MS);
	digitalWrite(PIN,LOW);
}
