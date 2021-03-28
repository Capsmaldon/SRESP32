#ifndef SRESP_32_PINS_H
#define SRESP_32_PINS_H

#include <Arduino.h>
#include <Esp32Encoder.h>
#include "sresp32Model.h"

class Sresp32Pins
{
    public:
    Sresp32Pins(Sresp32Model &model) : model(model)
    {
        Serial.begin(115200);
        encoder.attachHalfQuad(17, 5);
    }

    void tick()
    {
        int count = encoder.getCount() / 2;
        if(count)
        {
            encoder.clearCount();
            Serial.println(count);

            Sresp32ModelEntry::LockedDataReference data = model.getEntry(Sresp32::VOLUME).access();
            float& volume = *static_cast<float*>(data.data);
            volume = volume + (count * 0.1f);
            if(volume < 0.0f) volume = 0.0f;
            else if(volume > 1.0f) volume = 1.0f;
        }

        vTaskDelay(40);
    }

    private:
    Sresp32Model &model;
    ESP32Encoder encoder;
};


#endif

