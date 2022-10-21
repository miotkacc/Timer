#pragma once

#include <functional>
#include <memory>

#include "ITimer.hpp"

template <typename T>
struct TimerAbstractFactory{
    virtual std::unique_ptr<ITimer<T>> CreateOneShotTimer(std::function<void()>, std::chrono::milliseconds) = 0;
    virtual std::unique_ptr<ITimer<T>> CreateRecurringTimer(std::function<void()>, std::chrono::milliseconds) = 0;
};
