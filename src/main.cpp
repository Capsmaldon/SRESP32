#include "sresp32Display.h"
#include "sresp32Audio.h"

Sresp32Display sresp32Display;

void setup() {
  // put your setup code here, to run once:
  sresp32Display.initialise();
}

void loop() {
  // put your main code here, to run repeatedly:
  sresp32Display.tick();
}