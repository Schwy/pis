/* compile using  "gcc -o swave swave.c -lrt -Wall" */
// http://www.instructables.com/id/RaspberryPi-Pulse-Width-Modulation-Demonstration/?ALLSTEPS

/***************************************************************************
 * Compile with:  gcc -o pwm_t pwm_t.c.c -lwiringPi
 *
 * All pin numbers are wiringPi numbers unless otherwise specified.
 * 
 * Pin 1 is the only hardware PWM pin available on all RaspberryPi models.
 * It is physical pin number 12 on the GPIO header.
 *
 * Pin 24 is the second hardware PWM pin available on model B+ only.
 * It is physical pin number 35 on the GPIO header.
 *
 * There is an LED (with series resistor) connected to PWMpin and ground.
 * An oscilloscope can be connected to PWMpin and ground.
 *
 * You can hear the tones if speakers are connected to the audio jack.
 * Changing the various settings can make the tones very loud.
 *
 * Menu choices:
 *
 *  1 Fade In-Out - Runs through a for loop one time.
 *    It runs from 0 to 100% to 0 of the duty cycle in the
 *    number of steps specified in the range.
 *
 *  2 Toggle the PWM mode between balanced and mark:space.
 *
 *  3 Set the range, the number of duty cycle steps between 0 and 100%.
 * 
 *  4 Change the PWM clock.
 *
 *  5 Set the duty cycle. The duty cycle should not be greater than the range.
 *    Duty cycle is 100% if duty cycle equals range.
 *
 *  6 QUIET sets duty cycle to zero.
 ***************************************************************************/

#include <wiringPi.h>
#include <stdio.h>

#define clrscr() printf("\e[1;1H\e[2J") // Clear screen.

int PWMpin= 1;    // 1 right (Or 24 left if model B+).

/***************************************************************************
 * menu() function - Display the menu and execute the choices.
 ***************************************************************************/
void menu(void)
{
  int range = 1024; // value passed to pwmSetRange.
  int clock = 32;   // value passed to pwmSetClock.
  int mode = 0;     // 0=balanced, 1=mark:space
  int duty = 0;     // Duty cycle
  int choice=0;
  int i; // Index for fade for loop. 
  int x; // Fade in/out switch.

  while(1) // Display the menu.
  { 
    clrscr();
    printf("\n\n                      Pulse Width Modulation Demonstration\n\n\n");
    printf("                      1 - Fade In - Out\n");
    printf("                      2 - Toggle PWM Mode: ");
    if(mode==0) printf("Balanced\n");
    else printf("Mark:Space\n");
    printf("                      3 - Set Range: %d\n", range);
    printf("                      4 - Set Clock: %d\n", clock);
    printf("                      5 - Set Duty Cycle: %d\n",duty);
    printf("                      6 - QUIET\n\n\n");
    printf("                          Press Selection: ");
    scanf("%d", &choice);

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
      case 6: // Quiet, set duty cycle to zero.
        duty = 0;
        pwmWrite(PWMpin, duty);
        break;
    }
  }
}

/*********************************************************************
 * main() function
 *********************************************************************/
int main(void)
{
  wiringPiSetup();
  pinMode (PWMpin, PWM_OUTPUT);
  menu();
  return 0;
}

