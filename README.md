# hRNG
Simple hRNG access for the Adafruit nRF52 BLE Feather.

The bluefruit.h libraries reference an nRF52 library that has all the hardware registers beautifully laid out, but I really like the methods and organization presented by the paper "C++ Hardware Register Access Redux" (included in this repository).  My objective is to minimize the space this library takes during implimentation, and maximize the access speed to these True Random Numbers.  I am a chemist, not a programmer, but I really want True Random Numbers in my BTLE arduino based process control systems.

Also included in this repository (mostly for my reference) are the nRF52 datasheet from Nordic, the Cortex-M4 datasheet, and the Adafruit user-guide for the Feather.

Work to be done:
The header is a mess, I need to weed out a lot of the #includes that aren't actually required.

There may be excessive namespacing (hRNG namespace wrapper), and non-standard function names, but that is due to weird issues I was running into with Arduino IDE using "rand" function from the main IDE rather than the hRNG->rand function.

Currently the library is causing a "break" from the "for" loop every 100th pass of the random function. Probably from a stray interrupt?

I am updating this project currently in Sept. 2022 (about 5 years later), and at this point I don't trust 5 years ago myself.
