/************** ECE 2049 LAB 3 CODE ******************/
/**************  3   March   2021   ******************/
/*************    Jonathan Lopez   ******************/
/***************************************************/

//Time and Temperature Display

#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <JRL.h>
#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)
#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)
/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

// Globals
unsigned int inputTemp;
float temps[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int avgcount = 0;
unsigned int checksec = 0;
unsigned long int currsecs = 5679960;
int currentSel = 0;
long unsigned int rightButton, leftButton;
//char dateFormat[];
unsigned long int months, days, hrs, mins, secs, howManyDays;
unsigned long int todaysDay;
unsigned long int mths;
bool editbool = false;

// Function Prototypes
void swDelay(char numLoops);
void configLaunchpadButtons();
void displayTime(long unsigned int inTime);
void displayTemp(float inAvgTempC);
void configTimerA2();
unsigned long int monthHa(unsigned long int seconds);
unsigned long int daysHa(unsigned long int daysP,  unsigned long int month);
float setADC12();
float avg(float temp[10]);
unsigned char buttonP();
bool edit();

#pragma vector = TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void)
{
    currsecs++;
    checksec = 9;
}

// Main
void main(void)
{
    //ADC setup
    _BIS_SR(GIE);
    // Global Interrupt enable

    WDTCTL = WDTPW | WDTHOLD;                                                                      // Stop watchdog timer
    REFCTL0 &= ~REFMSTR;
    ADC12CTL0 = ADC12SHT0_9 | ADC12REFON | ADC12ON | ADC12MSC;
    ADC12CTL1 = ADC12SHP |  ADC12CONSEQ_1;
    P6SEL |= BIT0;
    ADC12MCTL0 = ADC12SREF_0 | ADC12INCH_0 ;
    ADC12MCTL1 = ADC12SREF_1 | ADC12INCH_10 | ADC12EOS; //ch10
    __delay_cycles(100);
    ADC12CTL0 |= ADC12ENC;

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
    // You can then configure it properly, if desired

    //Init Code
    initLeds();
    configDisplay();
    configKeypad();
    configLaunchpadButtons();
    configTimerA2();



    while (1){    // Forever loop

        // Draw a box around everything because it looks nice
        Graphics_Rectangle box = {.xMin = 3, .xMax = 125, .yMin = 3, .yMax = 125 };
        Graphics_drawRectangle(&g_sContext, &box);
        displayTime(currsecs);
        rightButton = P1IN & BIT1;
        if ((rightButton == 0) && (editbool == false)){
            editbool = true;
            edit();
        }
        while (avgcount < 10){
            temps[avgcount] = setADC12();
            avgcount ++;
        }
        if (avgcount == 10){
            avgcount = 0;
        }
        if (checksec == 9){
            temps[avgcount] = setADC12();
            float dispTempC = avg(temps);
            displayTemp(dispTempC);
            checksec = 0;

        }




    }  // end while (1)
}// end main

//Functions
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

void configLaunchpadButtons(){
    P1SEL &= ~(BIT1);
    P2SEL &= ~(BIT1);

    P1DIR &= ~(BIT1);
    P2DIR &= ~(BIT1);

    P1REN |= (BIT1);
    P2REN |= (BIT1);


    P1OUT |= (BIT1);
    P2OUT |= (BIT1);
}

void configTimerA2(){
    TA2CTL = TASSEL_1 | MC_1 | ID_0;
    TA2CCR0 = 32767;      //1 second
    TA2CCTL0 = CCIE;
}

void displayTime(long unsigned int inTime){
    //
    char dateFormat[] = {'M', 'M', 'M', ' ', 'D', 'D', '\0'};
    char timeFormat[] = {'H', 'H', ':', 'M', 'M', ':', 'S', 'S', '\0'};
    months = monthHa(inTime);
    howManyDays = (unsigned long int)inTime / 24L / 3600L;
    days = daysHa(howManyDays, months);
    inTime -= howManyDays * 24 * 3600;
    hrs = inTime / 3600L;
    inTime -= hrs * 3600L;
    mins = inTime / 60L;
    inTime -= mins * 60L;
    secs = inTime;
    if (months == 1){
        dateFormat[0] = 'J';
        dateFormat[1] = 'A';
        dateFormat[2] = 'N';
    }else if (months == 2){
        dateFormat[0] = 'F';
        dateFormat[1] = 'E';
        dateFormat[2] = 'B';
    }else if (months == 3){
        dateFormat[0] = 'M';
        dateFormat[1] = 'A';
        dateFormat[2] = 'R';
    }else if (months == 4){
        dateFormat[0] = 'A';
        dateFormat[1] = 'P';
        dateFormat[2] = 'R';
    }else if (months == 5){
        dateFormat[0] = 'M';
        dateFormat[1] = 'A';
        dateFormat[2] = 'Y';
    }else if (months == 6){
        dateFormat[0] = 'J';
        dateFormat[1] = 'U';
        dateFormat[2] = 'N';
    }else if (months == 7){
        dateFormat[0] = 'J';
        dateFormat[1] = 'U';
        dateFormat[2] = 'L';
    }else if (months == 8){
        dateFormat[0] = 'A';
        dateFormat[1] = 'U';
        dateFormat[2] = 'G';
    }else if (months == 9){
        dateFormat[0] = 'S';
        dateFormat[1] = 'E';
        dateFormat[2] = 'P';
    }else if (months == 10){
        dateFormat[0] = 'O';
        dateFormat[1] = 'C';
        dateFormat[2] = 'T';
    }else if (months == 11){
        dateFormat[0] = 'N';
        dateFormat[1] = 'O';
        dateFormat[2] = 'V';
    }else if (months == 12){
        dateFormat[0] = 'D';
        dateFormat[1] = 'E';
        dateFormat[2] = 'C';
    }
    dateFormat[4] = days/10 + 0x30;
    dateFormat[5] = days%10 + 0x30;
    //time
    timeFormat[0] = hrs/10 + 0x30;
    timeFormat[1] = hrs%10 + 0x30;
    timeFormat[3] = mins/10 + 0x30;
    timeFormat[4] = mins%10 + 0x30;
    timeFormat[6] = secs/10 + 0x30;
    timeFormat[7] = secs%10 + 0x30;
    //display
    Graphics_drawStringCentered(&g_sContext, (uint8_t*) dateFormat , AUTO_STRING_LENGTH, 50, 25, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, (uint8_t*) timeFormat , AUTO_STRING_LENGTH, 50, 45, OPAQUE_TEXT);
    Graphics_flushBuffer(&g_sContext);


}

unsigned long int monthHa(unsigned long int secs){
    unsigned long int daysGoneBy = (unsigned long int)secs / 3600L / 24L;

    if (daysGoneBy <= 30){
        mths = 1; //Jan
    }else if (31 <= daysGoneBy && daysGoneBy <= 58){
        mths = 2; //Feb
    }else if (59 <= daysGoneBy && daysGoneBy <= 89){
        mths = 3; //Mar
    }else if (90 <= daysGoneBy && daysGoneBy <= 119){
        mths = 4; //Apr
    }else if (120 <= daysGoneBy && daysGoneBy <= 150){
        mths = 5; //May
    }else if (151 <= daysGoneBy && daysGoneBy <= 180){
        mths = 6; //Jun
    }else if (181 <= daysGoneBy && daysGoneBy <= 211){
        mths = 7; //Jul
    }else if (212 <= daysGoneBy && daysGoneBy <= 242){
        mths = 8; //Aug
    }else if (243L <= daysGoneBy && daysGoneBy <= 272){
        mths = 9; //Sep
    }else if (273 <= daysGoneBy && daysGoneBy <= 303){
        mths = 10; //Oct
    }else if (304 <= daysGoneBy && daysGoneBy <= 333){
        mths = 11; //Nov
    }else if (334 <= daysGoneBy && daysGoneBy <= 364){
        mths = 12; //Dec
    }
    return mths;
}

unsigned long int daysHa(unsigned long int daysP, unsigned long int mths){

    if (mths == 1){
        todaysDay = daysP + 1; //Jan
    }else if (mths == 2){
        todaysDay = daysP - 31 + 1; //Feb
    }else if (mths == 3){
        todaysDay = daysP - 31 - 28 + 1; //Mar
    }else if (mths == 4){
        todaysDay = daysP - 31 - 28 - 31 + 1; //Apr
    }else if (mths == 5){
        todaysDay = daysP - 31 - 28 - 31 - 30 + 1; //May
    }else if (mths == 6){
        todaysDay = daysP - 31 - 28 - 31 - 30 - 31 + 1; //Jun
    }else if (mths == 7){
        todaysDay = daysP - 31 - 28 - 31 - 30 - 31 - 30 + 1; //Jul
    }else if (mths == 8){
        todaysDay = daysP - 31 - 28 - 31 - 30 - 31 - 30 - 31 + 1; //Aug
    }else if (mths == 9){
        todaysDay = daysP - 31 - 28 - 31 - 30 - 31 - 30 - 31 - 31 + 1; //Sep
    }else if (mths == 10){
        todaysDay = daysP - 31 - 28 - 31 - 30 - 31 - 30 - 31 - 31 - 30 + 1; //Oct
    }else if (mths == 11){
        todaysDay = daysP - 31 - 28 - 31 - 30 - 31 - 30 - 31 - 31 - 30 - 31 + 1; //Nov
    }else if (mths == 12){
        todaysDay = daysP - 31 - 28 - 31 - 30 - 31 - 30 - 31 - 31 - 30 - 31 - 30 + 1; //Dec
    }
    return todaysDay;
}

float setADC12(){
    float tempC;
    float res;
    unsigned int bits30, bits85;
    bits30 = CALADC12_15V_30C;
    bits85 = CALADC12_15V_85C;
    res = ((float)(85.0 - 30.0))/((float)bits85 - bits30);
    ADC12CTL0 |= ADC12SC;
    while (ADC12CTL1 & ADC12BUSY){
        __no_operation();
    }
    inputTemp = ADC12MEM1 & 0x0FFF;
    tempC = (float)((long)inputTemp - CALADC12_15V_30C) * res +30.0;
    return tempC;
}

float avg(float temp[10]){
    float avg1 = (temp[1] + temp[2] + temp[3] + temp[4] + temp[5]+ temp[6] + temp[6] + temp[7] + temp[8] + temp[9]) / 10;
    return avg1;
}

void displayTemp(float inAvgTempC){
    char tempC1[] = {'d', 'd', 'd', '.', 'f', 'C', '\0'};
    char tempF1[] = {'d', 'd', 'd', '.', 'f', 'F', '\0'};
    float tempFC = inAvgTempC * 1.8 + 32; // (9/5) + 32

    tempC1[0] = (int)inAvgTempC / 100 + 0x30;
    tempC1[1] = (int)inAvgTempC / 10 % 10 + 0x30;
    tempC1[2] = (int)inAvgTempC % 10 + 0x30;
    tempC1[4] = (int)(inAvgTempC * 10) % 10 + 0x30;

    tempF1[0] = (int)tempFC / 100 + 0x30;
    tempF1[1] = (int)tempFC / 10 % 10 + 0x30;
    tempF1[2] = (int)tempFC % 10 + 0x30;
    tempF1[4] = (int)(tempFC * 10) % 10 + 0x30;
    //display
    Graphics_drawStringCentered(&g_sContext, (uint8_t*) tempC1 , AUTO_STRING_LENGTH, 50, 65, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, (uint8_t*) tempF1 , AUTO_STRING_LENGTH, 50, 75, OPAQUE_TEXT);
    Graphics_flushBuffer(&g_sContext);

}

bool edit(){
    currentSel = 0;
    while (rightButton == 0){
        rightButton = P1IN & BIT1;
    }
    while (currentSel == 0 && rightButton != 0){
        rightButton = P1IN & BIT1;
        leftButton = P2IN & BIT1;
        if ((leftButton == 0) && months < 12){
            switch (months){
            case 1:
                currsecs += (32 - days) * 86400;
                break;
            case 2:
                currsecs += (29 - days) * 86400;
                break;
            case 3:
                currsecs += (32 - days) * 86400;
                break;
            case 4:
                currsecs += (31 - days) * 86400;
                break;
            case 5:
                currsecs += (32 - days) * 86400;
                break;
            case 6:
                currsecs += (31 - days) * 86400;
                break;
            case 7:
                currsecs += (32 - days) * 86400;
                break;
            case 8:
                currsecs += (32 - days) * 86400;
                break;
            case 9:
                currsecs += (31 - days) * 86400;
                break;
            case 10:
                currsecs += (32 - days) * 86400;
                break;
            case 11:
                currsecs += (31 - days) * 86400;
                break;
            }
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }
        else if ((leftButton == 0) && months == 12){
            currsecs -= 28857599;
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }
    }
    currentSel++;
    while (rightButton == 0){
        rightButton = P1IN & BIT1;
    }
    while (currentSel == 1 && rightButton != 0){
        rightButton = P1IN & BIT1;
        leftButton = P2IN & BIT1;
        if ((leftButton == 0) && days < 28){
            currsecs += 86400;
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }
        else if ((leftButton == 0) && days >= 28){
            switch (months){
            case 1:
                if (days == 31){
                    currsecs -= 2591999; //31 Days
                }else{
                    currsecs += 86400;
                }
                break;
            case 2:
                if (days == 28){
                    currsecs -= 2332799; //28 Days
                }else{
                    currsecs += 86400;
                }
                currsecs -= 2419200; //28 Days
                break;
            case 3:
                if (days == 31){
                    currsecs -= 2591999; //31 Days
                }else{
                    currsecs += 86400;
                }
                break;
            case 4:
                if (days == 30){
                    currsecs -= 2505599; //30 Days
                }else{
                    currsecs += 86400;
                }
                break;
            case 5:
                if (days == 31){
                    currsecs -= 2591999; //31 Days
                }else{
                    currsecs += 86400;
                }
                break;
            case 6:
                if (days == 30){
                    currsecs -= 2505599; //30 Days
                }else{
                    currsecs += 86400;
                }
                break;
            case 7:
                if (days == 31){
                    currsecs -= 2591999; //31 Days
                }else{
                    currsecs += 86400;
                }
                break;
            case 8:
                if (days == 31){
                    currsecs -= 2591999; //31 Days
                }else{
                    currsecs += 86400;
                }
                break;
            case 9:
                if (days == 30){
                    currsecs -= 2505599; //30 Days
                }else{
                    currsecs += 86400;
                }
                break;
            case 10:
                if (days == 31){
                    currsecs -= 2591999; //31 Days
                }else{
                    currsecs += 86400;
                }
                break;
            case 11:
                if (days == 30){
                    currsecs -= 2505599; //30 Days
                }else{
                    currsecs += 86400;
                }
                break;
            }
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }
    }
    currentSel++;
    while (rightButton == 0){
        rightButton = P1IN & BIT1;
    }
    while (currentSel == 2 && rightButton != 0){
        rightButton = P1IN & BIT1;
        leftButton = P2IN & BIT1;
        if ((leftButton == 0) && hrs < 23){
            currsecs += 3600;
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }else if ((leftButton == 0) && hrs == 23){
            currsecs -= 82800;
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }
    }
    currentSel++;
    while (rightButton == 0){
        rightButton = P1IN & BIT1;
    }
    while (currentSel == 3 && rightButton != 0){
        rightButton = P1IN & BIT1;
        leftButton = P2IN & BIT1;
        if ((leftButton == 0) && mins < 59){
            currsecs += 60;
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }else if ((leftButton == 0) && mins == 59){
            currsecs -= 3540;
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }
    }
    currentSel++;
    while (rightButton == 0){
        rightButton = P1IN & BIT1;
    }
    while (currentSel == 4 && rightButton != 0){
        rightButton = P1IN & BIT1;
        leftButton = P2IN & BIT1;
        if ((leftButton == 0) && secs < 59){
            currsecs++;
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }else if ((leftButton == 0) && secs == 59){
            currsecs -= 59;
            while (leftButton == 0){
                leftButton = P2IN & BIT1;
            }
        }
    }
    while (rightButton == 0){
        rightButton = P1IN & BIT1;
    }
    Graphics_clearDisplay(&g_sContext); // Clear the display
    //editbool = false;
    return true;
}
