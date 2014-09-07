#include <iostream>
#include "ultrasn.h"

using namespace std;

int main(){

	wiringPiSetup();
	setPin();

	for(int i=0; i<10; i++){
		cout << getDistance() << endl;
		sleep(1);
	}




}
