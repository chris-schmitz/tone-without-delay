#include "MelodyPlayer.h"

MelodyPlayer::MelodyPlayer(uint8_t pin)
{
    speakerPin = pin;

    int melody_shaveAndAHairCut[] = {
        NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4, 0};

    int durations_shaveAndAHairCut[] = {
        4, 8, 8, 4, 4, 4, 4, 4, 4};
}

void MelodyPlayer::playMelody(MELODY name)
{
    switch (name)
    {
    case SHAVE_AND_A_HAIRCUT:
        Serial.println("Shave and a hair cut");
        activeMelody = melody_shaveAndAHairCut;
        activeDurations = durations_shaveAndAHairCut;
        break;
    }

    _playMelody();
}

void MelodyPlayer::_playMelody()
{
    Serial.println("Playing Melody");
    // * pulled from the toneMelody arduino example
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {

        int activeDuration = activeDurations[thisNote];
        int noteDuration = 1000 / activeDurations[thisNote];
        int noteFrequency = activeMelody[thisNote];

        Serial.println(thisNote);
        Serial.println(activeDuration);
        Serial.println(noteDuration);
        Serial.println(noteFrequency);

        tone(speakerPin, noteFrequency, noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        noTone(speakerPin);
    }
}
