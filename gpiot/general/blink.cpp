#include <wiringPi.h>
#include <unistd.h>


const int led = 0;

int main(){

	wiringPiSetup();

	pinMode(0, OUTPUT);
	digitalWrite(0, LOW);

	for(int i; i<20; i++){

		digitalWrite(0, HIGH);
		usleep(75000);
		digitalWrite(0, LOW);
		usleep(75000);

	}


}
