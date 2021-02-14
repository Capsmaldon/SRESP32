#include "sresp32Display.h"
#include "sresp32Audio.h"

Sresp32Display sresp32Display;
Sresp32Audio sresp32Audio;

void audioLoop(void* parameters)
{
  while(true)
  {
    sresp32Audio.tick();
  }
}

void displayLoop(void* parameters)
{
  while(true)
  {
    sresp32Display.tick();
  }
}

void setup() {
  sresp32Audio.initialise();
  sresp32Display.initialise();

  xTaskCreatePinnedToCore(audioLoop, "Audio", 10000, NULL, 1, NULL,  0); 
  xTaskCreatePinnedToCore(displayLoop, "Display", 10000, NULL, 1, NULL,  1); 
}

void loop() {
}