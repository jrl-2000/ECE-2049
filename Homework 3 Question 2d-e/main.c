#include <msp430.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

long unsigned int timer = 0;

// Function Prototypes
void swDelay(char numLoops);
void timerSetup();
int timerToDate(long unsigned int);

#pragma vector=TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR (void) {
    timer++;
}
// Main
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    timerSetup();
    while(1){
    }
    return 0;

}
int timeToDate(long unsigned int timmer)
{
    int daysDenom = 86400;
    int hoursDenom = 60*60;
    int[5] convertDate;
    float remainder = 0;
    float remainder1 = 0;
    float remainder2 = 0;
    float remainder3 = 0;
    int days;
    days = (timer/ (daysDenom));
    remainder = ((timer/ (daysDenom)) % 1);
    switch(days)
    {
    case 1 ... 31:
    convertDate[0] = 1;
    convertDate[1] = days;
    break;
    case 32 ... 59:
    convertDate[0] = 2;
    convertDate[1] = days - 31;
    break;
    case 60 ... 90
    convertDate[0] = 3;
    convertDate[1] = days - 59;
    break;
    case 91 ... 120:
    convertDate[0] = 4;
    convertDate[1] = days - 90;
    break;
    case 121 ... 151:
    convertDate[0] = 5;
    convertDate[1] = days - 120;
    break;
    case 152 ... 181:
    convertDate[0] = 6;
    convertDate[1] = days - 151;
    break;
    case 182 ... 212:
    convertDate[0] = 7;
    convertDate[1] = days - 181;
    break;
    case 213 ... 243:
    convertDate[0] = 8;
    convertDate[1] = days - 212;
    break;
    case 244 ... 273:
    convertDate[0] = 9;
    convertDate[1] = days - 243;
    break;
    case 274 ... 304:
    convertDate[0] = 10;
    convertDate[1] = days - 273;
    break;
    case 305 ... 334:
    convertDate[0] = 11;
    convertDate[1] = days - 304;
    break;
    case 335 ... 365
    convertDate[0] = 12;
    convertDate[1] = days - 334;
    break;
    }
    convertDate[2] = remainder * 24;
    remainder2 = ((remainder * 24) % 1);
    convertDate[3] = remainder2 * 60;
    remainder3 = ((remainder2 * 60) % 1);
    convertDate[4] = remainder3 * 60;
}


void timerSetup()
{
    TA2CTL = TASSEL_1 | ID_0 | MC_1;
    TA2CCR0 = 32767;
    TACCTL0 = CCIE;
}


void swDelay(char numLoops)
{
    // This function is a software delay. It performs
    // useless loops to waste a bit of time
    //
    // Input: numLoops = number of delay loops to execute
    // Output: none
    //
    // smj, ECE2049, 25 Aug 2013
    // hamayel qureshi, 28 march 2020

    volatile unsigned int i,j;	// volatile to prevent removal in optimization
    // by compiler. Functionally this is useless code

    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;					// SW Delay
        while (i > 0)				// could also have used while (i)
            i--;
    }
}
