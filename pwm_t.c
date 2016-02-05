/****************************************************************************/
/* Compile with:  gcc -o pwm_t pwm_t.c.c -lwiringPi							*/
/* Modifications & additions by Antoine G. 2016/02/05						*/
/* The user can change duty cycle and clock. Switching: follow instructions	*/
/* used: http://www.instructables.com/id/RaspberryPi-Pulse-Width-Modulation-Demonstration */
/****************************************************************************/

#include <stdio.h>
#include <wiringPi.h>

void change_range_clock_loop(void);

int mowd = 1;     	// 0=balanced, 1=mark:space
int PWMpin= 1;		// Pin PWM on Rpi 2:  
int range = 100;	// max value for duty cycle passed to pwmSetRange.
int clock = 192;	// clock, 192 for 50kHz at 50% dc
int duty = 25;		// Duty cycle
char overr;

void init(void)
{
	//Print information
	printf("Default values:\n\tMode: balanced\n\tpin: %d\n\trange: [0-%d]\n\tclock: %d\n\tDuty cycle: %d [0-%d]",PWMpin,range,clock,range,duty);
	printf("\nOverride values? [y/n]");
		scanf("%c",&overr);
	if(overr=='y' || overr=='Y')
	{
		printf("\nMode? (0=Mark:space 1=Balanced)\t");
			scanf("%d",&mowd);
			if(mowd==1){pwmSetMode(PWM_MODE_BAL);}
			else pwmSetMode(PWM_MODE_MS);
		printf("\nPin?[1/24] ");
			scanf("%d",&PWMpin);
			pinMode (PWMpin, PWM_OUTPUT);
		printf("\nRange? ");
			scanf("%d", &range);
			pwmSetRange(range);
		printf("\nClock? ");
			scanf("%d", &clock);
			pwmSetClock(clock);
		printf("\nDuty cycle? [0-%d] ",duty,range);
			scanf("%d", &duty);
			pwmWrite(PWMpin, duty);
	}
}

int main(void)
{
	wiringPiSetup();
	init();						//set user values
	change_range_clock_loop();	//change clock or duty cycle
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
		{	//change duty cycle
			pwmWrite(PWMpin, duty_r);
			printf("\nNew duty cycle? [0-%d] (-1 to switch to clock control)\ncurrent: clock=%d duty=%d/%d ",range,clock_r,duty_r,range);
			scanf("%d", &duty);
			if(duty == -1)
				{mod++;}
			else
				{duty_r=duty;}
		}
		if(mod==1)
		{	//change clock
			pwmSetClock(clock_r);
			printf("\nNew clock? (-1 to switch to range control)\ncurrent: clock=%d duty=%d%/%d% ",clock_r,duty_r,range);
			scanf("%d", &clock);
			if(clock == -1)
				{mod--;}
			else
				{clock_r=clock;}
		}
	}
}
