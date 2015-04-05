
#define FLASH_LED 8
#define ANT_LED 9

int x = 0;
char z[80];

void setup(){
	Serial.begin(9600);
	
	//while(Serial.available() == 0);
	
	//Serial.read();
	for(int i=0; i<80; i++)
		z[i] = 'a';
	
}

void loop(){
	Serial.write(x);
	x++;
	if(x>255)
		x = 0;
	blink(ANT_LED, 5);
	delay(200);
}

void blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}