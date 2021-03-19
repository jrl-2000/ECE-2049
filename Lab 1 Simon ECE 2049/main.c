/************** ECE2049 LAB 1 CODE ******************/
/**************  17 February   2021   ******************/
/*************    Jonathan Lopez   ******************/
/***************************************************/

#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"
#define SEQUENCE 10


typedef enum State
{
    WELCOME_SCREEN,
    WAIT_FOR_START,
    START_CNT_DOWN,
    CNT_DOWN_SC,
    START,
    PLAYING0,
    DISPLAY0,
    DISPLAY1,
    PLAYING1,
    DISPLAY2,
    PLAYING2,
    DISPLAY3,
    PLAYING3,
    DISPLAY4,
    PLAYING4,
    DISPLAY5,
    PLAYING5,
    DISPLAY6,
    PLAYING6,
    DISPLAY7,
    PLAYING7,
    DISPLAY8,
    PLAYING8,
    DISPLAY9,
    PLAYING9,
    PLAYING10,
    DISPLAY10,
    DISPLAY11,
    PLAYING11,
    DISPLAY12,
    PLAYING12,
    DISPLAY13,
    PLAYING13,
    DISPLAY14,
    PLAYING14,
    DISPLAY15,
    PLAYING15,
    DISPLAY16,
    PLAYING16,
    DISPLAY17,
    PLAYING17,
    DISPLAY18,
    PLAYING18,
    DISPLAY19,
    PLAYING19,
    PLAYING20,
    DISPLAY20,
    DISPLAY21,
    PLAYING21,
    DISPLAY22,
    PLAYING22,
    DISPLAY23,
    PLAYING23,
    DISPLAY24,
    PLAYING24,
    DISPLAY25,
    PLAYING25,
    DISPLAY26,
    PLAYING26,
    DISPLAY27,
    PLAYING27,
    DISPLAY28,
    PLAYING28,
    DISPLAY29,
    PLAYING29,
    PLAYING30,
    DISPLAY30,
    DISPLAY31,
    PLAYING31,
    DISPLAY32,
    PLAYING32,
    DISPLAY33,
    PLAYING33,
    DISPLAY34,
    PLAYING34,
    DISPLAY35,
    PLAYING35,
    DISPLAY36,
    PLAYING36,
    DISPLAY37,
    PLAYING37,
    DISPLAY38,
    PLAYING38,
    DISPLAY39,
    PLAYING39,
    PLAYING40,
    DISPLAY40,
    DISPLAY41,
    PLAYING41,
    DISPLAY42,
    PLAYING42,
    DISPLAY43,
    PLAYING43,
    DISPLAY44,
    PLAYING44,
    DISPLAY45,
    PLAYING45,
    DISPLAY46,
    PLAYING46,
    DISPLAY47,
    PLAYING47,
    DISPLAY48,
    PLAYING48,
    DISPLAY49,
    PLAYING49,
    PLAYING50,
    DISPLAY50,
    DISPLAY51,
    PLAYING51,
    DISPLAY52,
    PLAYING52,
    DISPLAY53,
    PLAYING53,
    DISPLAY54,
    PLAYING54,
    WON,
    LOSS
} State;

// Function Prototypes
void swDelay(char numLoops);
void welcomeSC();
void lose();
void win();
void placeNum();
bool drawCountdown();
void drawnums(int);
void drawcurrKey(char);

