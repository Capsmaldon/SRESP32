#include "sresp32Model.h"

Sresp32ModelEntry::LockedDataReference::LockedDataReference(const int key, const size_t size, void* data, std::mutex &lock, Sresp32ModelEntry &entry) : 
key(key), size(size), data(data), modelLock(lock), entry(entry)
{
    modelLock.lock();
}

Sresp32ModelEntry::LockedDataReference::~LockedDataReference()
{
    modelLock.unlock();
    if(notify) entry.updateObservers();
}

void Sresp32ModelEntry::LockedDataReference::disableNotification()
{
    notify = false;
}

Sresp32ModelEntry::Observer::~Observer()
{
    linkedEntry->removeObserver(this);
}
void Sresp32ModelEntry::Observer::link(Sresp32ModelEntry* entry, const size_t size)
{
    linkedEntry = entry;
}
void Sresp32ModelEntry::Observer::notify()
{
    LockedDataReference data = linkedEntry->access();
    data.disableNotification();
    notified(data);
}

Sresp32ModelEntry::Sresp32ModelEntry(const int key, size_t bytes) : key(key), size(bytes)
{
    data = malloc(size);
}

Sresp32ModelEntry::Sresp32ModelEntry(const Sresp32ModelEntry& other) : key(other.key), size(other.size), data(other.data)
{

}

void Sresp32ModelEntry::release()
{
    free(data);
}

void Sresp32ModelEntry::addObserver(Observer* observer)
{
    observer->link(this, size);
    observers.push_back(observer);
}

void Sresp32ModelEntry::removeObserver(Observer* observerToRemove)
{
    for(int i = 0; i < observers.size(); i++)
    {
        Observer* observer = observers[i];
        if(observerToRemove == observer)
        {
            observers.erase(observers.begin() + i);
            break;
        }
    }
}

void Sresp32ModelEntry::updateObservers()
{
    for(Observer* observer : observers)
    {
        observer->notify();
    }
}

Sresp32ModelEntry::LockedDataReference Sresp32ModelEntry::access()
{
    return LockedDataReference(key, size, data, lock, *this);
}

Sresp32Model::Sresp32Model()
{
    addEntry(0, sizeof(float));
    addEntry(1, sizeof(int));
    addEntry(2, sizeof(int) * 8 * 2);
}

Sresp32Model::~Sresp32Model()
{
    for(auto &valuePair : model) valuePair.second.release();
}

void Sresp32Model::addEntry(int key, unsigned long numOfBytes)
{
    model.emplace(key, Sresp32ModelEntry(key, numOfBytes));
}

Sresp32ModelEntry& Sresp32Model::getEntry(int key)
{
    return model.at(key);
}