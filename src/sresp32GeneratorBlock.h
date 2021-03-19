#ifndef SRESP_32_GENERATOR_BLOCK_H
#define SRESP_32_GENERATOR_BLOCK_H

#include <memory>
#include "sresp32Model.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_TWOPI
#define M_TWOPI 3.14159265358979323846 * 2.0
#endif

class Sresp32Generator
{
    public:
    Sresp32Generator(const int sampleRate)
    {
        reset(sampleRate);
    }

    void reset(const int sampleRate)
    {
        this->sampleRate = sampleRate;
        phase = 0;
        phaseIncrement = 0;
    }

    void setNote(int midiNote)
    {
        if(midiNote == 0) phaseIncrement = 0;
        else
        {
            float freq = 440.0 * pow(2.0, (midiNote - 69)/12.0);
            phaseIncrement = (M_TWOPI/static_cast<double>(sampleRate)) * freq;
        }
    }

    void tick(int16_t* buffer, unsigned int bufferLength)
    {
        for(int i = 0; i < bufferLength; i++)
        {
            buffer[i] += (phase < M_PI ? 1 : -1) * 2000.0;
            phase += phaseIncrement;
            if(phase > M_TWOPI) phase -= M_TWOPI;
        }
    }
    
    private:
    int sampleRate = 0;
    double phase = 0.0;
    double phaseIncrement = 0.0;
};

class Sresp32GeneratorBlock : Sresp32ModelEntry::Observer
{
    public:
    Sresp32GeneratorBlock(Sresp32Model &model, const int sampleRate) : model(model)
    {
        for(int i = 0; i < 2; i++)
        {
            generators[i] = new Sresp32Generator(sampleRate);
        }

        generators[0]->setNote(60);
        generators[1]->setNote(72);

        model.getEntry(1).addObserver(this);
    }

    void tick(int16_t* buffer, unsigned int bufferLength)
    {
        for(int voice = 0 ; voice < 2; voice++)
        {
            generators[voice]->tick(buffer, bufferLength);
        }
    }

    private:
    Sresp32Model &model;
    Sresp32Generator* generators[2];

    void notified(Sresp32ModelEntry::LockedDataReference &data) override
    {
        int step = *static_cast<int*>(data.data);
        int* sequence = static_cast<int*>(model.getEntry(2).access().data);

        for(int voice = 0; voice < 2; voice++)
        {
            int note = sequence[step * 2 + voice];
            generators[voice]->setNote(note);
        }
    }
};

#endif