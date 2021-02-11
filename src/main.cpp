#include "sresp32Display.h"
#include "sresp32Audio.h"

//Sresp32Display sresp32Display;
Sresp32Audio sresp32Audio;

void setup() {
  // put your setup code here, to run once:
  //sresp32Display.initialise();
  sresp32Audio.initialise();
}

void loop() {
  // put your main code here, to run repeatedly:
  //sresp32Display.tick();
  sresp32Audio.tick();
}