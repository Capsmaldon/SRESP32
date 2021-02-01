#include "sresp32Display.h"

Sresp32Display sresp32Display;

void setup() {
  // put your setup code here, to run once:
  sresp32Display.run();
}

void loop() {
  // put your main code here, to run repeatedly:
  sresp32Display.tick();
}