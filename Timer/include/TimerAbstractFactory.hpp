#pragma once

#include <functional>
#include <memory>

#include "ITimer.hpp"


struct TimerAbstractFactory{
    virtual std::unique_ptr<ITimer> CreateOneShotTimer(std::function<void()>, std::chrono::duration<double, std::ratio<1,1>>, std::chrono::nanoseconds checktime) = 0;
    virtual std::unique_ptr<ITimer> CreateRecurringTimer(std::function<void()>, std::chrono::duration<double, std::ratio<1,1>>, std::chrono::nanoseconds checktime) = 0;
};
