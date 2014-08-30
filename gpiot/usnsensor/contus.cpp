#include <iostream>
#include <wiringPi.h>
#include <ctime>
#include <unistd.h>

using namespace std;

const int AVGRATE = 3; //how much values to calculate average

int main (int argc, char** argv){

	clock_t start = 0, stop = 0;
	double elapsed;
	double distance = 0;
	double average = 0;

	wiringPiSetup();

	pinMode(4, OUTPUT);	//set pin16 to output
	pinMode(5, INPUT);		//set pin18 to input

	digitalWrite(4, LOW); //set pin16 (trigger) to low
	usleep(100000);			//let sensor become stable (in case trigger was 1 and a pulse fired) for 100milliseconds

	cout << "starting measurement \n";

	while(true){
		average = 0;
		for(int i=0; i<AVGRATE; i++){

			digitalWrite(4, HIGH);
			usleep(10);				//minimum 10 microseconds to send pulse
			digitalWrite(4, LOW);

			while(digitalRead(5) == LOW)
				start = clock();

			while(digitalRead(5) == HIGH)
				stop = clock();

			elapsed = ((double)(stop - start))/CLOCKS_PER_SEC;


			distance = elapsed * (340 * 100); //distance = time * speed of sound in cm (340m/s)
			distance /= 2;	//the time was the time it took to for the pulse to hit object and come back, thus 2 times the time. so distance is divided by 2

			average += distance;
		}

		average /= AVGRATE;

		cout << "distance: " << average << "cm \n";
		usleep(1000000);	//sleep for 1 second
	}

}
