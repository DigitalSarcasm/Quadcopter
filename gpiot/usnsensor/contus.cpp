#include <iostream>
#include <wiringPi.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

const int AVGRATE = 3; //how much values to calculate average

int main (int argc, char** argv){

	timeval start, stop, res;
	long start2 = 0, stop2 = 0;
	double elapsed;
	double distance = 0;
	double average = 0;
	double average2 = 0;

	wiringPiSetup();

	pinMode(4, OUTPUT);	//set pin16 to output
	pinMode(5, INPUT);		//set pin18 to input

	digitalWrite(4, LOW); //set pin16 (trigger) to low
	usleep(100000);			//let sensor become stable (in case trigger was 1 and a pulse fired) for 100milliseconds

	cout << "starting measurement \n";

	while(true){
		average = average2 = 0;
		for(int i=0; i<AVGRATE; i++){

			digitalWrite(4, HIGH);
			usleep(10);				//minimum 10 microseconds to send pulse
			digitalWrite(4, LOW);

			while(digitalRead(5) == LOW)
				gettimeofday(&start, NULL);			//clock is processor dependent

			while(digitalRead(5) == HIGH)
				gettimeofday(&stop, NULL);

			timersub(&stop, &start, &res);
			elapsed = ((double)(res.tv_usec))/1000000;


			distance = elapsed * (340 * 100); //distance = time * speed of sound in cm (340m/s)
			distance /= 2;	//the time was the time it took to for the pulse to hit object and come back, thus 2 times the time. so distance is divided by 2

			average += distance;
		}

		for(int i=0; i<AVGRATE; i++){

			digitalWrite(4, HIGH);
			delayMicroseconds(10);				//minimum 10 microseconds to send pulse
			digitalWrite(4, LOW);

			while(digitalRead(5) == LOW)
				start2 = micros();

			while(digitalRead(5) == HIGH)
				stop2 = micros();

			elapsed = (double)(stop2 - start2) / 1000000;


			distance = elapsed * (340 * 100); //distance = time * speed of sound in cm (340m/s)
			distance /= 2;	//the time was the time it took to for the pulse to hit object and come back, thus 2 times the time. so distance is divided by 2

			average2 += distance;
		}

		average /= AVGRATE;
		average2 /= AVGRATE;

		cout << "distance with clock: " << average << "cm \tdistance with delay: " << average2 << "cm \n";
		usleep(1000000);	//sleep for 1 second
	}

}
