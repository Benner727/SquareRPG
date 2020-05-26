#pragma once

#include <Square.h>

#include <string>

template <class T>
class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void Update(T* subject) = 0;
};