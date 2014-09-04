#include <wirinPi.h>
#include <sys/time.h>
#include <unistd.h>

timeval TIMEOUT = {0, 1400}; //default timeout is 0.014seconds because the sensor maxs out at 5 meters
int AVGRATE = 3;

int TRIGGER = 4; //default pin is pin16
int ECHO = 5; //default pin is pin18


void setPin(int trig = TRIGGER, int echo = ECHO){
	pinMode(TRIGGER, OUTPUT);
	pinMode(ECHO, INPUT);
}

/*
 * wiringpiSetup should already be run
 * 
 */
double getDistance(timeval& timeout = &TIMEOUT){
	
	timeval start, stop;
	double elapsed;
	
	for(int i=0; i<AVGRATE; i++){
		
		digitalWrite(TRIGGER, LOW);
		usleep(15000);			//let module stabilize
		
		digitalWrite(TRIGGER, HIGH);
		usleep(10);
		digitalWrite(ECHO, LOW);
		
	}
	

	
}
