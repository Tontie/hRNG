# hRNG
Simple hRNG access for the Adafruit nRF52 BLE Feather.

The bluefruit.h libraries reference an nrf52 library that has all the hardware registers beautifully laid out, but I really like the methods and organization presented by the paper "C++ Hardware Register Access Redux" (included in this repository).  Also included are the nRF52 datasheet form Nordic (register details abound!), the Cortex-M4 datasheet, and the Adafruit user-guide for their feather. 

I am a chemist, not a programmer, but I couldn't find any utilizations of the hardware RNG in the nRF52 Feather, so I tried to make as simple/modular of a library as possible.  The header is a mess, I need to weed out a lot of the #includes that aren't actually required.  There may be excessive namespacing (hRNG namespace wrapper), and non-standard function names, but that is due to weird issues I was running into with Arduino IDE using "rand" function from the main IDE rather than the hRNG->rand function.

Currently the library is causing a soft reset of the main loop in the arduino every 100th pass of the random function. Not sure why or how, since one would expect a full reset on an overload?  Probably from a stray interrupt?
