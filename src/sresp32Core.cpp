#include "sresp32Core.h"

Sresp32Core::Sresp32Core(Sresp32Model &model) : sequencer(model), coreComponent(model)
{
    Heltec.begin(true, false, true);
    Heltec.display->clear();
}

void Sresp32Core::tick()
{
    if(sequencer.tick())
    {
        Heltec.display->clear();
        coreComponent.paint();
        Heltec.display->display();
    }
    vTaskDelay(1);
}