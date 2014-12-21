#include "rutil.h"
#include <ArduinoUnit.h>

test(timer_not_started){
	Timer t;
	assertEqual(t.getTime(), 0);
}

test(timer_timing){
	Timer t;
	long start = millis(), stop;
	
	t.start();
	for(int i=0; i<200; i++)
		i*5/2;
	t.stop();
	stop = millis();
	assertEqual(t.getTime(), (stop - start));
	
	//test the timer without stopping it
	start = millis();
	t.start();
	for(int i=0; i<200; i++)
		i*5/2;
	stop = millis();
	assertEqual(t.getTime(), (stop - start));
}


///packet tests
test(packet_default_constructor){
	Packet p;
	assertEqual(p.getType(), 0);
	assertEqual(p.getMeta(), 0);
	assertEqual(p.getPriority(), 0);
	assertEqual(p.getOverhead(), 0);
}

test(packet_constructor_set_values_var){
	byte type = 3, meta = 22, priority = 155, datal = 42;
	byte data[datal];
	for(int i=0; i<datal; i++)
		data[i] = i;
	
	Packet p(type, meta, data, datal, priority);
	
	assertEqual(p.getType(), type);
	assertEqual(p.getMeta(), meta);
	assertEqual(p.getPriority(), priority);
	assertEqual(p.length(), datal);
	for(int i=0; i<p.length(); i++)
		assertEqual(p.getData()[i], i);
}

test(packet_constructor_set_values_temp){
	byte data[42];
	for(int i=0; i<42; i++)
		data[i] = i;
	
	Packet p(3, 22, data, 42, 155);
	
	assertEqual(p.getType(), 3);
	assertEqual(p.getMeta(), 22);
	assertEqual(p.getPriority(), 155);
	assertEqual(p.length(), 42);
	for(int i=0; i<p.length(); i++)
		assertEqual(p.getData()[i], i);

}

test(packet_overhead_functions){
	byte type1 = 6, meta1 = 30;
	byte type2 = 8, meta2 = 0;
	byte type3 = 5, meta3 = 32;
	
	assertNotEqual(Packet::makeOverhead(type1, meta1), 0);
	
	byte overhead = Packet::makeOverhead(type1, meta1);
	assertEqual(Packet::getPacketType(overhead), type1);
	assertEqual(Packet::getPacketMeta(overhead), meta1);
	
	assertEqual(Packet::makeOverhead(type2, meta2), 0);
	assertEqual(Packet::makeOverhead(type3, meta3), 0);
}

test(packet_constructor_overhead){
	byte type = 3, meta = 22, priority = 155, datal = 42;
	byte data[datal];
	for(int i=0; i<datal; i++)
		data[i] = i;
	
	Packet p(Packet::makeOverhead(type, meta), data, datal, priority);
	
	assertEqual(p.getType(), type);
	assertEqual(p.getMeta(), meta);
	assertEqual(p.getPriority(), priority);
	assertEqual(p.length(), datal);
	for(int i=0; i<p.length(); i++)
		assertEqual(p.getData()[i], i);
}

test(packet_set_Data){
	byte type = 3, meta = 22, priority = 155, datal = 42;
	byte data[datal];
	byte data2[datal-1];
	for(int i=0; i<datal; i++){
		data[i] = i;
		if(i<datal-1)
			data2[i] = i*2;
	}
	
	Packet p(Packet::makeOverhead(type, meta), data, datal, priority);
	for(int i=0; i<p.length(); i++)
		assertEqual(p.getData()[i], i);
	
	p.setData(data2, datal-1);
	assertEqual(p.length(), datal-1);
	
	for(int i=0; i<p.length(); i++)
		assertEqual(p.getData()[i], i*2);
}

test(packet_set_overhead_values){
	Packet p;
	byte type = 6, meta = 16;
	
	assertEqual(p.getOverhead(), 0);
	
	p.setOverhead(type, meta);
	
	assertEqual(p.getType(), type);
	assertEqual(p.getMeta(), meta);
}

test(packet_set_overhead){
	Packet p;
	byte type = 6, meta = 16;
	byte overhead = Packet::makeOverhead(type, meta);
	
	assertEqual(p.getOverhead(), 0);
	
	p.setOverhead(overhead);
	
	assertEqual(p.getType(), type);
	assertEqual(p.getMeta(), meta);
	
	type = 2;
	
	p.setType(type);
	assertEqual(p.getType(), type);
	
	meta = 30;
	
	p.setMeta(meta);
	assertEqual(p.getMeta(), meta);
	
	
	assertEqual(p.setType(8), 0); //it went over the byte limit for type
	
	assertEqual(p.setMeta(32), 0); //it went over the byte limit for meta
}

void setup(){
	Serial.begin(115200);
}

void loop(){
	Test::run();
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