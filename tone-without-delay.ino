/**
 * | Tone without delay!
 *
 * * This is a proof of concept I used to work thorugh the state machine logic I wanted to used
 * * for the tones in the pegasus project. The TunePlayer class is def built with the pegasus project
 * * in mind, so it's intentionally not made to accept a variety of melodies and allow for their playback.
 * * The class could def be refactored to do that, but that's something I'm leaving for future me.
 *
 * * Also, I'm sure something like TunePlayer already exists out there, but I couldn't find code for doing this
 * * on a brief scan of the internet and, ultimately, the point of this proof of concept and the whole Pegasus
 * * project is an excuse for me to learn a bunch of concepts and approaches in a more practical way.
 *
 * * All of this to say: if you're looking at this proof of concept, know that it's not really meant to be
 * * generically used and it doesn't necessarily apply best practices.
 *
 * * The Pegasus project:
 * ^ https://github.com/chris-schmitz/pegasus
 *
 * * also, there are a bunch of comments in here that are better read via vscode using the Better Comments extension:
 * ^ https://marketplace.visualstudio.com/items?itemName=aaron-bond.better-comments
 */

#include <Adafruit_NeoPixel.h>
#include "src/tunePlayer/TunePlayer.h"

const int SPEAKER = 3;
const int LEDs = 2;

// * adding this in to test out the melody switching
#define BUTTON 1
int buttonState = 0;

TunePlayer player = TunePlayer(SPEAKER);
Adafruit_NeoPixel bar = Adafruit_NeoPixel(8, LEDs, NEO_GRB + NEO_KHZ800);

// * State management for the lights
const int lightInterval = 50;
unsigned long previousLightMillis = 0;
uint8_t lightIndex = 0;
boolean lightOn = true;

// * Colors:
uint32_t lightsOff = bar.Color(0, 0, 0);
uint32_t cyan = bar.Color(0, 255, 255);

// * game state
enum gameStates
{
    GS_IDLE = 0,
    GS_START,
    GS_PROCESSING,
    GS_COMPLETE,
};
gameStates currentGameState = GS_IDLE;

MELODY melodyToPlay;

void setup()
{
    player.playMelody(MELODY_READY);
    Serial.begin(9600);
    // * Leaving in for troubleshooting
    // while (!Serial)
    //     ;
    bar.begin();
    bar.show();
    showReady();

    // * temp add for button testing
    attachInterrupt(BUTTON, rotateGameState, RISING);
}

void loop()
{

    unsigned long currentMillis = millis();
    handleLights(currentMillis);

    // * The gist of the logic:
    // * is the current tone playing the same as the current state? Note that the player should retain the state even after song is played
    // | yes => continue playing
    // ^ no:
    // ^ stop playing current melody
    // ^ reset player state (playcount, active note, anything else?)
    // ^ set the new melody
    // ^ trigger play (will play once and stop)

    // * mapping the game state enum to the melody enum, really we could prob
    // * conflate the two enums, but I kind of like the flexibility of mapping
    // * them together for now
    switch (currentGameState)
    {
    case GS_IDLE:
        melodyToPlay = MELODY_IDLE;
        break;
    case GS_START:
        melodyToPlay = MELODY_READY;
        break;
    case GS_PROCESSING:
        melodyToPlay = MELODY_PROCESSING;
        break;
    case GS_COMPLETE:
        melodyToPlay = MELODY_COMPLETE;
        break;
    }

    if (player.currentMelody == melodyToPlay)
    {
        player.playMelodyWithoutDelay();
    }
    else
    {
        player.stopPlaying();
        player.reset();
        player.setActiveMelody(melodyToPlay);
        player.playMelodyWithoutDelay();
    }
}

void rotateGameState()
{
    switch (currentGameState)
    {
    case GS_IDLE:
        currentGameState = GS_START;
        break;
    case GS_START:
        currentGameState = GS_PROCESSING;
        break;
    case GS_PROCESSING:
        currentGameState = GS_COMPLETE;
        break;
    case GS_COMPLETE:
        currentGameState = GS_IDLE;
        break;
    }
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

    player.playMelody(MELODY_READY);
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
