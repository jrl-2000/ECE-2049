/************** ECE 2049 LAB 4 CODE ******************/
/**************  10   March   2021   ******************/
/*************    Jonathan Lopez   ******************/
/***************************************************/

// Includes
#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

//This is to use for slave configurations
#define SLAVE_PORT_SPI_SEL P4SEL
#define SLAVE_PORT_SPI_DIR P4DIR
#define SLAVE_PORT_SPI_OUT P4OUT
#define SLAVE_PORT_CS_SEL P4SEL
#define SLAVE_PORT_CS_DIR P4DIR
#define SLAVE_PORT_CS_OUT P4OUT
#define SLAVE_PORT_CS_REN P4REN
#define SLAVE_PIN_SPI_MOSI BIT1
#define SLAVE_PIN_SPI_MISO BIT2
#define SLAVE_PIN_SPI_SCLK BIT3
#define SLAVE_PIN_SPI_CS BIT0
#define SLAVE_SPI_REG_CTL0 UCB1CTL0
#define SLAVE_SPI_REG_CTL1 UCB1CTL1
#define SLAVE_SPI_REG_BRL UCB1BR0
#define SLAVE_SPI_REG_BRH UCB1BR1
#define SLAVE_SPI_REG_IFG UCB1IFG
#define SLAVE_SPI_REG_STAT UCB1STAT
#define SLAVE_SPI_REG_TXBUF UCB1TXBUF
#define SLAVE_SPI_REG_RXBUF UCB1RXBUF
//This is needed to configure P8.2 to use it as CS by MSP430
#define MSP_PORT_CS_SEL P8SEL
#define MSP_PORT_CS_DIR P8DIR
#define MSP_PORT_CS_OUT P8OUT
#define MSP_PIN_CS BIT2
#define MSP_SPI_REG_TXBUF       UCB0TXBUF
#define MSP_SPI_REG_RXBUF       UCB0RXBUF
#define MSP_SPI_REG_IFG         UCB0IFG

//Global Variables
unsigned long int months, days, hrs, mins, secs, howManyDays;
unsigned long int todaysDay;
unsigned long int mths;
unsigned long int currsecs = 0; //2;
float volts;
float volts1;
long unsigned int idkyet;
unsigned char idkyet1[4];
unsigned char w = 0x55;
unsigned char r = 0x11;
unsigned char bytes[4];
char voltageFormat[] = {'V', 'o', 'l', 't', 'a', 'g', 'e', ':', ' ','V', '.', 'D', ' ', 'V', 'o', 'l', 't', 's', '\0'};
//Function Prototypes
void swDelay(char numLoops);
void configTimerA2();
void displayTime(long unsigned int inTime);
float potVolts();
void configADC12();
void configLaunchpadButtons();
void displayVolts(float in);
void breakUpFloat(float in);
void unionFloat(float in);

//DOROZ FUNCTIONS
void InitSlaveSPI();
unsigned char SlaveSPIRead();
void MasterSPIWrite (unsigned int data);

//ISR
#pragma vector = TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void)
{
    currsecs++;

}

