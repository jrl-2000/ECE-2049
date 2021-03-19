//Question 2a
#include "msp430.h"
#include <stdlib.h>
#define MAX_PTS 300 // sets a global variable named MAX_PTS to 300

//ECE 2049 C21 Homework 2 Question 2a

// IMPORTANT: PUT YOUR NAME AND ECE BOX NUMBER HERE!!!
//Jonathan Lopez ECE Mailbox # 178

//Question 2 (a and b):

//i. Add a comment to each line of code below saying what it does.

//ii. Run these 2 simple programs in Code Composer Studio. Take a screen capture of each
//being run in the debugger.

//iii. Comment on the efficiency (both memory space and run-time) of the integer math
//program vs the floating point program.

void main(void)
{ // Give total size (in bytes) of these variables as declared
    int in[MAX_PTS]; //declares and array of integers called in to the size 300 as declared as a global variable.
    float out[MAX_PTS]; //declares and array of floats to the size 300 as declared as a global variable.
    volatile int i, a, SPAN=2500, OFFSET=499, M=8; //declares i,1,SPAN, OFFSET, and M as volatile integers meaning the value can change at any time by the code the compiler finds nearby
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    for (i = 0; i < MAX_PTS; i++) //for loop for i starting @ 0 until i is less than 300 (MAX_PTS)
    {
        in[i] = (rand() % SPAN) - OFFSET; //fills in with random numbers between and -499 and 2001
        if (i < M) // if i < M which is 8,
            out[i] = 0.0; //the i-th array of out out (floats) is 0.0
        else //if i >= M
        {
            out[i] = 0.0; //sets the i-th array to 0.0
            for (a = 0; a < M; a++) //for a < M (or 8)
                out[i] += (float)in[i-a]; //the i-th value of the array out = the value itself plus (the type float) of the array in with the value of the both indices subtracted from each other.
            out[i] = out[i]/M; //the i-th array of out = itself divided by M which is 8
        }
    }
}
