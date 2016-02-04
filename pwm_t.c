/* compile using  "gcc -o swave swave.c -lrt -Wall" */
// http://www.instructables.com/id/RaspberryPi-Pulse-Width-Modulation-Demonstration/?ALLSTEPS

/***************************************************************************
 * Compile with:  gcc -o pwm_t pwm_t.c.c -lwiringPi
 *
 * arg1 = frequency
 * default = 100Hz
 *
 * arg2 = duty cycle
 * default = 50%
 *
 * arg3 = PIN
 * default = 1 (#6)
 ***************************************************************************/

#include <wiringPi.h>
#include <stdio.h>

void change_cycle_loop(void);
int PWMpin= 1;    // 1 right (Or 24 left if model B+).
int duty = 0;     // Duty cycle
int range = 100; // value passed to pwmSetRange.
/***************************************************************************
 * menu() function - Display the menu and execute the choices.
 ***************************************************************************/
void init(void)
{

	int clock = 19;   // value passed to pwmSetClock.
	int mode = 0;     // 0=balanced, 1=mark:space



  
	//Print information
	printf("\nDefault pin=\t%d \t\t input?",PWMpin);
		scanf("%d",&PWMpin);
		//PWMpin = &PWMpin;
		pinMode (PWMpin, PWM_OUTPUT);
	printf("\nDefault range=\t%d \t\t input?",range);
		scanf("%d", &range);
		pwmSetRange(range);       // Default 1024 (unsigned int)
	printf("\nDefault clock=\t%d \t\t input?",clock);
		scanf("%d", &clock);
		pwmSetClock(clock);
	printf("\nDefault duty cycle=\t%d \t input?",duty);
		scanf("%d", &duty);
		pwmWrite(PWMpin, duty);
}

/*********************************************************************
 * main() function
 *********************************************************************/
int main(void)
{
	wiringPiSetup();
	init();
	change_cycle_loop();
	return 0;
}

void change_cycle_loop(void)
{
	while(1) // Display the menu.
	{
	
	printf("\nCurrent duty cycle=\t%d \t input? [0-%d]",duty,range);
		scanf("%d", &duty);
		pwmWrite(PWMpin, duty);
	}
}
	
/*
	switch(choice) // Execute the choice.
	{
		case 1: // Fade duty cycle within 0 - range - 0.
			clrscr();
			x = 1; 
			for (i=0; i>-1; i+=x)
			{
			pwmWrite(PWMpin, i);
			printf("   %d\n", i);
			delay (7);
			if(i > range) x = -1;
			}
			pwmWrite(PWMpin, 0);
			duty=0;
		break;
		case 2: // toggle PWM mode Mark:Space/Balanced.
			mode = !mode;
			if(mode==0) pwmSetMode(PWM_MODE_BAL); 
			else pwmSetMode(PWM_MODE_MS); 
			pwmWrite(PWMpin, duty);
		break;
		case 3: // Change the range. (number of steps for duty cycle)
			printf("\n\n\n                          Enter Range: ");
			scanf("%d", &range);
			pwmSetRange(range);       // Default 1024 (unsigned int)
			pwmWrite(PWMpin, duty);
		break;
		case 4: // Change the clock.
			printf("\n\n\n                          Enter Clock: ");
			scanf("%d", &clock);
			pwmSetClock(clock);       // Default 32 (int)
			pwmWrite(PWMpin, duty);
		break;
		case 5: // Set the duty cycle.
			printf("\n\n\n                          Enter Duty Cycle: ");
			scanf("%d", &duty);
			pwmWrite(PWMpin, duty);
		break;
		}
	}
	*/
