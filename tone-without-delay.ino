#include <Adafruit_NeoPixel.h>
#include "src/melodyPlayer/MelodyPlayer.h"

const int SPEAKER = 3;
const int LEDs = 2;

MelodyPlayer player = MelodyPlayer(SPEAKER);
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
    player.playMelody(READY);
    Serial.begin(9600);
    // while (!Serial)
    //     ;
    bar.begin();
    bar.show();
    showReady();
}

void loop()
{
    unsigned long currentMillis = millis();
    handleLights(currentMillis);

    // | is the current tone playing the same as the current state? Note that the player should retain the state even after song is played
    // * mapping the game state enum to the melody enum, really we could prob
    // * conflate the two enums, but I kind of like the flexibility of mapping
    // * them together for now
    switch (currentGameState)
    {
    case GS_IDLE:
        melodyToPlay = IDLE;
        break;
    case GS_START:
        melodyToPlay = READY;
        break;
    case GS_PROCESSING:
        melodyToPlay = PROCESSING;
        break;
    case GS_COMPLETE:
        melodyToPlay = COMPLETE;
        break;
    }

    if (player.currentMelody == melodyToPlay)
    {
        // | yes => continue playing
        Serial.println("in the if ");
        player.playMelodyWithoutDelay();
    }
    else
    {
        Serial.println("in the else ");
        // ^ no:
        // ^ stop playing current melody
        player.stopPlaying();
        // ^ reset player state (playcount, active note, anything else?)
        player.reset();
        // ^ set the new melody
        player.setActiveMelody(melodyToPlay);
        // ^ trigger play (will play once and stop)
        player.playMelodyWithoutDelay();
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

    player.playMelody(READY);
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
