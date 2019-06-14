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

    static int melody_shaveAndAHairCut[];
    static int durations_shaveAndAHairCut[];
    int *activeMelody;
    int *activeDurations;

    void _playMelody();

public:
    MelodyPlayer(uint8_t speakerPin);
    void playMelody(MELODY name);
};
#endif