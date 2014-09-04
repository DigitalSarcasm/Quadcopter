#include <wiringPi.h>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv){

	wiringPiSetup();

	pinMode(4, INPUT);

	digitalWrite(4, LOW);

	sleep(1);

	digitalWrite(0, LOW);

	return 0;


}
