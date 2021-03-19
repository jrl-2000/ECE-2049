/*
 * songs.h
 *
 *  Created on: Mar 1, 2021
 *      Author: Jonathan Lopez
 */

#ifndef SONGS_H_
#define SONGS_H_
#include <notes.h>

typedef enum NoteModifier {
    NONE = 0,
    REST = 1,
} NoteModifier;

typedef struct Note
{
    int frequency; // Frequency in Hz
    int duration; // Duration in sixteenth notes
    short modifier;
} Note;

typedef struct Song
{
    const Note* notes;
    short noteCount;
    short silenceDuration;
    short noteDuration; // Duration of an eighth note in milliseconds (60000/2) / bpm
} Song;
Note midnightCityNotes[] = {
                            {NOTE_REST, 2, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1

                            {NOTE_FS5, 1, NONE},//2

                            {NOTE_FS5, 1, NONE},//3

                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 4, REST},

                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1

                            {NOTE_FS5, 1, NONE},//2

                            {NOTE_FS5, 1, NONE},//3

                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 4, REST},

                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1

                            {NOTE_FS5, 1, NONE},//2

                            {NOTE_FS5, 1, NONE},//3

                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 4, REST},
                            {NOTE_REST, 2, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1

                            {NOTE_FS5, 1, NONE},//2

                            {NOTE_FS5, 1, NONE},//3

                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 8, REST},
                            {NOTE_A4, 2, NONE}, //lyrics part

                            {NOTE_A4, 2, NONE}, //lyrics part

                            {NOTE_A4, 2, NONE}, //lyrics part
                            {NOTE_REST, 2, REST},
                            {NOTE_A4, 12, NONE}, //lyrics part long
                            {NOTE_REST, 8, REST},
                            {NOTE_A4, 2, NONE}, //lyrics part2

                            {NOTE_A4, 2, NONE}, //lyrics part2

                            {NOTE_A4, 2, NONE}, //lyrics part2
                            {NOTE_REST, 2, REST},
                            {NOTE_A4, 8, NONE}, //lyrics part2 long

                            {NOTE_A4, 2, NONE}, //lyrics part2 long
                            {NOTE_FS4, 4, NONE},
                            {NOTE_G4, 2, NONE},
                            {NOTE_FS4, 2, NONE},
                            {NOTE_D4, 8, NONE},

                            {NOTE_A4, 2, NONE}, //lyrics part3

                            {NOTE_A4, 2, NONE}, //lyrics part3

                            {NOTE_A4, 2, NONE}, //lyrics part3
                            {NOTE_REST, 2, REST},
                            {NOTE_A4, 12, NONE}, //lyrics part3 long
                            {NOTE_REST, 8, REST},
                            {NOTE_A4, 2, NONE}, //lyrics part4

                            {NOTE_A4, 2, NONE}, //lyrics part4

                            {NOTE_A4, 2, NONE}, //lyrics part4
                            {NOTE_REST, 2, REST},
                            {NOTE_A4, 4, NONE}, //lyrics part4 long
                            {NOTE_FS5, 4, NONE},
                            {NOTE_A4, 2, NONE},
                            {NOTE_FS4, 4, NONE},
                            {NOTE_G4, 4, NONE},
                            {NOTE_B4, 4, NONE},//main part again
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1

                            {NOTE_FS5, 1, NONE},//2

                            {NOTE_FS5, 1, NONE},//3
                           //
                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 4, REST},
                            {NOTE_REST, 2, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1
                           //
                            {NOTE_FS5, 1, NONE},//2
                           //
                            {NOTE_FS5, 1, NONE},//3
                           //
                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 4, REST},
                            {NOTE_REST, 2, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1
                           //
                            {NOTE_FS5, 1, NONE},//2
                           //
                            {NOTE_FS5, 1, NONE},//3
                           //
                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 4, REST},
                            {NOTE_REST, 2, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1
                           //
                            {NOTE_FS5, 1, NONE},//2
                           //
                            {NOTE_FS5, 1, NONE},//3
                           //
                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 8, REST},
                            {NOTE_A4, 2, NONE}, //lyrics part again
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part
                            {NOTE_REST, 2, REST},
                            {NOTE_A4, 12, NONE}, //lyrics part long
                            {NOTE_REST, 8, REST},
                            {NOTE_A4, 2, NONE}, //lyrics part2
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part2
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part2
                            {NOTE_REST, 2, REST},
                            {NOTE_A4, 8, NONE}, //lyrics part2 long
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part2 long
                            {NOTE_FS4, 4, NONE},
                            {NOTE_G4, 2, NONE},
                            {NOTE_FS4, 2, NONE},
                            {NOTE_D4, 8, NONE},
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part3
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part3
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part3
                            {NOTE_REST, 2, REST},
                            {NOTE_A4, 12, NONE}, //lyrics part3 long
                            {NOTE_REST, 8, REST},
                            {NOTE_A4, 2, NONE}, //lyrics part4
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part4
                           //
                            {NOTE_A4, 2, NONE}, //lyrics part4
                            {NOTE_REST, 2, REST},
                            {NOTE_A4, 4, NONE}, //lyrics part4 long
                            {NOTE_FS4, 4, NONE},
                            {NOTE_A4, 2, NONE},
                            {NOTE_FS4, 4, NONE},
                            {NOTE_G4, 8, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_B4, 2, NONE}, //lyrics part B
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part B
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part B
                           //
                            {NOTE_CS5, 2, NONE}, //lyrics part4 C#
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_CS6, 2, NONE}, //lyrics part4 C#
                            {NOTE_E6, 4, NONE},
                            {NOTE_D6, 2, NONE},
                            {NOTE_CS6, 2, NONE},
                            {NOTE_REST, 8, REST},
                            {NOTE_B4, 2, NONE}, //lyrics part4 B

                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_CS5, 2, NONE}, //lyrics part4 C#
                           //
                            {NOTE_CS5, 3, NONE}, //lyrics part4 C#
                            {NOTE_D5, 3, NONE},
                            {NOTE_E5, 2, NONE},
                            {NOTE_CS5, 4, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_CS5, 2, NONE}, //lyrics part4 C#
                           //
                            {NOTE_CS5, 4, NONE}, //lyrics part4 C#
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_B4, 2, NONE}, //lyrics part4 B
                           //
                            {NOTE_CS6, 2, NONE}, //lyrics part4 C#
                           //
                            {NOTE_CS6, 4, NONE}, //lyrics part4 C
                            {NOTE_REST, 8, REST},
                            {NOTE_B4, 2, NONE},
                            {NOTE_CS5, 2, NONE},
                           //
                            {NOTE_CS5, 2, NONE},
                           //
                            {NOTE_CS5, 2, NONE},
                            {NOTE_REST, 2, REST},
                            {NOTE_CS5, 3, NONE},
                            {NOTE_D5, 3, NONE},
                            {NOTE_E5, 2, NONE},
                            {NOTE_CS5, 4, NONE},
                            {NOTE_A5, 4, NONE}, //again
                            {NOTE_B4, 4, NONE},//main part again
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1
                           //
                            {NOTE_FS5, 1, NONE},//2
                           //
                            {NOTE_FS5, 1, NONE},//3
                           //
                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 4, REST},
                            {NOTE_REST, 2, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1
                           //
                            {NOTE_FS5, 1, NONE},//2
                           //
                            {NOTE_FS5, 1, NONE},//3
                           //
                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_E5, 8, NONE},
                            {NOTE_D5, 8, NONE},
                            {NOTE_A4, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_E5, 8, NONE},
                            {NOTE_D5, 8, NONE},
                            {NOTE_A4, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_E5, 4, NONE},
                           //
                            {NOTE_E5, 2, NONE},
                            {NOTE_CS5, 1, NONE},
                           //
                            {NOTE_CS5, 4, NONE},
                            {NOTE_REST, 3, REST},
                            {NOTE_CS5, 1, NONE},
                            {NOTE_B4, 4, NONE},
                            {NOTE_REST, 3, REST},
                            {NOTE_CS5, 1, NONE},
                            {NOTE_A4, 4, NONE},
                            {NOTE_G4, 2, NONE},
                            {NOTE_FS4, 4, NONE},
                            {NOTE_B4, 4, NONE},
                            {NOTE_A4, 2, NONE},
                            {NOTE_B4, 4, NONE},
                            {NOTE_CS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_E5, 2, NONE},
                            {NOTE_D5, 4, NONE},
                            {NOTE_CS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_E5, 2, NONE},
                            {NOTE_D5, 3, NONE},
                            {NOTE_CS5, 2, NONE},
                            {NOTE_E5, 8, NONE},
                            {NOTE_REST, 2, REST},
                            {NOTE_A5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_A5, 2, NONE},
                            {NOTE_B4, 4, NONE},
                            {NOTE_A5, 2, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_B4, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_A5, 2, NONE},
                            {NOTE_B4, 4, NONE},//main part last time
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1
                           //
                            {NOTE_FS5, 1, NONE},//2
                           //
                            {NOTE_FS5, 1, NONE},//3
                           //
                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_REST, 4, REST},
                            {NOTE_REST, 2, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 4, NONE},
                            {NOTE_REST, 4, REST},
                            {NOTE_FS5, 2, NONE},
                            {NOTE_D5, 2, NONE},
                            {NOTE_B4, 2, NONE},
                            {NOTE_FS5, 1, NONE},//1
                           //
                            {NOTE_FS5, 1, NONE},//2
                           //
                            {NOTE_FS5, 1, NONE},//3
                           //
                            {NOTE_FS5, 1, NONE},//4
                            {NOTE_B4, 12, NONE},

};