// Main
void main(void){
    _BIS_SR(GIE);
    // Global Interrupt enable
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
    // You can then configure it properly, if desired

    // Init code
    initLeds();
    configDisplay();
    configKeypad();
    configTimerA2();
    configADC12();
    InitSlaveSPI();

    //varibles
    unsigned int timer_cpy1;
    unsigned int timer_cpy2;
    unsigned int timer_cpy3;
    unsigned int timer_cpy4;
    long unsigned int timer_cpy;
    float voltsCopy;
    //float voltsVer;
    while (1){    // Forever loop

        Graphics_Rectangle box = {.xMin = 3, .xMax = 125, .yMin = 3, .yMax = 125 };
        Graphics_drawRectangle(&g_sContext, &box);

        // test SPI code
        MasterSPIWrite(w);
        r = SlaveSPIRead();
        // r should be 0x55

        //long unsigned in is 32 bits
        // 32/8 = 4
        //floats are 32 bits as well
        //need 4 bytes to get the memory across

        volts1 = potVolts(); //gets the voltage in a float

        //TIME
        idkyet = 0x00000000;
        timer_cpy = currsecs;
        timer_cpy1 = (timer_cpy & 0xFF000000)>>24;
        timer_cpy2 = (timer_cpy & 0x00FF0000)>>16;
        timer_cpy3 = (timer_cpy & 0x0000FF00)>>8;
        timer_cpy4 = (timer_cpy & 0x000000FF);

        MasterSPIWrite(timer_cpy1);
        idkyet  |= ((long unsigned int) (SlaveSPIRead()) << 24);
        MasterSPIWrite(timer_cpy2);
        idkyet  |= ((long unsigned int) (SlaveSPIRead()) << 16);
        MasterSPIWrite(timer_cpy3);
        idkyet  |= ((long unsigned int) (SlaveSPIRead()) << 8);
        MasterSPIWrite(timer_cpy4);
        idkyet  |= ((long unsigned int) (SlaveSPIRead()));

        //VOLTAGE
        voltsCopy = volts1;
        breakUpFloat(voltsCopy);
        //bytes now set
        //SPI time
        MasterSPIWrite(bytes[0]);
        idkyet1[0]  |= ((long unsigned int) (SlaveSPIRead()) << 24);
        MasterSPIWrite(bytes[1]);
        idkyet1[1]  |= ((long unsigned int) (SlaveSPIRead()) << 16);
        MasterSPIWrite(bytes[2]);
        idkyet1[2]  |= ((long unsigned int) (SlaveSPIRead()) << 8);
        MasterSPIWrite(bytes[3]);
        idkyet1[3]  |= ((long unsigned int) (SlaveSPIRead()));


        //DISPLAY THE VOLTS AND TIMER
        displayVolts(volts1);
        displayTime(currsecs);
        //Graphics_drawStringCentered(&g_sContext, "Voltage:" , AUTO_STRING_LENGTH, 50, 65, OPAQUE_TEXT);
        Graphics_flushBuffer(&g_sContext);
    }  // end while (1)
}// end main

void swDelay(char numLoops){
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

    for (j=0; j<numLoops; j++){
        i = 50000 ;					// SW Delay
        while (i > 0)				// could also have used while (i)
            i--;
    }
}

