#include <Adafruit_NeoPixel.h>
#include "pitches.h"

Adafruit_NeoPixel bar = Adafruit_NeoPixel(8, 2, NEO_GRB + NEO_KHZ800);

const int tonePin = 3;

// notes in the melody:
int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4};

unsigned long previousMillis = 0;

long pauseBetweenNotes = 100;
long noteDuration = 100;

const long interval = pauseBetweenNotes;
// const long interval = noteDuration;
boolean outputTone = false; // Records current state
int thisNote = 0;

const int lightInterval = 50;
unsigned long previousLightMillis = 0;
uint8_t lightIndex = 0;
boolean lightOn = true;

uint32_t lightsOff = bar.Color(0, 0, 0);

uint32_t cyan = bar.Color(0, 255, 255);

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;
    bar.begin();
    bar.show();

    for (uint8_t i = 0; i < 8; i++)
    {
        bar.setPixelColor(i, 255, 255, 0);
        bar.show();
        delay(100);
    }
    for (uint8_t i = 0; i < 8; i++)
    {
        bar.setPixelColor(i, 0, 0, 0);
        bar.show();
        delay(100);
    }
}

// IN LOOP
void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousLightMillis >= lightInterval)
    {
        if (lightOn)
        {
            bar.setPixelColor(lightIndex, cyan);
        }
        else
        {
            bar.setPixelColor(lightIndex, lightsOff);
        }
        bar.show();

        if (lightIndex < 8)
        {
            lightIndex++;
        }
        else
        {
            lightIndex = 0;
            lightOn = !lightOn;
        }

        previousLightMillis = currentMillis;
    }

    if (outputTone)
    {
        // We are currently outputting a tone
        // Check if it's been long enough and turn off if so
        if (currentMillis - previousMillis >= noteDuration)
        {
            previousMillis = currentMillis;
            noTone(tonePin);
            outputTone = false;
        }
    }
    else
    {
        // We are currently in a pause
        // Check if it's been long enough and turn on if so
        if (currentMillis - previousMillis >= pauseBetweenNotes)
        {
            previousMillis = currentMillis;
            tone(tonePin, melody[thisNote]);
            outputTone = true;

            if (thisNote < 8)
            {
                thisNote++;
            }
            else
            {
                thisNote = 0;
            }
        }
    }
}
