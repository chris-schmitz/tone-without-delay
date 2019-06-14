#include "MelodyPlayer.h"

MelodyPlayer::MelodyPlayer(uint8_t pin)
{
    speakerPin = pin;
}

// * Shave and a haircut
int MelodyPlayer::length_shaveAndAHairCut = 9;
int MelodyPlayer::melody_shaveAndAHairCut[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4, 0};
int MelodyPlayer::durations_shaveAndAHairCut[] = {
    4, 8, 8, 4, 4, 4, 4, 4, 4};

// * READY
int MelodyPlayer::length_READY = 8;
int MelodyPlayer::melody_READY[] = {
    NOTE_C3, NOTE_C3, 0, NOTE_C4, NOTE_C4, 0, NOTE_C3, NOTE_C3};
int MelodyPlayer::durations_READY[] = {
    16, 16, 8, 16, 16, 8, 16, 16};

// * PROCESSING
int MelodyPlayer::length_PROCESSING = 8;
int MelodyPlayer::melody_PROCESSING[] = {
    NOTE_C3, NOTE_D3, NOTE_E3, NOTE_D3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_D3};
int MelodyPlayer::durations_PROCESSING[] = {
    8, 8, 8, 8, 8, 8, 8, 8};

// * COMPLETE
int MelodyPlayer::length_COMPLETE = 4;
int MelodyPlayer::melody_COMPLETE[] = {
    NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4};
int MelodyPlayer::durations_COMPLETE[] = {
    8, 8, 8, 2};

// * IDLE
int MelodyPlayer::length_IDLE = 14;
int MelodyPlayer::melody_IDLE[] = {
    NOTE_C3, NOTE_C3, NOTE_C3, NOTE_E3, NOTE_C3, NOTE_F3, NOTE_G3, 0, NOTE_G3, NOTE_G3, NOTE_F3, NOTE_D3, NOTE_E3, NOTE_C3};
int MelodyPlayer::durations_IDLE[] = {
    8, 4, 8, 8, 8, 8, 4, 2, 8, 4, 8, 8, 8, 8};

/**
 * * Play a given melody per the passed in enum.
 * * Params:
 * * MELODY name The MELODY enum valu
 */
void MelodyPlayer::playMelody(MELODY name)
{
    Serial.print("Name: ");
    Serial.println(name);
    switch (name)
    {
    case SHAVE_AND_A_HAIRCUT:
        Serial.println("Shave and a hair cut");
        activeLength = length_shaveAndAHairCut;
        activeMelody = melody_shaveAndAHairCut;
        activeDurations = durations_shaveAndAHairCut;
        break;
    case READY:
        Serial.println("Playing melody: READY");
        activeLength = length_READY;
        activeMelody = melody_READY;
        activeDurations = durations_READY;
        break;
    case PROCESSING:
        Serial.println("Playing melody: PROCESSING");
        activeLength = length_PROCESSING;
        activeMelody = melody_PROCESSING;
        activeDurations = durations_PROCESSING;
        break;
    case COMPLETE:
        Serial.println("Playing melody: COMPLETE");
        activeLength = length_COMPLETE;
        activeMelody = melody_COMPLETE;
        activeDurations = durations_COMPLETE;
        break;
    case IDLE:
        Serial.println("Playing melody: IDLE");
        activeLength = length_IDLE;
        activeMelody = melody_IDLE;
        activeDurations = durations_IDLE;
        break;
    }

    _playMelody();
}

/**
 * * The method for actually playing the selected melody.
 * ! note that the melody desired should be set in the
 * ! active pointer properties before this method is called
 */
void MelodyPlayer::_playMelody()
{
    Serial.println("Playing Melody");
    // * pulled from the toneMelody arduino example
    for (int thisNote = 0; thisNote < activeLength; thisNote++)
    {

        int activeDuration = activeDurations[thisNote];
        int noteDuration = 1000 / activeDurations[thisNote];
        int noteFrequency = activeMelody[thisNote];

        // * leaving in for troubleshooting
        // Serial.println(thisNote);
        // Serial.println(activeDuration);
        // Serial.println(noteDuration);
        // Serial.println(noteFrequency);

        tone(speakerPin, noteFrequency, noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        noTone(speakerPin);
    }
}
