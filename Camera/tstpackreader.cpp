#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include "rutil.h"

int getPacket(int* buffer, int length);
int fd;
int main(){
	using namespace std;
	
	char* name = "/dev/serial/by-id/usb-FTDI_FT231X_USB_UART_DA00S4AR-if00-port0";
	int c[62];
	string s;
	stringstream ss;
	
	wiringPiSetup();
	
	fd = serialOpen(name, 9600);
	cout << fd << endl;
	serialFlush(fd);
	while(1){
		if(serialDataAvail(fd) > PACKETSIZE){
			
			int l;
			l = getPacket(c, serialDataAvail(fd));
			//ss.str(c);
			//cout << ss.str();
			
			for(int i=0; i<l; i++)
				cout << c[i] << " ";
			cout << endl;
			cout.flush();
		}
//		cout << serialDataAvail(fd) << endl;
		
		sleep(1);
	}
	
}

//should return a packet object
int getPacket(int* buffer, int length){
	byte buf[PACKETSIZE];
	for(int i=0; i<length; i++){
		buffer[i] = serialGetchar(fd);
	}
	return length;
}