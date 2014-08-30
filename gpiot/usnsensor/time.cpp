#include <iostream>
#include <wiringPi.h>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

int main(int argc, char** argv){

	clock_t startc = 0, stopc = 0;
	int startw = 0, stopw = 0;
	timeval starttd, stoptd, res;
	double c, w, td;

	wiringPiSetup();


//usleep
	cout << "using usleep: \n";

	startc = clock();
	startw = micros();
	gettimeofday(&starttd, NULL);

	usleep(500000);

	stopc = clock();
	stopw = micros();
	gettimeofday(&stoptd, NULL);

	c = ((double)(stopc - startc))/CLOCKS_PER_SEC;
	w = ((double)(stopw - startw))/1000000;
	timersub(&stoptd, &starttd, &res);		//can't substract values as they are they might be negative due to roll over,
	td = ((double)(res.tv_usec))/1000000;	//use function sys/time.h functions for timeval arithmetics

	cout << "elapsed: clock: " << c << "secs \tmicro: " << w << "secs \t timeofday: " << td << "secs \n";

//delay

	cout << "using delayMicro: \n";

	startc = clock();
	startw = micros();
	gettimeofday(&starttd, NULL);

	delayMicroseconds(500000);

	stopc = clock();
	stopw = micros();
	gettimeofday(&stoptd, NULL);

	c = ((double)(stopc - startc))/CLOCKS_PER_SEC;
	w = ((double)(stopw - startw))/1000000;
	timersub(&stoptd, &starttd, &res);
	td = ((double)(res.tv_usec))/1000000;

	cout << "elapsed: clock: " << c << "secs \tmicro: " << w << "secs \t timeofday: " << td << "secs \n";



}
