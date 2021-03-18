#include "sresp32Audio.h"

Sresp32Audio::Sresp32Audio(Sresp32Model &model) : model(model)
{
    static const i2s_config_t i2s_config = {
        .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = sampleRate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = static_cast<i2s_comm_format_t>(I2S_COMM_FORMAT_I2S),
        .intr_alloc_flags = 0, // default interrupt priority
        .dma_buf_count = 8,
        .dma_buf_len = bufferLength,
        .use_apll = false
    };

    static const i2s_pin_config_t pin_config = {
        .bck_io_num = 12,
        .ws_io_num = 14,
        .data_out_num = 13,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
    i2s_set_sample_rates(I2S_NUM_0, 44100);

    setNote(60);

    model.getEntry(0).addObserver(this);
    model.getEntry(1).addObserver(this);
}

void Sresp32Audio::notified(Sresp32ModelEntry::LockedDataReference &data)
{
    switch(data.key)
    {
        case 0: //Volume
        volume = *static_cast<float*>(data.data);
        break;

        case 1: //Step
        {
        step = *static_cast<int*>(data.data);
        int* sequence = static_cast<int*>(model.getEntry(2).access().data);
        int note = sequence[step];
        setNote(note);
        }
        break;
    }
}

void Sresp32Audio::setNote(int midiNote)
{
    float freq = 440.0 * pow(2.0, (midiNote - 69)/12.0);
    phaseIncrement = (M_TWOPI/static_cast<double>(sampleRate)) * freq;
}

void Sresp32Audio::tick()
{
    for(int i = 0; i < bufferLength; i++)
    {
        buffer[i] = sin(phase) * 2000 * volume;
        phase += phaseIncrement;
        if(phase > M_TWOPI) phase -= M_TWOPI;
    }

    size_t bytesWritten = 0;
    i2s_write(I2S_NUM_0, buffer, bufferLength * sizeof(int16_t), &bytesWritten, 1000);
}