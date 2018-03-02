# hRNG
Simple hRNG access for the Adafruit nRF52 BLE Feather.


Currently the library may be causing a soft reset of the main loop in the arduino every 100th pass of the random function.
Not sure why or how, since one would expect a full reset on an overload?  Could be from a stray interrupt?
