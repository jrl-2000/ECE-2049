unsigned int value1, value2, value3;
REFCTL0 &= ~REFMSTR;
// ADC12REFON: turn on internal reference voltage –1.5V
// ADC12ON: turn on ADC
// ADC12MSC: multiple channel for sample and conversion
ADC12CTL0 = ADC12SHT0_10 + ADC12SHT1_10 + ADC12REFON + ADC12ON + ADC12MSC;
// ADC12CSTARTADD_7: start conversion at ADC12MEM7
// ADC12SHP: SAMPCON signal source from the sampling timer
// Start conversion with ADC12MEM12
ADC12CTL1 = ADC12CSTARTADD_7 + ADC12SHP;
P6SEL |= BIT6;
// Analog pin A6 selected for ADC
P7SEL |= BIT1;
// Analog pin A13 selected for ADC
ADC12MCTL7 = ADC12SREF_0 + ADC12INCH_6;
// Input channel 6, the reference used isRef_0, V(R+) = Vcc = 3.3 V, and V(R-) = Vss. The full-scale range is 3.3  V.
ADC12MCTL8 = ADC12SREF_2 + ADC12INCH_13;
// input channel 13, the reference used is Ref_2,V(R+) = VeREF+ = 3.0 V, and V(R-) = VSS. This makes the full-scale range 3.0 V.
ADC12MCTL9 = ADC12SREF_1 + ADC12INCH_8 + ADC12EOS;// input channel 8, the referenced usedis Ref_1, V(R+) = VREF+ = 1.5 V, and V(R-) = Vss. The full-scale range is 1.5 V
ADC12CTL0 |= (ADC12SC|ADC12ENC);
while (ADC12CTL1 & ADC12BUSY){
    __no_operation();
    value1 = ADC12MEM7 & 0x0FFF; // get low 12 bits output memory register 7
    value2 = ADC12MEM8 & 0x0FFF; // get low 12 bits output memory register 8
    value3 = ADC12MEM9 & 0x0FFF;// get low 12 bits output memory register 9
}

float convert(){
    float adcVolts, pressureKPA;
    adcVolts = adcPressure * 2.5/16384;
    pressureKpa = adcVolts / 0.000111+ 0.12;
    return pressureKpa * 0.0009864;
}
uint32_t timer_cnt = 0;
bool sample = false;
#pragama vector = TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void){
    Timer_cnt++;
    sample = true;
}
void main(){
    WDCTL = WDTPW | WDTHOLD;
    // TASSEL_1 -> ACLK; MC_1 -> Up Mode; ID_0 -> divider = 1
    TA2CTL = TASSEL_1 + MC_1 + ID_0;
    TA2CCR0 = 3276; // interrupt occurs every 0.1s
    TA2CCTL0 = CCIE;
    _BIS_SR(GIE);
    uint32_t temp0, temp1, temp2;
    float tempDegC0, tempDegC1, tempDegC2;
    REFCTL0 &= ~REFMSTR;// multiple channels, use 2.5V internal reference voltage
    ADC12CTL0 = ADC12SHT0_9 + ADC12SHT1_9 + ADC12REF2_5 + ADC12REFON + ADC12ON +ADC12MSC;
    ADC12CTL1 = ADC12SHP | ADC12CONSEQ_1;ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_2;
    ADC12MCTL1 = ADC12SREF_1 + ADC12INCH_3;
    ADC12MCTL2 = ADC12SREF_1 + ADC12INCH_7 + ADC12EOS;// configure functional mode
    P6SEL |= (BIT2 | BIT3 | BIT7);
    ADC12CTL0 &= ~ADC12SC;
    while(1){
        if(sample){
            // if 0.1s has occurred
            ADC12CTL0 &= ~ADC12SC;
            // clear the start bit
            ADC12CTL0 |= ADC12SC + ADC12ENC;
            while (ADC12CTL1 & ADC12BUSY){
                __no_operation();
            }
            temp0 = ADC12MEM0 & 0x0FFF;
            temp1 = ADC12MEM1 & 0x0FFF;
            temp2 = ADC12MEM2 & 0x0FFF;
            tempDegC0 = ((temp0 * 2.5)/4096 –1.65) / 0.00780;
            tempDegC1 = ((temp1 * 2.5)/4096 –1.65) / 0.00780;
            tempDegC2 = ((temp2 * 2.5)/4096 –1.65) / 0.00780;sample = false;
        }
    }
}


