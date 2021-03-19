// Library to include with MSP430 definitions
#include <msp430.h>
// Function prototypes
void switchConfig();
char switchIO();

/** Main function for application*/

void main(void){
    WDTCTL = WDTPW + WDTHOLD; // Disable watchdog timer// Configure input switches
    switchConfig();// Get value of input switches
    char in_val = switchIO();
}

/** Return value of 4 switches interpreted as a binary nibble* P2.6 = MSB* P2.3 = LSB*/

char switchIO(){
    // Define result variable - set to zero
    char result;// Read in switch inputs
    result = P2IN & 0x78; // Only want bits 6 down to 3 (01111000)
    // Shift value 3 bits to the right to map into range 0 to F
    result = result >> 3;// Return result value to caller
    return result;
}

/** Configure Pins 2.6 down to 2.3 as digital input*/
void switchConfig(){
    // Configure pins for GPIO mode
    P2SEL &= ~(BIT6|BIT5|BIT4|BIT3);// Configure pins for input mode (0 == input)
    P2DIR &= ~(BIT6|BIT5|BIT4|BIT3);// Disable internal pull resistors for pins
    P2REN &= ~(BIT6|BIT5|BIT4|BIT3);
}
