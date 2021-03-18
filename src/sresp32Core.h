#ifndef SRESP_32_DISPLAY_H
#define SRESP_32_DISPLAY_H

#include <Arduino.h>
#include <heltec.h>
#include "sresp32Sequencer.h"
#include "sresp32CoreComponent.h"

class Sresp32Core
{
    public:

    Sresp32Core(Sresp32Model &model) : sequencer(model), coreComponent(model)
    {
        Heltec.begin(true, false, true);
        Heltec.display->clear();
    }

    void tick()
    {
        if(sequencer.tick())
        {
            Heltec.display->clear();
            coreComponent.paint();
            Heltec.display->display();
        }
        vTaskDelay(1);
    }

    private:
    Sresp32Sequencer sequencer;
    Sresp32CoreComponent coreComponent;
};

#endif