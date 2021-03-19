//Question 2b
#include "msp430.h"
#include <stdlib.h>
#define MAX_PTS 300 //global variable MAX_PT assigned to 300
#define M 8 //global variable M assigned to 8
#define SHIFT 3 //global variable SHIFT assigned to 3
#define SPAN 2500 //global variable SPAN assigned to 2500
#define OFFSET 499 //global variable OFFSET assigned to 499

//ECE 2049 C21 Homework 2 Question 2b

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
    int in[MAX_PTS]; //array of integers with the array length of 300 called in
    int out[MAX_PTS]; //array of integers with the array length of 300 called out
    volatile int i,a; //declaration of volatile integers i and a not assigned to anything right now
    long int sum; // declaration of a long integer
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    for (i = 0; i < MAX_PTS; i++) // for loop; for i < 300 starting at 0 and i increases every time
    {
        in[i] = (rand() % SPAN) - OFFSET; //for the i-th value of the array "in" set it to a random number between -499 and 2001
        if (i < M) // if the index "i" is less than M (which is globally declared as 8)
            out[i] = 0; // the value of i-th value of "out" is 0
        else //if i >= 8
        {
            sum = 0; //assignment for the long int sum is set to 0
            for (a = 0; a < M; a++) //for loop; for a < 8; a++ increases every time
                sum += in[i-a]; //the long int sum = itself Plus the (i-a)-th value of the array "in"
            out[i] = sum >> SHIFT; //the i-th value of the array "out" is shifted by the shift value which is 3 (global variable). It is shifted to the right as denoted by ">>"
        }
    }
}
