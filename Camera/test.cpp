#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>

int main(){
	using namespace std;
	int t=0, fd = 0;
	char* name = "/dev/serial/by-id/usb-FTDI_FT231X_USB_UART_DA00S4AR-if00-port0";
	
	t = wiringPiSetup();
	fd = serialOpen(name, 115200);
	
	cout << t << " " << fd << endl;
}
