#include "sresp32Sequencer.h"

Sresp32Sequencer::Sresp32Sequencer(Sresp32Model &model) : model(model)
{
    auto dataRef = model.getEntry(2).access();
    int* sequence = static_cast<int*>(dataRef.data);
    sequence[0] = 60;
    sequence[1] = 62;
    sequence[2] = 64;
    sequence[3] = 65;
    sequence[4] = 67;
    sequence[5] = 69;
    sequence[6] = 70;
    sequence[7] = 71;
}

bool Sresp32Sequencer::tick()
{
    bool ready = millis() > (time + stepDelay);

    if(ready)
    {
        time = millis();
        updateCounter();

        Sresp32ModelEntry::LockedDataReference data = model.getEntry(0).access();
        float& volume = *static_cast<float*>(data.data);
        if(volume <= 0.1f) volume = 1.0f;
        else volume = 0.0f;
    }
    return ready;
}

void Sresp32Sequencer::updateCounter()
{
    stepCounter += stepDirection;
    if(stepCounter >= stepNum) stepCounter = 0;
    else if(stepCounter < 0) stepCounter = stepNum-1;

    Sresp32ModelEntry::LockedDataReference data = model.getEntry(1).access();
    int& counter = *static_cast<int*>(data.data);
    counter = stepCounter;
}