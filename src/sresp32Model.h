#ifndef SRESP_32_MODEL_H
#define SRESP_32_MODEL_H

#include <atomic>
#include <Arduino.h>
#include <unordered_map>
#include <mutex>
#include <string.h>

namespace Sresp32
{
    enum Model
    {
        VOLUME = 0,
        VOICES,
        STEPS,
        STEP,
        SEQUENCE
    };
}

class Sresp32ModelEntry
{
public:
    class LockedDataReference
    {
        public:
        LockedDataReference(const int key, const size_t size, void* data, std::mutex &lock, Sresp32ModelEntry &entry);
        ~LockedDataReference();
        void disableNotification();

        const int key;
        const size_t size;
        void* data;

        private:
        bool notify = true;
        std::mutex &modelLock;
        Sresp32ModelEntry &entry;
    };

    class Observer
    {
        public:
        virtual ~Observer();
        void link(Sresp32ModelEntry* entry, const size_t size);
        void notify();
        virtual void notified(LockedDataReference &data) = 0;

        private:
        Sresp32ModelEntry* linkedEntry;
    };

    Sresp32ModelEntry(const int key, size_t bytes);
    Sresp32ModelEntry(const Sresp32ModelEntry& other);

    void release();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observerToRemove);
    void updateObservers();
    LockedDataReference access();
    
private:
    std::mutex lock;

    const int key;
    const size_t size;
    void* data;
    std::vector<Observer*> observers;
};

class Sresp32Model
{
    public:
    Sresp32Model();
    ~Sresp32Model();
    void addEntry(int key, unsigned long numOfBytes);
    Sresp32ModelEntry& getEntry(int key);

    private:
    std::unordered_map<int, Sresp32ModelEntry> model;
};

#endif