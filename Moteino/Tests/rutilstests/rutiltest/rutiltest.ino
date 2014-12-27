#include "rutil.h"
#include <ArduinoUnit.h>

///////////////////////////timer tests
test(AA_timer_not_started){
	Timer t;
	assertEqual(t.getTime(), 0);
}

test(AB_timer_timing){
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


////////////////////////////////////packet tests
test(BA_packet_default_constructor){
	Packet p;
	assertEqual(p.getType(), 0);
	assertEqual(p.getMeta(), 0);
	assertEqual(p.getPriority(), 0);
	assertEqual(p.getOverhead(), 0);
	assertEqual(p.plength(), 1);
	assertEqual(p.length(), 0);
}

test(BB_packet_constructor_set_values_var){
	byte type = 3, meta = 22, priority = 155, datal = 42;
	byte data[datal];
	for(int i=0; i<datal; i++)
		data[i] = i;
	
	Packet p(type, meta, data, datal, priority);
	
	assertEqual(p.getType(), type);
	assertEqual(p.getMeta(), meta);
	assertEqual(p.getPriority(), priority);
	assertEqual(p.length(), datal);
	assertEqual(p.plength(), datal+1);
	for(int i=0; i<p.length(); i++)
		assertEqual(p.getData()[i], i);
}

test(BC_packet_constructor_set_values_temp){
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

test(BD_packet_comparison){
	byte data[35];
	byte data2[59];
	
	for(int i=0; i<35; i++){
		data[i] = i;
		data2[i] = i*2;
	}
	
	Packet p1(1, 20, data, 35, 0);
	Packet p2(5, 12, data2, 59, 0);
	
	assertEqual(p1==p2, false);
	
	p2.setType(1);
	assertEqual(p1==p2, false);
	p2.setMeta(20);
	assertEqual(p1==p2, false);
	p2.setData(data, 35);
	assertEqual(p1==p2, true);
	p2.setPriority(20);
	assertEqual(p1==p2, false);
	p2.setPriority(0);
	assertEqual(p1==p2, true);
	p2.setOverhead(128);
	assertEqual(p1==p2, false);
	assertEqual(p1==p1, true);
}

test(BE_packet_copy){
	byte data[35];
	byte data2[59];
	
	for(int i=0; i<35; i++){
		data[i] = i;
		data2[i] = i*2;
	}
	
	Packet p1(1, 20, data, 35, 0);
	Packet p2(5, 12, data2, 59, 0);
	Packet p3 = p1;
	
	assertEqual(p1==p2, false);
	assertEqual(p1==p3, true);
	
	p2 = p1;
	assertEqual(p1==p2, true);
	
}

test(BF_packet_overhead_functions){
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

test(BG_packet_constructor_overhead){
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

test(BH_packet_set_Data){
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

test(BI_packet_set_overhead_values){
	Packet p;
	byte type = 6, meta = 16;
	
	assertEqual(p.getOverhead(), 0);
	
	p.setOverhead(type, meta);
	
	assertEqual(p.getType(), type);
	assertEqual(p.getMeta(), meta);
}

test(BJ_packet_set_overhead){
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

////////////////////////////PacketQueue tests

test(packetqueue_queue_dequeue_packet){
	Packet p1(5,20,0,0,0);
	Packet p2(1,12,0,0,0);
	Packet p3(7,30,0,0,0);
	PacketQueue<> q;

	assertEqual(q.length(), 0);

	q.queue(p1);
	
	assertEqual(q.length(), 1);
	Packet px = q.dequeue();
//	assertEqual(q.dequeue().getOverhead(), p1.getOverhead());
	printPacket(p1);
	printPacket(px);
	assertEqual(q.length(), 0);
	
	q.queue(p1);
	q.queue(p2);
	assertEqual(q.length(), 2);
	
	assertEqual(q.dequeue().getOverhead(), p1.getOverhead());
	assertEqual(q.length(), 1);
	
	q.queue(p3);
	assertEqual(q.length(), 2);
	assertEqual(q.dequeue().getOverhead(), p2.getOverhead());	
	assertEqual(q.dequeue().getOverhead(), p3.getOverhead());
	assertEqual(q.length(), 0);
	
	assertEqual(q.dequeue().getOverhead(), Packet().getOverhead());	//should return empty packet
	
}

test(packetqueue_queue_dequeue_data){
//	Packet(5,20,0,0);
//	Packet(1,12,0,0);
//	Packet(7,30,0,0);
	PacketQueue<> q;

	assertEqual(q.length(), 0);

	q.queue(5, 20, 0, 0);
	
	assertEqual(q.length(), 1);
	assertEqual(q.dequeue().getOverhead(), Packet(5,20,0,0,0).getOverhead());
	assertEqual(q.length(), 0);
	
	q.queue(5, 20, 0, 0);
	q.queue(1, 12, 0, 0);
	assertEqual(q.length(), 2);
	
	assertEqual(q.dequeue().getOverhead(), Packet(5,20,0,0,0).getOverhead());
	assertEqual(q.length(), 1);
	
	q.queue(7, 30, 0, 0);
	assertEqual(q.length(), 2);
	assertEqual(q.dequeue().getOverhead(), Packet(1,12,0,0,0).getOverhead());
	assertEqual(q.length(), 1);
	assertEqual(q.dequeue().getOverhead(), Packet(7,30,0,0,0).getOverhead());
	assertEqual(q.length(), 0);
	assertEqual(q.dequeue().getOverhead(), Packet().getOverhead());	//should return empty packet
}

//test(packetqueue_copy_constructor){
//	
//}
//
//test(packetqueue_assignment){
//	
//}

test(packetqueue_overfill_queue){
	PacketQueue<> q;
	
	for(int i=0; i<QUEUESIZE; i++)
		assertEqual(q.queue(Packet(5,20,0,0,0)), 1);
		
	assertEqual(q.length(), QUEUESIZE);
	assertEqual(q.queue(Packet(5,20,0,0,0)), 0);
	
	q.dequeue();
	assertEqual(q.queue(Packet(5,20,0,0,0)), 1);
}

test(packetqueue_cycle_queue){
	PacketQueue<> q;
	
	for(int i=0; i<QUEUESIZE; i++)
		q.queue(Packet(i,20,0,0,0));
		
	assertEqual(q.length(), QUEUESIZE);
	
	for(int i=0; i<QUEUESIZE/2; i++)	//dequeue half
		assertEqual(q.dequeue().getType(), i);
		
	assertEqual(q.length(),  QUEUESIZE - QUEUESIZE/2);
	
	q.queue(Packet(5,20,0,0,0));
	
	assertEqual(q.dequeue().getType(), QUEUESIZE/2);
}

test(clientlist_add_remove){
	ClientList<> cl;
	assertEqual(cl.lenght(), 0);
	
	cl.add(5);
	assertEqual(cl.lenght(), 1);
	assertEqual(cl.getClient(0), 5);
	
	cl.add(6);
	assertEqual(cl.lenght(), 2);
	assertEqual(cl.getClient(0), 5);
	assertEqual(cl.getClient(1), 6);
	
	cl.remove(5);
	
	assertEqual(cl.lenght(), 1);
	assertEqual(cl.getClient(0), 6);
	
	cl.add(5);
	cl.toggleRequest(1);
	assertEqual(cl.lenght(), 2);
	assertEqual(cl.getClient(1), 5);
	assertEqual(cl.getClient(0), 6);
	assertEqual(cl.getRequest(1), true);
	
}

test(clientlist_overfill_and_existing){
	ClientList<> cl;
	
	for(int i=0; i<LISTSIZE; i++)
		assertEqual(cl.add(i), 1);
	
	assertEqual(cl.add(LISTSIZE), 0);
	
	cl.remove(0);
	
	assertEqual(cl.add(1), 0);	//1 is already in the list
	assertEqual(cl.add(LISTSIZE+1), 1);
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