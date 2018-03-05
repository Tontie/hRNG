#include <QuickStats.h>
#include <SPI.h>
#include <hRNG.h>

QuickStats stats;
hRNG::funk *rng;

const int pool = 100;  //larger pool = smaller std. dev. This is good.
const int del = 50;    //delay of 5 vs 500 no effect on std. dev. Also good.

uint8_t x, y, z;
float dev[pool];
float maxDev = 0;

void setup() {
  Serial.begin(115200);
  delay(20);
  while(!Serial){
    ; //Make sure Serial starts
  }
  Serial.println();
  Serial.print("Hard Reset");
  Serial.println();
  
  rng->init();

}

void loop() {
  
  Serial.println();
  Serial.print("Soft Reset");
  Serial.println();

  //Every 100th pass through the "for" loop, for some reason there is a soft reset.
  //maybe some strange interrupt in the hRNG lib? Will address later.
  
  for(z = 1, y = 1; z < pool; z++, y++){
      if(y == 1){
         Serial.println();
      }
      if(y != 1){
         Serial.print("  ::  ");
      }
      x = rng->Randy();
      dev[z] = x;
      Serial.print(x);
      if(z%5 == 0){
         Serial.print("        || ");
         Serial.print(stats.stdev(dev, pool));
         if(stats.stdev(dev, pool) > maxDev){
            maxDev = stats.stdev(dev, pool);
         }
         Serial.print(" || ");
         Serial.print(maxDev);
         y = 0;
      }
      delay(del);
  }
}
