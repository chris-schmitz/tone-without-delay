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

    int melody_shaveAndAHairCut[9];
    int durations_shaveAndAHairCut[9];
    int *activeMelody;
    int *activeDurations;

    void _playMelody();

public:
    MelodyPlayer(uint8_t speakerPin);
    void playMelody(MELODY name);
};
#endif