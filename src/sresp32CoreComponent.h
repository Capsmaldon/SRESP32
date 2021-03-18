#ifndef SRESP_32_CORE_COMPONENT_H
#define SRESP_32_CORE_COMPONENT_H

#include <Arduino.h>
#include <heltec.h>

#include "sresp32Model.h"

class Sresp32CoreComponent : public Sresp32ModelEntry::Observer
{
public:
    Sresp32CoreComponent(Sresp32Model &model) : model(model)
    {
        display = Heltec.display;
        model.getEntry(1).addObserver(this);
    }

    void notified(Sresp32ModelEntry::LockedDataReference &data) override
    {
        stepCounter = *static_cast<int*>(data.data);
    }

    void paint()
    {
        String counterString(stepCounter);
        display->drawString(0, 0, counterString);
    }

private:
    SSD1306Wire* display = nullptr;
    Sresp32Model &model;

    int stepCounter = 0;
};

#endif