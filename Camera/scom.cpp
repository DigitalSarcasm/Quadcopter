#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include "base64.h"
#include "rutil.h"
#include <stdio.h>
#include <poll.h>

using namespace std;

string getBase64Img(string name);

int main(){
	char* name = "/dev/serial/by-id/usb-FTDI_FT231X_USB_UART_DA00S4AR-if00-port0";
	int fd;
	pollfd fds[1];
	Timer tim;
	
	wiringPiSetup();
	
	byte data[30];
	
	for(int i=0; i<30; i++)
		data[i] = i;
	
	Packet p((byte)2, (byte)0, (byte*)data, (byte)30, (byte)0);
	
	fd = serialOpen(name, 9600);
	cout << fd << endl;
	
	fds[0].fd = fd;
	fds[0].events = POLLIN;
	
	p.pad();
	
	for(int i=0; i<p.plength(); i++)
		cout << (int)p.getPacket()[i] << " ";
	
	cout << endl << (int)p.plength() <<" done \n";
	
//	cout << getBase64Img("Donate.jpg");
	
	while(1){
//		tim.start();
//		if(serialDataAvail(fd) > 0){
		poll(fds, 1, 100);
		if(fds[0].revents & POLLIN){
			int x = serialGetchar(fd);
			if(x == 1){
				//for(int i=0; i< p.plength(); i++){
//					serialPutchar(fd, p.getPacket()[i]);
					write(fd, p.getPacket(), (int)p.plength());
				//}
				serialFlush(fd);
			}
			cout << "SENT ";
			cout.flush();
		}
		cout << "here";
		cout << serialDataAvail(fd) << " ";
		cout.flush();
//		usleep(500000);
//		sleep(1);
//		delay(100);

		//while(tim.getElapsedTimeInMilliSec() < 500);

//		if(serialDataAvail(fd)){
//			int c = serialGetchar(fd);
//			cout << c;
//			cout.flush();
//		}
	}
//	while(1){
//		if(serialDataAvail(fd) > 0){
//			int x = serialGetchar(fd);
//			cout << x;
//			cout.flush();
//			serialPutchar(fd, 45);
//		}
//	}
	
	//MESSAGE: the sync program worked. Thus i think it is the client that is the problem. I added a delay in the code, see if that works
}

string getBase64Img(string name){
	ifstream file;
	vector<unsigned char> binBuf;
	string imgB64 = "";
	
	file.open(name.c_str(), ios::binary|ios::in);	//open image
	
	char c;
	while(file.get(c)){	//get binary data of image
		binBuf.push_back((unsigned char)c);
	}
	
	imgB64 = base64_encode(&binBuf[0], binBuf.size());	//create base64 encoding of image
	
	file.close();
	return imgB64;
}