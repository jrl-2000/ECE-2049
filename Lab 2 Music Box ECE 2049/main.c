/************** ECE 2049 LAB 2 CODE ******************/
/**************  17   February   2021   ******************/
/*************    Jonathan Lopez   ******************/
/***************************************************/
#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <notes.h>
#include <songs.h>


/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

typedef enum State
{
    WELCOME_SCREEN,
    WAIT_FOR_START,
    SELECTION,
    WAIT_SELECT,
    START_CNT_DOWN,
    CNT_DOWN_SC,
    START_PLAYING,
    PLAYING,
    PAUSED,
    RESET
}State;
//Global Variables
int currentSec;
char songOne[13] = "Midnight City";
char songTwo[13] = "Frame of Mind";
char songOneArtist[3] = "M83";
char songTwoArtist[15] = "Tristam, Braken";
int selection = 0;
int clock;
int leap = 0;
char countdown = 0;
int maxcount;
char countdownState = 0;
int note = 0;
int noteCount = 0;
int delay1 = 0;

// Function Prototypes
void swDelay(char numLoops);
void configUserLED(char inbits);
void welcomeSC();
bool drawCountdown(int time);
void drawSelection();
void drawPlaying(int selection);
void drawPaused(int selection);
void configTimerA2(int max);
void fasterSlower(int modifier, int maxc);
void setLEDs(unsigned char);
void configSmolLEDs();
void setSmolLEDs(unsigned char);



#pragma vector=TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void)
{
    if (leap < 141){
        clock++;
        leap++;
    }else{
        clock += 2;
        leap = 0;
    }
    if (clock % 200 == 0){
        currentSec++;
    }
}
// Main
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
    // You can then configure it properly, if desired
    unsigned char keyPressed = 0, lastKey = 0;
    unsigned long startTime, deltaTime;
    maxcount = 163;

    bool shouldPlay = false;
    int notecounter = 0;

    State state = WELCOME_SCREEN;

    Song currentSong;
    Note currentNote;

    //setup functions
    initLeds();
    configDisplay();
    configKeypad();
    configTimerA2(maxcount);
    //timer count and delay it does while timer count < start at +plus delay empty while loop
    while (1)    // Forever loop
    {
        // Check if any keys have been pressed on the 3x4 keypad
        keyPressed = getKey();

        if (keyPressed == '#' && state != WAIT_FOR_START)
        {
            state = RESET;
        }
        if(keyPressed == '1'&& state == PLAYING){
            lastKey = '1';
            state = PAUSED;
        }else if(keyPressed == '2' && state == PLAYING){
            lastKey = '2';
            fasterSlower(5, maxcount);
        }else if(keyPressed == '2'&& lastKey == '2' && state == PLAYING){
            lastKey = 0;
            fasterSlower(7, maxcount);
        }else if(keyPressed == '3' && state == PLAYING){
            lastKey = '3';
            fasterSlower(3, maxcount);
        }else if(keyPressed == '3'&& lastKey == '3' && state == PLAYING){
            lastKey = 0;
            fasterSlower(1, maxcount);
        }else if(keyPressed =='4' && state == PLAYING){
            state = SELECTION;
        }

        switch(state)
        {
        case WELCOME_SCREEN:
            welcomeSC();
            state = WAIT_FOR_START;
            break;
        case WAIT_FOR_START:
            if (keyPressed == '*')
            {
                state = SELECTION;
            }
            break;
        case SELECTION:
            Graphics_clearDisplay(&g_sContext); // Clear the display
            drawSelection();
            state = WAIT_SELECT;

            break;
        case WAIT_SELECT:
            if (keyPressed == '1')
            {
                selection = 1;
                noteCount = 513;
                state = START_CNT_DOWN;
            }else if(keyPressed == '2')
            {
                selection = 2;
                noteCount = 100;
                state = START_CNT_DOWN;
            }
            break;
        case START_CNT_DOWN:

            startTime = clock;
            state = CNT_DOWN_SC;
            break;
        case CNT_DOWN_SC:
            deltaTime = clock - startTime;
            if (drawCountdown(deltaTime))
            {
                state = START_PLAYING;
            }
            break;
        case START_PLAYING:
            drawPlaying(selection);
            if (selection == 1){
                currentSong = midnightCity;
            }else if(selection == 2){
                currentSong = frameOfMind;
            }
            currentNote = currentSong.notes[0];
            BuzzerPWM(currentNote.frequency);
            startTime = clock;
            state = PLAYING;
            break;
        case PLAYING:

            deltaTime = clock - startTime;


            if (shouldPlay && deltaTime > (currentSong.noteDuration * currentNote.duration/ 5)){

                BuzzerOff();
                shouldPlay = false;
                startTime = clock; // Reset the timer
            }


            else if (!shouldPlay && deltaTime > (currentSong.silenceDuration / 5)){
                notecounter++;
                currentNote = currentSong.notes[notecounter % currentSong.noteCount];


                if (notecounter == currentSong.noteCount)
                {
                    notecounter = 0;
                    state = START_PLAYING;
                }


                BuzzerPWM(currentNote.frequency);
                setSmolLEDs(0); //song loops
                shouldPlay = true;
                startTime = clock;

            }

            break;

        case PAUSED:
            BuzzerOff();
            drawPaused(selection);
            delay1 = clock;

            if(keyPressed == '1' && lastKey == '1'){
                state = PLAYING;
                deltaTime = clock - delay1;
                lastKey = 0;

            }


            break;

        case RESET:
            BuzzerOff();
            state = WELCOME_SCREEN;

            maxcount = 163;
            notecounter = 0;

            break;

        } // end switch



    }  // end while (1)
} //  end main


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

    volatile unsigned int i,j;  // volatile to prevent removal in optimization
    // by compiler. Functionally this is useless code

    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;                 // SW Delay
        while (i > 0)               // could also have used while (i)
            i--;
    }
}
void configUserLED(char inbits) //Pre Lab 2
{
    if ((inbits & BIT0) == 0x01){
        P1OUT |= BIT0;
    }
    if ((inbits & BIT1) == 0x02){
        P4OUT |= BIT7;
    }
}


