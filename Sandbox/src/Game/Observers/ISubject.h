#pragma once

#include "Game/Observers/IObserver.h"

#include <memory>
#include <vector>

template <class T>
class ISubject
{
private:
    std::vector<std::shared_ptr<IObserver<T>>> mObservers;

public:
    virtual ~ISubject() = default;

    virtual inline void RegisterObserver(std::shared_ptr<IObserver<T>> observer)
    {
        mObservers.push_back(observer);
    }

    virtual inline void RemoveObserver(std::shared_ptr<IObserver<T>> observer)
    {
        auto iterator = std::find(mObservers.begin(), mObservers.end(), observer);

        if (iterator != mObservers.end())
            mObservers.erase(iterator);
    }

    virtual inline void NotifyObservers()
    {
        for (auto observer : mObservers)
            observer->Update(static_cast<T*>(this));
    }
};