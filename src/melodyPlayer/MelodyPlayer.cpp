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
    _setActiveMelody(name);
    _playMelody();
}

void MelodyPlayer::playMelody(MELODY name, unsigned long currentMillis)
{
    Serial.println("Top of public play melody overload");
    _currentMillis = currentMillis;
    _setActiveMelody(name);
    _playMelodyWithoutDelay();

    // TODO: I feel like it's something around here.
    // ! after we're done playing the melody, do we need to reset the state so that
    // ! we get the right active melody?
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

void MelodyPlayer::_playMelodyWithoutDelay()
{
    Serial.println("Top of private play melody");
    // * Not ready for change, kick out early
    Serial.print("_currentMillis: ");
    Serial.println(_currentMillis);
    Serial.print("_nextChange: ");
    Serial.println(_nextChange);
    if (_currentMillis < _nextChange)
    {
        Serial.println("early return");
        return;
    }

    unsigned long millisTillNextChange = 0;

    Serial.print("Note playing: ");
    Serial.println(_notePlaying);

    if (_notePlaying)
    {
        millisTillNextChange = _pauseBetweenNotes;
        noTone(speakerPin);
    }
    else
    {
        Serial.println("top of else clause");
        millisTillNextChange = 1000 / activeDurations[_activeNote];
        Serial.print("millisTillNextChange: ");
        Serial.println(millisTillNextChange);
        Serial.print("activeNote: ");
        Serial.println(_activeNote);
        Serial.print("activeMelody: ");
        Serial.println(*activeMelody);

        if (activeMelody[_activeNote] != 0)
        {
            Serial.println("playing note");
            int note = activeMelody[_activeNote];
            Serial.print("note: ");
            Serial.println(note);
            tone(speakerPin, note);
        }
        else
        {
            Serial.println("playing blank note");
            noTone(speakerPin);
        }

        _activeNote++;
        Serial.print("activeNote after increment: ");
        Serial.println(_activeNote);
        if (_activeNote > activeLength)
        {
            _activeNote = 0;
        }
        Serial.println("End of else clause");
    }

    Serial.print("millisTillNextChange: ");
    Serial.println(millisTillNextChange);
    _notePlaying = !_notePlaying;
    _nextChange = _currentMillis + millisTillNextChange;
    Serial.print("_nextChange at the end of the method: ");
    Serial.println(_nextChange);
}

void MelodyPlayer::_setActiveMelody(MELODY name)
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
}