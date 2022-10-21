#pragma once

#include "TimerAbstractFactory.hpp"

template <typename T>
struct SimpleTimerFactory: TimerAbstractFactory<T>
{
    std::unique_ptr<ITimer<T>> CreateOneShotTimer(std::function<void()>, std::chrono::milliseconds);
    std::unique_ptr<ITimer<T>> CreateRecurringTimer(std::function<void()>, std::chrono::milliseconds);
};

#include "../src/SimpleTimerFactory.cpp"