void configTimerA2(){
    TA2CTL = TASSEL_1 | MC_1 | ID_0;
    TA2CCR0 = 32767;      //1 second
    TA2CCTL0 = CCIE;
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

void displayTime(long unsigned int inTime){
    char timeFormat[] = {'H', 'H', ':', 'M', 'M', ':', 'S', 'S', '\0'};
    howManyDays = (unsigned long int)inTime / 24L / 3600L;
    inTime -= howManyDays * 24 * 3600;
    hrs = inTime / 3600L;
    inTime -= hrs * 3600L;
    mins = inTime / 60L;
    inTime -= mins * 60L;
    secs = inTime;
    //time
    timeFormat[0] = hrs/10 + 0x30;
    timeFormat[1] = hrs%10 + 0x30;
    timeFormat[3] = mins/10 + 0x30;
    timeFormat[4] = mins%10 + 0x30;
    timeFormat[6] = secs/10 + 0x30;
    timeFormat[7] = secs%10 + 0x30;
    //display
    Graphics_drawStringCentered(&g_sContext, (uint8_t*) timeFormat , AUTO_STRING_LENGTH, 60, 45, OPAQUE_TEXT);
    Graphics_flushBuffer(&g_sContext);
}

void displayVolts(float in){
    unsigned int V1, V2;
    float V3;
    V1 = (unsigned int) in;
    V3 = in * 10;
    V2 = (unsigned int) V3;
    voltageFormat[9] = V1 + 0x30;
    voltageFormat[11] = V2%10 + 0x30;
    Graphics_drawStringCentered(&g_sContext, (uint8_t*) voltageFormat , AUTO_STRING_LENGTH, 65, 65, OPAQUE_TEXT);
    Graphics_flushBuffer(&g_sContext);
}

void configADC12(){
    REFCTL0 &= ~REFMSTR;
    ADC12CTL0 = ADC12SHT0_9 | ADC12REFON | ADC12ON ;
    ADC12CTL1 = ADC12SHP;
    P6SEL |= BIT4;
    ADC12MCTL0 = ADC12SREF_0 | ADC12INCH_4;
    __delay_cycles(100);
    ADC12CTL0 |= ADC12ENC;
}

float potVolts(){
    float voltsHere;
    ADC12CTL0 &~ ADC12SC;
    ADC12CTL0 |= ADC12SC;
    while (ADC12CTL1 & ADC12BUSY)
        __no_operation();
    volatile float potReading = ADC12MEM0 & 0x0FFF;
    voltsHere = ((potReading/4095) * 3.3);
    return voltsHere;
}

void breakUpFloat(float in){
    unsigned char c[sizeof in];
    memcpy(c, &in, sizeof in);
    c[0] = bytes[0];
    c[1] = bytes[1];
    c[2] = bytes[2];
    c[3] = bytes[3];
}

//CODE PROF. DOROZ GAVE US
void InitSlaveSPI(){
    // Configure SCLK, MISO and MOSI for peripheral mode
    SLAVE_PORT_SPI_SEL |=
            (SLAVE_PIN_SPI_MOSI|SLAVE_PIN_SPI_MISO|SLAVE_PIN_SPI_SCLK);
    // Configure the Slave CS as an Input P4.0
    SLAVE_PORT_CS_SEL &= ~SLAVE_PIN_SPI_CS;
    SLAVE_PORT_CS_DIR &= ~SLAVE_PIN_SPI_CS;
    SLAVE_PORT_CS_REN |= SLAVE_PIN_SPI_CS;
    SLAVE_PORT_CS_OUT |= SLAVE_PIN_SPI_CS;
    // Configure the CS output of MSP430 P8.2. It will set P4.0 high or low.
    MSP_PORT_CS_SEL &= ~MSP_PIN_CS;
    MSP_PORT_CS_DIR |= MSP_PIN_CS;
    MSP_PORT_CS_OUT |= MSP_PIN_CS;
    // Disable the module so we can configure it
    SLAVE_SPI_REG_CTL1 |= UCSWRST;
    SLAVE_SPI_REG_CTL0 &= ~(0xFF); // Reset the controller config parameters
    SLAVE_SPI_REG_CTL1 &= ~UCSSEL_3; // Reset the clock configuration
    // Set SPI clock frequency (which is the same frequency as SMCLK so this can apparently be 0)
    SPI_REG_BRL = ((uint16_t)SPI_CLK_TICKS) & 0xFF; // Load the low byte
    SPI_REG_BRH = (((uint16_t)SPI_CLK_TICKS) >> 8) & 0xFF; // Load the high byte
    //capture data on first edge
    //inactive low polarity
    //MSB first
    //8 bit
    //Slave Mode//
    //4 wire - SPI active low
    //Synchronous mode
    SLAVE_SPI_REG_CTL0 |= UCCKPH + UCMSB + UCMODE_2 + UCSYNC;
    // Reenable the module
    SLAVE_SPI_REG_CTL1 &= ~UCSWRST;
    SLAVE_SPI_REG_IFG &= ~UCRXIFG;
}

unsigned char SlaveSPIRead(){
    unsigned char c;
    while (!(SLAVE_SPI_REG_IFG & UCRXIFG)){
        c = SLAVE_SPI_REG_RXBUF;
    }
    return (c & 0xFF);
}

void MasterSPIWrite (unsigned int data){
    // Start SPI transmission by de-asserting CS
    MSP_PORT_CS_OUT &= ~(MSP_PIN_CS);
    // Write data/ 1-byte at a time
    uint8_t byte = (unsigned char) ((data)&0xFF);
    // Send byte
    MSP_SPI_REG_TXBUF = byte;
    // Wait for SPI peripheral to finish transmitting
    while (!(MSP_SPI_REG_IFG & UCTXIFG)) {
        _no_operation();
    }
    // Assert CS
    MSP_PORT_CS_OUT |= MSP_PIN_CS;
}
