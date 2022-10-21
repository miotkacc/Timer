#pragma once

#include <chrono>

template <typename T>
struct ITimer{
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual T getElapsedTime() const = 0;
};