# Tone without delay

![demo](readme_attachments/demo.gif)

[video explanation of demo](https://vimeo.com/343229038)

I'm trying to work through using the arduino tone function without delay similar to the blink without delay.

Really, this should be a proof of concept folder in my [pegasus plinko project repository](https://github.com/chris-schmitz/pegasus), but I foresee running into the need for this concept frequently in the future so I wanted to work out the core structure and thought process separately so I could refer back to it more easily in the future.

# The basic idea

In the main Pegasus project I want to run the leds for the pegs and the sound effects from the same microcontroller and I want the patterns for both the tones and the lights to be interruptible and changeable at any point. Because of this I knew that I couldn't count on using delay for either.

I already have a proof of concept (in the pegasus project folder) for handling the lights, but I hadn't done a tone-without-delay a la blink without delay before, so I thought I'd do another isolated proof of concept to figure it out. I also knew that I'd prob need this specific logic for future projects outside of pegasus, so I decided to do this POC stand alone.

## How it works

The TunePlayer class is just an abstraction of a state machine. It will let you tell it which of a select few tunes (tunes = melody + durations + tone) you'd like to play and when you tell it to play without delay it will, you know, play the tune without delay and tt will only play the tune once.

The code is _kindof_ well commented, but the comments are aimed at future me, not necessarily at a wider audience, so I hope but cannot guarantee they'll be helpful ;P
