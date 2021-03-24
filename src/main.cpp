#include <memory>

#include "sresp32Model.h"
#include "sresp32Core.h"
#include "sresp32Audio.h"
#include "sresp32Pins.h"

std::unique_ptr<Sresp32Model> sresp32Model;
std::unique_ptr<Sresp32Pins> sresp32Pins;
std::unique_ptr<Sresp32Core> sresp32Core;
std::unique_ptr<Sresp32Audio> sresp32Audio;

void audioLoop(void* parameters)
{
  while(true) sresp32Audio->tick();
}

void coreLoop(void* parameters)
{
  while(true) sresp32Core->tick();
}

void pinLoop(void* parameters)
{
  while(true) sresp32Pins->tick();
}

void setup() {
  sresp32Model = std::unique_ptr<Sresp32Model>(new Sresp32Model());
  sresp32Pins = std::unique_ptr<Sresp32Pins>(new Sresp32Pins(*sresp32Model));
  sresp32Core = std::unique_ptr<Sresp32Core>(new Sresp32Core(*sresp32Model));
  sresp32Audio = std::unique_ptr<Sresp32Audio>(new Sresp32Audio(*sresp32Model));

  xTaskCreatePinnedToCore(audioLoop, "Audio", 10000, NULL, 1, NULL,  0); 
  xTaskCreatePinnedToCore(coreLoop, "Core", 10000, NULL, 1, NULL,  1); 
  xTaskCreatePinnedToCore(pinLoop, "Pins", 10000, NULL, 1, NULL,  1); 
}

void loop() {
}