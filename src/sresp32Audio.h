#ifndef SRESP_32_AUDIO_H
#define SRESP_32_AUDIO_H

#include <Arduino.h>
#include "driver/i2s.h"
#include "sresp32Model.h"
#include "sresp32GeneratorBlock.h"

class Sresp32Audio : public Sresp32ModelEntry::Observer
{
public:
    Sresp32Audio(Sresp32Model &model);
    void notified(Sresp32ModelEntry::LockedDataReference &data) override;
    void setNote(int midiNote);
    void tick();

private:
    const int bufferLength = 64;
    const int sampleRate = 44100;
    int16_t buffer[64];

    Sresp32Model &model;
    float volume = 1.0f;

    Sresp32GeneratorBlock generators;
};

#endif