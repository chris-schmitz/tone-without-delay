#include <Adafruit_NeoPixel.h>
#include "src/melodyPlayer/MelodyPlayer.h"

const int SPEAKER = 3;
const int LEDs = 2;

MelodyPlayer player = MelodyPlayer(SPEAKER);
Adafruit_NeoPixel bar = Adafruit_NeoPixel(8, LEDs, NEO_GRB + NEO_KHZ800);

// * State management for the tones

// * shave and a hair cut
unsigned long previousMillis = 0;
long pauseBetweenNotes = 100;
long noteDuration = 100;
const long interval = pauseBetweenNotes;
boolean outputTone = false; // Records current state
int thisNote = 0;

// * State management for the lights
const int lightInterval = 50;
unsigned long previousLightMillis = 0;
uint8_t lightIndex = 0;
boolean lightOn = true;

// * Colors:
uint32_t lightsOff = bar.Color(0, 0, 0);
uint32_t cyan = bar.Color(0, 255, 255);

void setup()
{
    // player.playMelody(READY);
    Serial.begin(9600);
    while (!Serial)
        ;
    bar.begin();
    bar.show();
    showReady();
}

void loop()
{
    player.playMelody(SHAVE_AND_A_HAIRCUT);
    // unsigned long currentMillis = millis();

    // handleLights(currentMillis);

    // // * pulled and modified from the stack overflow post:
    // // * https://arduino.stackexchange.com/questions/17355/playing-melody-with-tone-without-using-delay

    // if (outputTone)
    // {
    //     // We are currently outputting a tone
    //     // Check if it's been long enough and turn off if so

    //     if (currentMillis - previousMillis >= noteDuration)
    //     {
    //         previousMillis = currentMillis;
    //         noTone(SPEAKER);
    //         outputTone = false;
    //     }
    // }
    // else
    // {
    // // We are currently in a pause
    // // Check if it's been long enough and turn on if so
    // // ? I'm assuming we want to keep this as a standard duration. should it be?

    // if (currentMillis - previousMillis >= pauseBetweenNotes)
    // {
    //     previousMillis = currentMillis;

    //     int currentNote = melody[thisNote];
    //     if (currentNote != 0)
    //     {
    //         tone(SPEAKER, currentNote);
    //     }
    //     else
    //     {
    //         noTone(SPEAKER);
    //     }
    //     outputTone = true;

    //     if (thisNote < 8)
    //     {
    //         thisNote++;
    //     }
    //     else
    //     {
    //         thisNote = 0;
    //     }

    //     // * figure out the duration for the new note
    //     noteDuration = 1000 / noteDurations[thisNote];
    // }
    // }
}

void showReady()
{

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

    // // * pulled from the toneMelody arduino example
    // // iterate over the notes of the melody:
    // for (int thisNote = 0; thisNote < 8; thisNote++)
    // {

    //     // to calculate the note duration, take one second divided by the note type.
    //     //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    //     int noteDuration = 1000 / noteDurations[thisNote];
    //     tone(SPEAKER, melody[thisNote], noteDuration);

    //     // to distinguish the notes, set a minimum time between them.
    //     // the note's duration + 30% seems to work well:
    //     int pauseBetweenNotes = noteDuration * 1.30;
    //     delay(pauseBetweenNotes);
    //     // stop the tone playing:
    //     noTone(SPEAKER);
    // }
}

void handleLights(unsigned long currentMillis)
{

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
}
