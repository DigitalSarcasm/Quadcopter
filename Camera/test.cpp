#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <unistd.h>
#include <sstream>

int main(){
	using namespace std;
	int t=0, fd = 0;
	char* name = "/dev/serial/by-id/usb-FTDI_FT231X_USB_UART_DA00S4AR-if00-port0";
//	char* name = "/dev/ttyUSB1";
	stringstream ss;
	
	t = wiringPiSetup();
	fd = serialOpen(name, 9600);
	
	cout << t << " " << fd << endl;
	
	//serialPutchar(fd, 'c');
	
	cout << "reading\n";
	
	serialFlush(fd);
	while(1){
		if(serialDataAvail(fd)>100){
			int c = 0; 
			char s[80];
			int siz;

			//int x =  read(fd, &c, 1);
			c = serialGetchar(fd);
//			siz = read(fd, s, serialDataAvail(fd));
//			char ch = c;
			ss << c;
			cout << ss.str() << " ";
			cout.flush();
			ss.str("");
//			cout << serialDataAvail(fd) << endl;
		}
	}
}
