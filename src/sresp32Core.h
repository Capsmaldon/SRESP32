#ifndef SRESP_32_CORE_H
#define SRESP_32_CORE_H

#include <Arduino.h>
#include <heltec.h>
#include "sresp32Model.h"
#include "sresp32Sequencer.h"
#include "sresp32CoreComponent.h"

class Sresp32Core
{
    public:
    Sresp32Core(Sresp32Model &model);
    void tick();

    private:
    Sresp32Sequencer sequencer;
    Sresp32CoreComponent coreComponent;
};

#endif