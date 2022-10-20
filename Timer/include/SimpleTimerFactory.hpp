#pragma once

#include "TimerAbstractFactory.hpp"

struct SimpleTimerFactory: TimerAbstractFactory
{
    std::unique_ptr<ITimer> CreateOneShotTimer(std::function<void()>, std::chrono::milliseconds);
    std::unique_ptr<ITimer> CreateRecurringTimer(std::function<void()>, std::chrono::milliseconds);
};
