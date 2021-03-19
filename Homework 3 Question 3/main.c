void init_sys(void){
    P5SEL |= (BIT5|BIT4|BIT3|BIT2);
    UCSCTL6 &= ~(XT2OFF); // Turn on XT2CLK
    UCSCTL4 = 0x0054;
}
void setupTimerA2(void){
    // Use SMCLK (TASSEL_2), count in Up Mode (MC_1), and set the clock divider to 1 (ID_0)
    TA2CTL = TASSEL_2 + MC_1 + ID_0;
    TA2CRR0 = 1999; // 1999 + 1 = 2000 tics, or exactly 0.25 ms
    TA2CCTL0 = CCIE; // enable interrupt}// TimerA2  ISR
}
#pragma vector = TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void){
    timer++;
}


void countToDisplay(int  count){
    long unsigned int Count = count * 2.5;
    char d[7];
    for (int i = 6; i <= 0; --i){
        if (i == 2){
            --i;
        }
        d[i]= (Count %10) + 0x30;
        Count/= 10;
    }
    d[2] = ‘.’;

 }
