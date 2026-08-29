# Sound LED visualizer

A sound-reactive LED visualizer that makes LEDs dance to the volume of your music.

How it works: The sound sensor feeds analog signal to the board, which calculates the intensity using RMS, minus DC bias, then lights up 0 to 7 LEDs depending on how loud the sound is. The max level auto adjusts over time (with decay) so it adapts to the loudest recent sound.

Video of working example, tested against a few songs of different genre:

[![Working example](https://img.youtube.com/vi/avLi9cZeD4k/0.jpg)](https://www.youtube.com/watch?v=avLi9cZeD4k)

## Components used

- 7x LEDs
- 7x 220 ohm resistors
- Jumper wires: male to male (GPIO to LEDs) and male to female (GPIO to KY-037)
- ESP32-S3 dev board (Arduino boards will work as well)
- KY-037 sound sensor module
- Breadboard

## Environmnent

VSCode + PlatformIO

## Configurations

| Define | Purpose |
|---|---|
| `DEBUG` | Uncomment to enable serial logging |
| `SAMPLE_COUNT` | Samples per reading (256–512 recommended tradeoff between accuracy and delay) |
| `LOOP_DELAY` | Delay between readings (ms) |
| `READ_DELAY` | Delay between individual samples (us) |
| `DECAY_RATE` | How fast the auto-adjusting max level decays over time |
| `MIN_RMS` | Noise floor. Tune this using DEBUG output |

## Known Limitations
 
- No frequency detection. This only measures intensity/loudness, not pitch or tone.
- The KY-037 module doesn't pick up ambient/environmental sound well. It needs to be pressed directly against the speaker to get a usable signal.

