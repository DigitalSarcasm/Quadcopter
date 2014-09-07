#include "ultrasn.h"

void setPin(int trig = TRIGGER, int echo = ECHO){
	TRIGGER = trig;	//mirror if the defaults haven't changed
	ECHO = echo;
	pinMode(TRIGGER, OUTPUT);
	pinMode(ECHO, INPUT);
}

/*
 * Pre : wiringpiSetup should already be run
 * 		 Pins should be set (setPin())
 *
 * Gets the distance of surrounding objects using ultrasonic sensors HC-SR04
 * The distance returned is the average (default AVGRATE).
 *
 * if the pulses do not return/are detected, the reading is timed out and retried
 * the function allows of a certain amount of time outs before assuming failure (default TIMEOUTLIMIT)
 *
 * returns distance or -1 if the time out limit has been reached
 *
 */
double getDistance(int avgRate = AVGRATE, timeval& timeout = TIMEOUT, int timeOutLimit = TIMEOUTLIMIT){

	timeval start, stop;
	timeval timerStart, timerStop, result;
	double elapsed = 0;
	double sumDistance = 0;
	int timeOutCount = 0;	//number of times the pulse can timeout

	//let module stabilize FOR 15 15 millisec
	digitalWrite(TRIGGER, LOW);
	usleep(15000);

	//gets the average of diatances
	for(int i=0; i<avgRate && timeOutCount<timeOutLimit; i++){
		bool timedOut = false;

		//trigger pulses send
		digitalWrite(TRIGGER, HIGH);
		usleep(10);
		digitalWrite(TRIGGER, LOW);

		gettimeofday(&timerStart, NULL); //start timeout timer

		//check if the signal changes or
		do(){
			gettimeofday(&timerStop, NULL);
			timersub(&timerStop, &timerStart, &result);
			timedOut = !(timercmp(&result, &timeout, <=)); //if (a<=b) does not equal false (man page it, its confusing to read)

			gettimeofDay(&start, NULL);			//get time that the echo pins turns to 1
		}while( (digitalRead(ECHO) == LOW) && !timedOut ); //while echo is low and the loop hasn't timed out

		//if not timed out, get travelTime reading
		if(!timedOut){
			while(digitalRead(ECHO) == 1)
				gettimeofday(&stop, NULL);
		}
		else{	//else, restart loop for another reading
			i--;
			timeOutCount++;
			continue;
		}

		//find distance
		timersub(&stop, &start, &result);	//time elapsed
		elapsed = (double)result.tv_sec + (double)result.tv_usec/1000000;	//in seconds
		sumDistance += (elapsed * 340 * 100)/2;	//add distance to the sum
	}

	if(timeOutCount == timeOutLimit)
		return -1;

	return sumDistance/avgRate;

}
