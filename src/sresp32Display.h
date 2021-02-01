#include <Arduino.h>
#include <heltec.h>

class Sresp32Display
{
    public:

    void run()
    {
        Heltec.begin(true, false, true);
        Heltec.display->clear();
    }

    void tick()
    {
        String counterString(counter);
        Heltec.display->clear();
        Heltec.display->drawString(0, 0, counterString);
        Heltec.display->display();
        updateCounter();
        delay(500);
    }

    private:

    void updateCounter()
    {
        counter++;
        if(counter >= 8) counter = 0;
    }



    int counter = 0;
};