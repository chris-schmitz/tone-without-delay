#ifndef MELODY_PLAYER
#define MELODY_PLAYER
#include "pitches.h"
#include "Arduino.h"

enum MELODY
{
    SHAVE_AND_A_HAIRCUT = 0,
    IDLE,
    READY,
    PROCESSING,
    COMPLETE,
};

class MelodyPlayer
{
    uint8_t speakerPin;

    // * Durations and frequencies for the different playable melodies
    // | Note that the frequencies and durations are set in the implmentation file.
    // | At the moment there's no way of passing in the info via public method.
    static int length_shaveAndAHairCut;
    static int melody_shaveAndAHairCut[];
    static int durations_shaveAndAHairCut[];

    static int length_READY;
    static int melody_READY[];
    static int durations_READY[];

    static int length_PROCESSING;
    static int melody_PROCESSING[];
    static int durations_PROCESSING[];

    static int length_COMPLETE;
    static int melody_COMPLETE[];
    static int durations_COMPLETE[];

    static int length_IDLE;
    static int melody_IDLE[];
    static int durations_IDLE[];

    // * internal pointers used in the dynamic melody selection
    int activeLength;
    int *activeMelody;
    int *activeDurations;

    void _playMelody();

public:
    MelodyPlayer(uint8_t speakerPin);
    void playMelody(MELODY name);
};
#endif