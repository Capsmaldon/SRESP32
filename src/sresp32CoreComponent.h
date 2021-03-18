#ifndef SRESP_32_CORE_COMPONENT_H
#define SRESP_32_CORE_COMPONENT_H

#include <Arduino.h>
#include <heltec.h>
#include "sresp32Model.h"

class Sresp32CoreComponent : public Sresp32ModelEntry::Observer
{
public:
    Sresp32CoreComponent(Sresp32Model &model);
    void notified(Sresp32ModelEntry::LockedDataReference &data) override;
    void paint();

private:
    SSD1306Wire* display = nullptr;
    Sresp32Model &model;

    int stepCounter = 0;
};

#endif