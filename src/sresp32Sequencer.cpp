#include "sresp32Sequencer.h"

Sresp32Sequencer::Sresp32Sequencer(Sresp32Model &model) : model(model)
{
    auto dataRef = model.getEntry(Sresp32::SEQUENCE).access();
    int* sequence = static_cast<int*>(dataRef.data);

    sequence[0 * 2 + 0] = 59;
    sequence[1 * 2 + 0] = 61;
    sequence[2 * 2 + 0] = 63;
    sequence[3 * 2 + 0] = 64;
    sequence[4 * 2 + 0] = 66;
    sequence[5 * 2 + 0] = 68;
    sequence[6 * 2 + 0] = 70;
    sequence[7 * 2 + 0] = 71;

    sequence[0 * 2 + 1] = 0;
    sequence[1 * 2 + 1] = 37;
    sequence[2 * 2 + 1] = 0;
    sequence[3 * 2 + 1] = 40;
    sequence[4 * 2 + 1] = 0;
    sequence[5 * 2 + 1] = 44;
    sequence[6 * 2 + 1] = 0;
    sequence[7 * 2 + 1] = 47;
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

    Sresp32ModelEntry::LockedDataReference data = model.getEntry(Sresp32::STEP).access();
    int& counter = *static_cast<int*>(data.data);
    counter = stepCounter;
}