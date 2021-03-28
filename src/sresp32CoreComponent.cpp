#include "sresp32CoreComponent.h"

Sresp32CoreComponent::Sresp32CoreComponent(Sresp32Model &model) : model(model)
{
    display = Heltec.display;
    model.getEntry(Sresp32::STEP).addObserver(this);
    Sresp32ModelEntry::LockedDataReference data = model.getEntry(Sresp32::SEQUENCE).access();

    int* sequence = static_cast<int*>(data.data);
    for(int voice = 0; voice < 2; voice++)
    {
        for(int note = 0; note < 8; note++)
        {
            notes[voice][note] = sequence[note * 2 + voice];
        }
    }
}

void Sresp32CoreComponent::notified(Sresp32ModelEntry::LockedDataReference &data)
{
    stepCounter = *static_cast<int*>(data.data);
}

void Sresp32CoreComponent::paint()
{
    String title = "Tracker";
    String counterString = "" + String(stepCounter);
    const int titleBarHeight = 16;

    display->drawString(0, titleBarHeight - 11, title);
    display->drawHorizontalLine(0, titleBarHeight, 128);

    const int notesToDisplay = 4;
    for(int voice = 0; voice < 2; voice++)
    {
        int x = voice * 27;

        display->drawString(x + 3, titleBarHeight, counterString);
        display->setColor(OLEDDISPLAY_COLOR::INVERSE);
        display->fillRect(x + 2, titleBarHeight + 2, 24, 9);
        display->setColor(OLEDDISPLAY_COLOR::WHITE);
        display->drawVerticalLine(voice * x, titleBarHeight, 64 - 11);

        const int numOfNotes = 8;
        int startStep = stepCounter - 1;

        for(int note = startStep; note < startStep + notesToDisplay; note++)
        {
            int y = (note - startStep) * 9 + titleBarHeight + 9;

            int noteIndex = note >= numOfNotes ? note - numOfNotes : note < 0 ? note + numOfNotes : note;
            display->drawString(x + 3, y, getNoteString(notes[voice][noteIndex]));

            if(note == stepCounter)
            {
                display->setColor(OLEDDISPLAY_COLOR::INVERSE);
                display->fillRect(x + 2, y + 2, 24, 9);
                display->setColor(OLEDDISPLAY_COLOR::WHITE);
            }
        }
    } 
}

String Sresp32CoreComponent::getNoteString(int midiNote)
{
    static String names[12] {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    return midiNote == 0 ? "-" : names[midiNote % 12] + String(midiNote/12);
}