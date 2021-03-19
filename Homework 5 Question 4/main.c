#include <msp430.h> 

void configTimerA2();
void DACinit();
void DACSetValue(unsigned int dac);
unsigned int time_count;
unsigned int last_count;

unsigned int DACcodes = {4092, 3720, 3348, 2976, 2604, 2232, 1860, 1488, 1116, 744, 372, 0};
//int freq = 160;

// (1/160) = T = 0.00625 and 12 steps per period is 0.0625/12 = 0.000521

// 5V/ 11 steps = 454.5mV

//code diff = 372

#pragma vector = TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void)
{
    time_count++;

}


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    DACinit();
    configTimerA2();
    last_count = time_count;
    while(1){
        while(time_count == last_count){
            __no_operation();
            DACSetValue(DACcodes[time_count % 12]);
            last_count = time_count;

        }
    }//end wile 1


}// end main


void configTimerA2(){
    TA2CTL = TASSEL_1 | MC_1 | ID_0;
    //max_c = 17 - 1
    TA2CCR0 = 16;  //0.000521s which is  (1/160) = T = 0.00625 and 12 steps per period is 0.0625/12 = 0.000521
    TA2CCTL0 = CCIE;
}