//no swdelays anymore
bool drawCountdown(int timePassed)
{

    if (countdownState == 0 && timePassed > 0)
    {
        Graphics_clearDisplay(&g_sContext); // Clear the display
        Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48,
                                    50, TRANSPARENT_TEXT);
        setLEDs(BIT3);
        setSmolLEDs(BIT0);
        Graphics_flushBuffer(&g_sContext);
        countdownState = 1;
    }
    else if (countdownState == 1 && timePassed > 200)
    {
        Graphics_clearDisplay(&g_sContext); // Clear the display
        Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48,
                                    50, TRANSPARENT_TEXT);
        setLEDs(BIT2);
        setSmolLEDs(BIT1);
        Graphics_flushBuffer(&g_sContext);
        countdownState = 2;
    }
    else if (countdownState == 2 && timePassed > 400)
    {
        Graphics_clearDisplay(&g_sContext); // Clear the display
        Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 48,
                                    50, TRANSPARENT_TEXT);
        setLEDs(BIT1);
        setSmolLEDs(BIT0);
        Graphics_flushBuffer(&g_sContext);
        countdownState = 3;
    }
    else if (countdownState == 3 && timePassed > 600)
    {
        Graphics_clearDisplay(&g_sContext); // Clear the display
        Graphics_drawStringCentered(&g_sContext, "Go!", AUTO_STRING_LENGTH, 48,
                                    50, TRANSPARENT_TEXT);
        setLEDs(BIT3 | BIT2 | BIT1 | BIT0);
        setSmolLEDs(BIT1 | BIT0);
        Graphics_flushBuffer(&g_sContext);
        countdownState = 4;
    }
    else if (countdownState == 4 && timePassed > 800)
    {
        Graphics_clearDisplay(&g_sContext); // Clear the display
        Graphics_flushBuffer(&g_sContext);
        setLEDs(0);
        setSmolLEDs(0);
        return true;
    }
    return false;
}

