/* Compiler directives (includes and defines) */

//Jonathan Lopez ECE 2049 Homework 2 question 3
#include "msp430.h"
/* Function prototypes */
void setupP2_P3();
void in2_out3();
/*** Implement your functions here ***/
void setupP2_P3(){
    P3SEL = P3SEL & (BIT3 | BIT2 | BIT1 | BIT0); //P3SEL=0000 xxxx
    P3DIR = P3DIR | (BIT7 | BIT6 | BIT5 | BIT4); //P3DIR=1111 xxxx
    P2SEL &= ~(BIT7 | BIT6 | BIT5 | BIT4);  //P2SEL=0000 xxxx
    // Below is another equivalent way to set Pins 7-4 to 0
    P2DIR &= (BIT3 | BIT2 | BIT1 | BIT0);   //P2DIR=0000 xxxx
    P2REN = P2REN | (BIT7 | BIT6 | BIT5 | BIT4); //P2REN=1111 xxxx
    P2OUT = P2OUT & ~(BIT7| BIT6 | BIT5 | BIT4); //P2OUT=0000 xxxx
}
void in2_out3(){
    char input;
    // Read in from P2.7-4 and set low nibble to 0000
    // (because we're not using it)
    input = P2IN & (BIT7|BIT6|BIT5|BIT4); // **** 0000

    // Set all 4 output bits P3.7-4 to 0 to start
    P3OUT &= ~(BIT7| BIT6 | BIT5 | BIT4); // 0000 xxxx
    P3OUT |= input;  // now set them to whatever value input has
}
void main(){
    WDTCTL = WDTPW | WDTHOLD;
    // Stop watchdog timer
    setupP2_P3();
    in2_out3();
    // P2IN = 0xB4 => P3OUT = 0xB(*)
    // P2IN = 0x8F => P3OUT =  0x8(*)
    // where * represent preserved bits for P3OUT
    // P3IN and P2OUT will not affect P2IN and P3OUT since P3
    // is an output and P2 is an input. They are not using
    // those data registers.}
}
