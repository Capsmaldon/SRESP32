#include "sresp32CoreComponent.h"

Sresp32CoreComponent::Sresp32CoreComponent(Sresp32Model &model) : model(model)
{
    display = Heltec.display;
    model.getEntry(1).addObserver(this);
}

void Sresp32CoreComponent::notified(Sresp32ModelEntry::LockedDataReference &data)
{
    stepCounter = *static_cast<int*>(data.data);
}

void Sresp32CoreComponent::paint()
{
    String counterString(stepCounter);
    display->drawString(0, 0, counterString);
}