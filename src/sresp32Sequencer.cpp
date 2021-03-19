#include "sresp32Sequencer.h"

Sresp32Sequencer::Sresp32Sequencer(Sresp32Model &model) : model(model)
{
    auto dataRef = model.getEntry(2).access();
    int* sequence = static_cast<int*>(dataRef.data);

    sequence[0 * 2 + 0] = 60;
    sequence[1 * 2 + 0] = 62;
    sequence[2 * 2 + 0] = 64;
    sequence[3 * 2 + 0] = 65;
    sequence[4 * 2 + 0] = 67;
    sequence[5 * 2 + 0] = 69;
    sequence[6 * 2 + 0] = 71;
    sequence[7 * 2 + 0] = 72;

    sequence[0 * 2 + 1] = 0;
    sequence[1 * 2 + 1] = 38;
    sequence[2 * 2 + 1] = 0;
    sequence[3 * 2 + 1] = 41;
    sequence[4 * 2 + 1] = 0;
    sequence[5 * 2 + 1] = 45;
    sequence[6 * 2 + 1] = 0;
    sequence[7 * 2 + 1] = 48;
}

bool Sresp32Sequencer::tick()
{
    bool ready = millis() > (time + stepDelay);

    if(ready)
    {
        time = millis();
        updateCounter();

        // Sresp32ModelEntry::LockedDataReference data = model.getEntry(0).access();
        // float& volume = *static_cast<float*>(data.data);
        // if(volume <= 0.1f) volume = 1.0f;
        // else volume = 0.0f;
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