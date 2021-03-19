unsigned long int timer = 0;
unsigned long int leap = 0;
#pragma vector = TIMER2_A0_VECTOR
__interrupt void TIMER_A2_ISR (void){
    if (leap < 43){
        timer++;
        leap++;
    }else {
        leap = 0;
        timer = timer;
    }

}
