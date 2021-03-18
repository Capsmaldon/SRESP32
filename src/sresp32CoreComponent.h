#ifndef SRESP_32_CORE_COMPONENT_H
#define SRESP_32_CORE_COMPONENT_H

#include <Arduino.h>
#include <heltec.h>

#include "sresp32Tracker.h"
#include "sresp32Model.h"

class Sresp32CoreComponent
{
public:
    Sresp32CoreComponent(Sresp32Model &model) : model(model)
    {
        display = Heltec.display;
    }

    void paint()
    {
        Sresp32ModelEntry::LockedDataReference data = model.getEntry(1).access();
        int stepCounter = *static_cast<int*>(data.data);
        String counterString(stepCounter);
        display->drawString(0, 0, counterString);
    }

private:
    SSD1306Wire* display = nullptr;
    Sresp32Model &model;
};

#endif