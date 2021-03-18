#ifndef SRESP_32_SEQUENCER_H
#define SRESP_32_SEQUENCER_H

class Sresp32Sequencer
{
    public:
    Sresp32Sequencer(Sresp32Model &model) : model(model)
    {

    }

    bool tick()
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

    private:
    Sresp32Model &model;
    unsigned long time = 0;

    void updateCounter()
    {
        stepCounter += stepDirection;
        if(stepCounter >= stepNum) stepCounter = 0;
        else if(stepCounter < 0) stepCounter = stepNum-1;

        Sresp32ModelEntry::LockedDataReference data = model.getEntry(1).access();
        int& counter = *static_cast<int*>(data.data);
        counter = stepCounter;
    }

    int stepCounter = 0;
    int stepNum = 8;
    int stepDelay = 100;
    int stepDirection = 1;
};

#endif