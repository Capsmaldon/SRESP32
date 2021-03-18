#ifndef SRESP_32_MODEL_H
#define SRESP_32_MODEL_H

#include <atomic>
#include <Arduino.h>
#include <unordered_map>
#include <mutex>
#include <string.h>

static std::mutex lock;

class Sresp32ModelEntry
{
public:
    class LockedDataReference
    {
        public:
        LockedDataReference(const int key, const size_t size, void* data, std::mutex &lock, Sresp32ModelEntry &entry) : 
        key(key), size(size), data(data), modelLock(lock), entry(entry)
        {
            modelLock.lock();
        }

        ~LockedDataReference()
        {
            modelLock.unlock();
            if(notify) entry.updateObservers();
        }

        void disableNotification()
        {
            notify = false;
        }

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
        virtual ~Observer()
        {
            linkedEntry->removeObserver(this);
        }
        void link(Sresp32ModelEntry* entry, const size_t size)
        {
            linkedEntry = entry;
        }
        void notify()
        {
            LockedDataReference data = linkedEntry->access();
            data.disableNotification();
            notified(data);
        }
        virtual void notified(LockedDataReference &data) = 0;

        private:
        Sresp32ModelEntry* linkedEntry;
    };

    Sresp32ModelEntry(const int key, size_t bytes) : key(key), size(bytes)
    {
        data = malloc(size);
    }

    void release()
    {
        free(data);
    }

    void addObserver(Observer* observer)
    {
        observer->link(this, size);
        observers.push_back(observer);
    }

    void removeObserver(Observer* observerToRemove)
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

    void updateObservers()
    {
        for(Observer* observer : observers)
        {
            observer->notify();
        }
    }

    LockedDataReference access()
    {
        return LockedDataReference(key, size, data, lock, *this);
    }
    
private:
    const int key;
    const size_t size;
    void* data;
    std::vector<Observer*> observers;
};

class Sresp32Model
{
    public:
    Sresp32Model()
    {
        addEntry(0, sizeof(float));
        addEntry(1, sizeof(int));
    }

    ~Sresp32Model()
    {
        for(auto &valuePair : model) valuePair.second.release();
    }

    void addEntry(int key, unsigned long numOfBytes)
    {
        model.emplace(key, Sresp32ModelEntry(key, numOfBytes));
    }

    Sresp32ModelEntry& getEntry(int key)
    {
        return model.at(key);
    }

    private:
    std::unordered_map<int, Sresp32ModelEntry> model;
};

#endif