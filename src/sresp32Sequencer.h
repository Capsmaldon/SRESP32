#ifndef SRESP_32_SEQUENCER_H
#define SRESP_32_SEQUENCER_H

#include "Sresp32Model.h"

class Sresp32Sequencer
{
    public:
    Sresp32Sequencer(Sresp32Model &model);

    bool tick();

    private:
    Sresp32Model &model;
    unsigned long time = 0;

    void updateCounter();

    int stepCounter = 0;
    int stepNum = 8;
    int stepDelay = 100;
    int stepDirection = 1;
};

#endif