void welcomeSC()
{
    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display

    Graphics_drawStringCentered(&g_sContext, "Welcome", AUTO_STRING_LENGTH, 48,
                                25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "Press *", AUTO_STRING_LENGTH, 48,
                                70, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "to Start", AUTO_STRING_LENGTH, 48,
                                80, TRANSPARENT_TEXT);

    // Draw a box around everything because it looks nice
    Graphics_Rectangle box = {.xMin = 3, .xMax = 125, .yMin = 3, .yMax = 125 };
    Graphics_drawRectangle(&g_sContext, &box);

    // We are now done writing to the display.  However, if we stopped here, we would not
    // see any changes on the actual LCD.  This is because we need to send our changes
    // to the LCD, which then refreshes the display.
    // Since this is a slow operation, it is best to refresh (or "flush") only after
    // we are done drawing everything we need.
    Graphics_flushBuffer(&g_sContext);
}
void drawSelection(){


    Graphics_drawStringCentered(&g_sContext, "Pick a song.", AUTO_STRING_LENGTH, 50,
                                15, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "1. Midnight City", AUTO_STRING_LENGTH, 60,
                                30, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "2. Frame of Mind", AUTO_STRING_LENGTH, 60,
                                45, TRANSPARENT_TEXT);

    // Draw a box around everything because it looks nice
    Graphics_Rectangle box = {.xMin = 3, .xMax = 125, .yMin = 3, .yMax = 125 };
    Graphics_drawRectangle(&g_sContext, &box);

    // We are now done writing to the display.  However, if we stopped here, we would not
    // see any changes on the actual LCD.  This is because we need to send our changes
    // to the LCD, which then refreshes the display.
    // Since this is a slow operation, it is best to refresh (or "flush") only after
    // we are done drawing everything we need.
    Graphics_flushBuffer(&g_sContext);
}
void configTimerA2(int max){
    TA2CTL = TASSEL_1 + ID_0 + MC_1;
    TA2CCR0 = max + 1;
    TA2CCTL0 = CCIE;
    _BIS_SR(GIE);
}
void drawPlaying(int selection){
    Graphics_clearDisplay(&g_sContext); // Clear the display

    Graphics_drawStringCentered(&g_sContext, "Playing", AUTO_STRING_LENGTH, 50,
                                15, TRANSPARENT_TEXT);
    if (selection == 1){
        Graphics_drawStringCentered(&g_sContext, "Midnight City", AUTO_STRING_LENGTH, 50,
                                    25, TRANSPARENT_TEXT);
    }else if(selection == 2){
        Graphics_drawStringCentered(&g_sContext, "Frame of Mind", AUTO_STRING_LENGTH, 50,
                                    25, TRANSPARENT_TEXT);
    }
    Graphics_drawStringCentered(&g_sContext, "1 to Pause/Play", AUTO_STRING_LENGTH, 50,
                                35, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "2 to speed up", AUTO_STRING_LENGTH, 50,
                                45, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "3 to slow down", AUTO_STRING_LENGTH, 50,
                                55, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "4 Return", AUTO_STRING_LENGTH, 50,
                                65, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);

}
void drawPaused(int selection){
    Graphics_clearDisplay(&g_sContext); // Clear the display

    Graphics_drawStringCentered(&g_sContext, "Paused", AUTO_STRING_LENGTH, 50,
                                15, TRANSPARENT_TEXT);

    if (selection ==1){
        Graphics_drawStringCentered(&g_sContext, "Midnight City", AUTO_STRING_LENGTH, 50,
                                    25, TRANSPARENT_TEXT);
    }else if(selection ==2){
        Graphics_drawStringCentered(&g_sContext, "Frame of Mind", AUTO_STRING_LENGTH, 50,
                                    25, TRANSPARENT_TEXT);
    }
    Graphics_drawStringCentered(&g_sContext, "1 to Pause/Play", AUTO_STRING_LENGTH, 50,
                                35, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "2 to speed up", AUTO_STRING_LENGTH, 50,
                                45, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "3 to slow down", AUTO_STRING_LENGTH, 50,
                                55, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "4 Return", AUTO_STRING_LENGTH, 50,
                                65, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);
}
void fasterSlower(int modifier, int maxc){
    if (modifier == 5){
        maxc = maxc /2;
    }else if (modifier == 7){
        maxc = maxc / 4;
    } else if (modifier == 3){
        maxc = maxc * 2;
    } else if (modifier == 1){
        maxc = maxc * 4;
    }

}
void setLEDs(unsigned char state)
{
    unsigned char mask = 0;

    // Turn all LEDs off to start
    P6OUT &= ~(BIT4 | BIT3 | BIT2 | BIT1);

    if (state & BIT0){
        mask |= BIT4;
    }
    if (state & BIT1){
        mask |= BIT3;
    }
    if (state & BIT2){
        mask |= BIT1;
    }
    if (state & BIT3){
        mask |= BIT2;
    }
    P6OUT |= mask;
}

void configSmolLEDs()
{

    P1SEL &= ~(BIT0);
    P1DIR |= BIT0;
    P1OUT &= ~(BIT0);

    P4SEL &= ~(BIT7);
    P4DIR |= BIT7;
    P4OUT &= ~(BIT7);
}

void setSmolLEDs(unsigned char outputState)
{

    if (outputState & BIT0){
        P1OUT |= BIT0;
    }else{
        P1OUT &= ~BIT0;
    }
    if (outputState & BIT1){
        P4OUT |= BIT7;

    }else{
        P4OUT &= ~BIT7;
    }
}

//bool drawCountdown()
//{
//
//
//    Graphics_clearDisplay(&g_sContext); // Clear the display
//    Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48,
//                                50, TRANSPARENT_TEXT);
//    Graphics_flushBuffer(&g_sContext);
//    swDelay(2);
//
//    Graphics_clearDisplay(&g_sContext); // Clear the display
//    Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48,
//                                50, TRANSPARENT_TEXT);
//
//    Graphics_flushBuffer(&g_sContext);
//    swDelay(2);
//
//    Graphics_clearDisplay(&g_sContext); // Clear the display
//    Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 48,
//                                50, TRANSPARENT_TEXT);
//    Graphics_flushBuffer(&g_sContext);
//    swDelay(2);
//
//    Graphics_clearDisplay(&g_sContext); // Clear the display
//
//    return true;
//
//}

