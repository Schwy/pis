/* compile using  "gcc -o swave swave.c -lrt -Wall" */
// http://www.instructables.com/id/RaspberryPi-Pulse-Width-Modulation-Demonstration/?ALLSTEPS

/***************************************************************************
 * Compile with:  gcc -o pwm_t pwm_t.c.c -lwiringPi
 ***************************************************************************/

#include <wiringPi.h>
#include <stdio.h>

void change_range_clock_loop(void);
int PWMpin= 1;    // 1 right (Or 24 left if model B+).
int duty = 25;     // Duty cycle
int range = 100; // value passed to pwmSetRange.
int clock = 192;   // value passed to pwmSetClock.
int mode = 1;     // 0=balanced, 1=mark:space
int mowd = 1;

void init(void)
{
	//Print information
	printf("\nMode? (0=Mark:space 1=Balanced)\t");
		scanf("%d",&mowd);
		if(mowd==1){pwmSetMode(PWM_MODE_BAL);}
		else pwmSetMode(PWM_MODE_MS);
	printf("\nPin? (default=%d) [1/24]\t",PWMpin);
		scanf("%d",&PWMpin);
		//PWMpin = &PWMpin;
		pinMode (PWMpin, PWM_OUTPUT);
	printf("\nRange? (default=%d)\t",range);
		scanf("%d", &range);
		pwmSetRange(range);       // Default 1024 (unsigned int)
	printf("\nClock? (default=%d)\t",clock);
		scanf("%d", &clock);
		pwmSetClock(clock);
	printf("\nDuty cycle? (default=%d%%)\n[0-%d]\t\t\t",duty,range);
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
	change_range_clock_loop();
	return 0;
}

void change_range_clock_loop(void)
{
	int mod = 0; // 0=range - 1=clock
	int duty_r = duty;
	int clock_r = clock;


while(1) // Display choices
	{
		if(mod==0)
		{
			pwmWrite(PWMpin, duty_r);
			printf("\nNew duty cycle? [0-%d] (%d to switch to clock control)\ncurrent: clock=%d duty=%d%% ",range,range+1,clock_r,duty_r);
			scanf("%d", &duty);
			if(duty == range+1)
				{mod++;}
			else
				{duty_r=duty;}
		}
		if(mod==1)
		{
			pwmSetClock(clock_r);
			printf("\nNew clock? (0 to switch to range control)\ncurrent: clock=%d duty=%d%% ",clock_r,duty_r);
			scanf("%d", &clock);
			if(clock == 0)
				{mod--;}
			else
				{clock_r=clock;}
		}
	}
}