const Song midnightCity =
{
 midnightCityNotes,
 513-81,
 20,
 150
};

const Note frameOfMindNotes[] = {
                                 {NOTE_REST, 2, REST},
                                 {NOTE_AS4, 8, NONE},
                                 {NOTE_GS4, 4, NONE},
                                 {NOTE_FS4, 4, NONE},
                                 {NOTE_AS4, 4, NONE},
                                 {NOTE_CS5 , 8, NONE},
                                 {NOTE_GS4, 4, NONE},
                                 {NOTE_FS4, 4, NONE},
                                 {NOTE_AS4, 4, NONE},
                                 {NOTE_GS4, 8, NONE},
                                //
                                 {NOTE_GS4, 4, NONE},
                                //
                                 {NOTE_GS4, 4, NONE},
                                //
                                 {NOTE_GS4, 4, NONE},
                                //
                                 {NOTE_GS4, 4, NONE},
                                 {NOTE_AS4, 2, NONE},
                                 {NOTE_FS4, 4, NONE},
                                 {NOTE_GS4, 8, NONE},
                                 {NOTE_F4, 4, NONE},
                                 {NOTE_FS4, 2, NONE},
                                 {NOTE_F4, 2, NONE},
                                 {NOTE_DS4, 2, NONE},
                                 {NOTE_DS4, 4, NONE},
                                 {NOTE_CS3, 8, NONE},//repeat
                                 {NOTE_REST, 2, REST},
                                 {NOTE_AS4, 8, NONE},
                                 {NOTE_GS4, 4, NONE},
                                 {NOTE_FS4, 4, NONE},
                                 {NOTE_AS4, 4, NONE},
                                 {NOTE_CS5 , 8, NONE},
                                 {NOTE_GS4, 4, NONE},
                                 {NOTE_FS4, 4, NONE},
                                 {NOTE_AS4, 4, NONE},
                                 {NOTE_GS4, 8, NONE},
                                //
                                 {NOTE_GS4, 4, NONE},
                                //
                                 {NOTE_GS4, 4, NONE},
                                //
                                 {NOTE_GS4, 4, NONE},
                                //
                                 {NOTE_GS4, 4, NONE},
                                 {NOTE_AS4, 2, NONE},
                                 {NOTE_FS4, 4, NONE},
                                 {NOTE_GS4, 8, NONE},
                                 {NOTE_F4, 4, NONE},
                                 {NOTE_FS4, 2, NONE},
                                 {NOTE_F4, 2, NONE},
                                 {NOTE_DS4, 2, NONE},
                                 {NOTE_DS4, 4, NONE},
                                 {NOTE_CS3, 4, NONE},//end
                                 {NOTE_REST, 2, REST},
                                 {NOTE_CS6, 16, NONE},
                                 {NOTE_B5, 8, NONE},
                                 {NOTE_AS5, 8, NONE},
                                 {NOTE_B5, 8, NONE},
                                 {NOTE_GS5, 8, NONE},
                                //
                                 {NOTE_GS5, 8, NONE},
                                 {NOTE_FS5, 8, NONE},
                                 {NOTE_F5, 8, NONE},
                                 {NOTE_FS5, 8, NONE},
                                //
                                 {NOTE_FS5, 4, NONE},
                                //
                                 {NOTE_FS5, 4, NONE},
                                //
                                 {NOTE_FS5, 4, NONE},
                                 {NOTE_GS5, 4, NONE},
                                 {NOTE_FS5, 4, NONE},
                                 {NOTE_CS6, 8, NONE},
                                 {NOTE_FS5, 4, NONE},
                                //
                                 {NOTE_FS5, 4, NONE},
                                //
                                 {NOTE_FS5, 4, NONE},
                                //
                                 {NOTE_FS5, 4, NONE},
                                 {NOTE_GS5, 4, NONE},
                                 {NOTE_AS5, 4, NONE},
                                 {NOTE_GS5, 8, NONE},
                                //
                                 {NOTE_GS5, 4, NONE},
                                 {NOTE_FS5, 2, NONE},
                                 {NOTE_F5, 8, NONE},
                                 {NOTE_CS5, 2, NONE},
                                 {NOTE_GS5, 4, NONE},
                                 {NOTE_FS5, 2, NONE},
                                 {NOTE_F5, 8, NONE},
                                //
                                 {NOTE_F5, 4, NONE},
                                 {NOTE_FS5, 2, NONE},
                                 {NOTE_F5, 2, NONE},
                                 {NOTE_DS5, 2, NONE},
                                //
                                 {NOTE_DS5, 4, NONE},
                                 {NOTE_CS5, 2, NONE},
                                 {NOTE_DS5, 8, NONE},

};
const Song frameOfMind =
{
 frameOfMindNotes,
 100-18,
  20,
  70
};


#endif /* SONGS_H_ */
