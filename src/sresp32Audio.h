#ifndef SRESP_32_AUDIO_H
#define SRESP_32_AUDIO_H

#include <Arduino.h>
#include "driver/i2s.h"
#include "freertos/queue.h"
#include "sresp32Model.h"
#include <atomic>

#ifndef M_TWOPI
#define M_TWOPI 3.14159265358979323846 * 2.0
#endif

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
    double phase = 0;
    double phaseIncrement;
    int16_t buffer[64];

    Sresp32Model &model;
    float volume = 1.0f;
    int step = 0;
};

#endif