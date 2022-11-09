#pragma once

#include <functional>
#include <memory>

#include "ITimer.hpp"


struct TimerAbstractFactory{
    [[nodiscard]]
    virtual std::unique_ptr<ITimer> CreateOneShotTimer(const std::function<void()>, const std::chrono::duration<double, std::ratio<1,1>>, const std::chrono::nanoseconds checktime) const = 0;
    [[nodiscard]]
    virtual std::unique_ptr<ITimer> CreateRecurringTimer(const std::function<void()>, const std::chrono::duration<double, std::ratio<1,1>>, const std::chrono::nanoseconds checktime) const = 0;
};
