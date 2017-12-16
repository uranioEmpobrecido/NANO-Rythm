// RYTHM, the simple drum box
//
// All in the spirit of open-source and open-hardware
// by Jorge Gutiérrez
//
// NANO
//
// 2017 Spain
//
// MAIN CODE

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "VARIABLES.h"

void setup() {
  
  GPIOSetup(); 
  //Sound that says that RYTHM is ready to work
  startPlayback(blip,blip_length);
}

void loop() {
  //Sound processing
  BeatEffect();
}
