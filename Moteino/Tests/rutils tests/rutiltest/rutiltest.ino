#include "rutil.h"

void setup(){
	//run all tests in setup
	
	Serial.begin(115200);
	
	//testing empty packet
	Packet p1;
	Serial.println("p1");
	printPacket(p1);
	
	byte buf[60];
	for(int i=0; i<60; i++)
		buf[i] = i;
	//testing setting values for empty packet
	Serial.println("p1 edited");
	p1.setOverhead(7, 6);
	p1.setData(buf, 60);
	printPacket(p1);
	
	//creating fully set packet version 1
	Packet p2(p1.getOverhead(), buf, 60, 8);
	Serial.println("p2");
	printPacket(p2);
	
	//creating fully set packet version 2
	Packet p3(5, 3, buf, 60, 200);
	Serial.println("p3");
	printPacket(p3);
	Serial.print("p3 overhead: type: "); Serial.print(p3.getType()); Serial.print(" meta: ");Serial.println(p3.getMeta()); 
	p3.setType(1); p3.setMeta(30);
	Serial.print("p3 overhead edited: type: "); Serial.print(p3.getType()); Serial.print(" meta: ");Serial.println(p3.getMeta()); 

}

void loop(){
	
}

void printPacket(Packet p){
	Serial.print("overhead:"); Serial.println(p.getOverhead(), BIN);
	Serial.print("data length: "); Serial.print(p.length()); Serial.print(" data: ");
	for(int i=0; i<p.length(); i++)
		Serial.print(p.getData()[i]);Serial.print(" ");
	Serial.println();
	Serial.print("priority: "); Serial.println(p.getPriority());
	Serial.println();
}