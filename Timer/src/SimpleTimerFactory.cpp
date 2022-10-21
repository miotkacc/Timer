#pragma once

#include <memory>

#include "SimpleTimerFactory.hpp"
#include "SimpleTimer.hpp"
#include "singleRunnerStrategy.hpp"
#include "recurringRunnerStrategy.hpp"
#include "functionInfo.hpp"

template <typename T>
std::unique_ptr<ITimer<T>> SimpleTimerFactory<T>::CreateOneShotTimer(std::function<void()> function, std::chrono::milliseconds interval)
{
    return std::make_unique<SimpleTimer<T>>(Timer::FunctionInfo{function, interval}, std::make_unique<SingleRunnerStrategy>());
}

template <typename T>
std::unique_ptr<ITimer<T>> SimpleTimerFactory<T>::CreateRecurringTimer(std::function<void()> function, std::chrono::milliseconds interval)
{
    return std::make_unique<SimpleTimer<T>>(Timer::FunctionInfo{function, interval}, std::make_unique<RecurringRunnerStrategy>());
}