// Main
void main(void)
{
    unsigned char keyPressed = 0;
    int counter = 0;
    int myrand[SEQUENCE];
    int i;
    State state = WELCOME_SCREEN;


    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
    // You can then configure it properly, if desired

    initLeds();
    configDisplay();
    configKeypad();

    while (1)    // Forever loop
    {
        // Check if any keys have been pressed on the 3x4 keypad
        keyPressed = getKey();
        switch(state)
        {
        case WELCOME_SCREEN:
            welcomeSC();
            state = WAIT_FOR_START;
            break;
        case WAIT_FOR_START:
            if (keyPressed == '*')
            {
                state = START_CNT_DOWN;
            }
            break;
        case START_CNT_DOWN:
            state = CNT_DOWN_SC;
            break;
        case CNT_DOWN_SC:
            if (drawCountdown())
            {
                state = START;
            }
            break;

        case START:
            //we are saving the sequence to an array of integers to check back later
            for (i = 0; i < SEQUENCE; i++){
                myrand[i] = (rand() % (4)) + 1;
            }
            state = DISPLAY0;
            break;
        case DISPLAY0:
            if(counter == 0){
                drawnums(myrand[0]);
                state = PLAYING0;
            }else if(counter == 1){
                drawnums(myrand[0]);
                state = DISPLAY1;
            }
            break;
        case PLAYING0:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                counter++;
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = DISPLAY0;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case DISPLAY1:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[1]);
            state = PLAYING1;
            break;
        case PLAYING1:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING2;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING2:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[1] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = DISPLAY2;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case DISPLAY2:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[0]);
            state = DISPLAY3;
            break;
        case DISPLAY3:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[1]);
            state = DISPLAY4;
            break;
        case DISPLAY4:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[2]);
            state = PLAYING3;
            break;
        case PLAYING3:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING4;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING4:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[1] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING5;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING5:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[2] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = DISPLAY6;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case DISPLAY6:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[0]);
            state = DISPLAY7;
            break;
        case DISPLAY7:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[1]);
            state = DISPLAY8;
            break;
        case DISPLAY8:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[2]);
            state = DISPLAY9;
            break;
        case DISPLAY9:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[3]);
            state = PLAYING6;
            break;
        case PLAYING6:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING7;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING7:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[1] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING8;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING8:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[2] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING9;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING9:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[3] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = DISPLAY10;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case DISPLAY10:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[0]);
            state = DISPLAY11;
            break;
        case DISPLAY11:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[1]);
            state = DISPLAY12;
            break;
        case DISPLAY12:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[2]);
            state = DISPLAY13;
            break;
        case DISPLAY13:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[3]);
            state = DISPLAY14;
            break;
        case DISPLAY14:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[4]);
            state = PLAYING10;
            break;
        case PLAYING10:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING11;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING11:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[1] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING12;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING12:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[2] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING13;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING13:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[3] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING14;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING14:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[4] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = DISPLAY15;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case DISPLAY15:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[0]);
            state = DISPLAY16;
            break;
        case DISPLAY16:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[1]);
            state = DISPLAY17;
            break;
        case DISPLAY17:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[2]);
            state = DISPLAY18;
            break;
        case DISPLAY18:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[3]);
            state = DISPLAY19;
            break;
        case DISPLAY19:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[4]);
            state = DISPLAY20;
            break;
        case DISPLAY20:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[5]);
            state = PLAYING15;
            break;
        case PLAYING15:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING16;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING16:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[1] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING17;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING17:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[2] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING18;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING18:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[3] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING19;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING19:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[4] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING20;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING20:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[5] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = DISPLAY21;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case DISPLAY21:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[0]);
            state = DISPLAY22;
            break;
        case DISPLAY22:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[1]);
            state = DISPLAY23;
            break;
        case DISPLAY23:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[2]);
            state = DISPLAY24;
            break;
        case DISPLAY24:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[3]);
            state = DISPLAY25;
            break;
        case DISPLAY25:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[4]);
            state = DISPLAY26;
            break;
        case DISPLAY26:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[5]);
            state = DISPLAY27;
            break;
        case DISPLAY27:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[6]);
            state = PLAYING21;
            break;
        case PLAYING21:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING22;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING22:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[1] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING23;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING23:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[2] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING24;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING24:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[3] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING25;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING25:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[4] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING26;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING26:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[5] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING27;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING27:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[6] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = DISPLAY28;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
            //
        case DISPLAY28:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[0]);
            state = DISPLAY29;
            break;
        case DISPLAY29:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[1]);
            state = DISPLAY30;
            break;
        case DISPLAY30:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[2]);
            state = DISPLAY31;
            break;
        case DISPLAY31:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[3]);
            state = DISPLAY32;
            break;
        case DISPLAY32:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[4]);
            state = DISPLAY33;
            break;
        case DISPLAY33:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[5]);
            state = DISPLAY34;
            break;
        case DISPLAY34:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[6]);
            state = DISPLAY35;
            break;
        case DISPLAY35:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[7]);
            state = PLAYING28;
            break;
            //
        case PLAYING28:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING29;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING29:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[1] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING30;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING30:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[2] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING31;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING31:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[3] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING32;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING32:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[4] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING33;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING33:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[5] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING34;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING34:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[6] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING35;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING35:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[7] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = DISPLAY36;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
            //
        case DISPLAY36:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[0]);
            state = DISPLAY37;
            break;
        case DISPLAY37:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[1]);
            state = DISPLAY38;
            break;
        case DISPLAY38:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[2]);
            state = DISPLAY39;
            break;
        case DISPLAY39:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[3]);
            state = DISPLAY40;
            break;
        case DISPLAY40:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[4]);
            state = DISPLAY41;
            break;
        case DISPLAY41:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[5]);
            state = DISPLAY42;
            break;
        case DISPLAY42:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[6]);
            state = DISPLAY43;
            break;
        case DISPLAY43:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[7]);
            state = DISPLAY44;
            break;
        case DISPLAY44:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[8]);
            state = PLAYING36;
            break;
            //
        case PLAYING36:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING37;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING37:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[1] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING38;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING38:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[2] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING39;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING39:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[3] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING40;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING40:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[4] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING41;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING41:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[5] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING42;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING42:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[6] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING43;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING43:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[7] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING44;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING44:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[8] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = DISPLAY45;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;

        case DISPLAY45:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[0]);
            state = DISPLAY46;
            break;
        case DISPLAY46:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[1]);
            state = DISPLAY47;
            break;
        case DISPLAY47:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[2]);
            state = DISPLAY48;
            break;
        case DISPLAY48:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[3]);
            state = DISPLAY49;
            break;
        case DISPLAY49:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[4]);
            state = DISPLAY50;
            break;
        case DISPLAY50:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[5]);
            state = DISPLAY51;
            break;
        case DISPLAY51:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[6]);
            state = DISPLAY52;
            break;
        case DISPLAY52:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[7]);
            state = DISPLAY53;
            break;
        case DISPLAY53:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[8]);
            state = DISPLAY54;
            break;
        case DISPLAY54:
            Graphics_clearDisplay(&g_sContext); //clear
            drawnums(myrand[9]);
            state = PLAYING45;
            break;

        case PLAYING45:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[0] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING46;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING46:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[1] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING47;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING47:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[2] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING48;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING48:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[3] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING49;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING49:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[4] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING50;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING50:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[5] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING51;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING51:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[6] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING52;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING52:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[7] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING53;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING53:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[8] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = PLAYING54;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case PLAYING54:
            Graphics_clearDisplay(&g_sContext); //clear
            if (keyPressed == myrand[9] + 48){
                drawcurrKey(keyPressed);
                BuzzerOn();
                P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
                swDelay(2);
                setLeds(0);
                BuzzerOff();
                Graphics_clearDisplay(&g_sContext); //clear
                swDelay(2);
                state = WON;
            }else if(keyPressed != 0){

                state = LOSS;
            }
            break;
        case WON:
            win();
            BuzzerOn();
            P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
            swDelay(5);
            setLeds(0);
            BuzzerOff();
            swDelay(10);
            counter = 0;
            state = WELCOME_SCREEN;
            break;
        case LOSS:
            lose();
            BuzzerOn();
            P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
            swDelay(5);
            setLeds(0);
            BuzzerOff();
            swDelay(10);
            counter = 0;
            state = WELCOME_SCREEN;
            break;
        }
    }
}



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
void welcomeSC()
{
    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display

    Graphics_drawStringCentered(&g_sContext, "SIMON", AUTO_STRING_LENGTH, 48,
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
void lose()
{
    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display

    Graphics_drawStringCentered(&g_sContext, "You Lose :(", AUTO_STRING_LENGTH, 48,
                                25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "Press *", AUTO_STRING_LENGTH, 48,
                                70, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "to Try Again", AUTO_STRING_LENGTH,
                                48, 80, TRANSPARENT_TEXT);

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

void win()
{
    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display

    Graphics_drawStringCentered(&g_sContext, "You Win :)", AUTO_STRING_LENGTH, 48,
                                25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "Press *", AUTO_STRING_LENGTH, 48,
                                70, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "to Play Again", AUTO_STRING_LENGTH,
                                48, 80, TRANSPARENT_TEXT);

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

bool drawCountdown()
{


    Graphics_clearDisplay(&g_sContext); // Clear the display
    Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48,
                                50, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);
    swDelay(2);

    Graphics_clearDisplay(&g_sContext); // Clear the display
    Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48,
                                50, TRANSPARENT_TEXT);

    Graphics_flushBuffer(&g_sContext);
    swDelay(2);

    Graphics_clearDisplay(&g_sContext); // Clear the display
    Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 48,
                                50, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);
    swDelay(2);

    Graphics_clearDisplay(&g_sContext); // Clear the display

    return true;

}

void drawnums(int rand)
{

    if (rand == 1){
        Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 28, 50, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
        BuzzerPWM(32);
        P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
        swDelay(2);
        setLeds(0);
        BuzzerOff();

    }else if(rand == 2){
        Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48, 50, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
        BuzzerPWM(64);
        P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
        swDelay(2);
        setLeds(0);
        BuzzerOff();

    }else if(rand == 3){
        Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 68, 50, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
        BuzzerPWM(128);
        P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
        swDelay(2);
        setLeds(0);
        BuzzerOff();

    }else if(rand == 4){
        Graphics_drawStringCentered(&g_sContext, "4", AUTO_STRING_LENGTH, 88, 50, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
        BuzzerPWM(256);
        P1OUT |= BIT0;      // Set the P1.0 as 1 (High)
        swDelay(2);
        setLeds(0);
        BuzzerOff();
    }
    swDelay(2);

}
void drawcurrKey(char aChar)
{


    if (aChar == '1'){
        Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 28, 50, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);



    }else if(aChar == '2'){
        Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48, 50, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);



    }else if(aChar == '3'){
        Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 68, 50, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);




    }else if(aChar == '4'){
        Graphics_drawStringCentered(&g_sContext, "4", AUTO_STRING_LENGTH, 88, 50, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);


    }
}







