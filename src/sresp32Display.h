#ifndef SRESP_32_DISPLAY_H
#define SRESP_32_DISPLAY_H

#include <Arduino.h>
#include <heltec.h>

class Sresp32Display
{
    public:

    void initialise()
    {
        Heltec.begin(true, false, true);
        Heltec.display->clear();
    }

    void tick()
    {
        String counterString(stepCounter);
        Heltec.display->clear();
        Heltec.display->drawString(0, 0, counterString);
        Heltec.display->display();
        updateCounter();
        delay(stepDelay);
    }

    private:

    void updateCounter()
    {
        stepCounter += stepDirection;
        if(stepCounter >= stepNum) stepCounter = 0;
        else if(stepCounter < 0) stepCounter = stepNum-1;
    }

    int stepCounter = 0;
    int stepNum = 8;
    int stepDelay = 500;
    int stepDirection = 1;
};

#endif