/*
 * blink.c: 0 ou 1 sur GPIO17
 */
 
#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

// PIN - wiringPi pin 0 is BCM_GPIO 17.
#define	PIN	0

int main(void)
{
	printf("Raspberry Pi blink\n");
	int time=0;
	wiringPiSetup();
	pinMode (PIN, OUTPUT);

	for (;;)
	{
		digitalWrite(PIN, HIGH);	// On
		//delay (1);	// mS, marche avec 1
		digitalWrite(PIN, LOW);	// Off
		//delay (1);	// mS, marche avec 1
	}
	return 0;
}