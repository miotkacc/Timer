#pragma once

#include "TimerAbstractFactory.hpp"


struct SimpleTimerFactory: TimerAbstractFactory
{
    std::unique_ptr<ITimer> CreateOneShotTimer(const std::function<void()>, const std::chrono::duration<double, std::ratio<1,1>>, const std::chrono::nanoseconds checktime=std::chrono::nanoseconds{400}) const override;
    std::unique_ptr<ITimer> CreateRecurringTimer(const std::function<void()>, const std::chrono::duration<double, std::ratio<1,1>>, const std::chrono::nanoseconds checktime=std::chrono::nanoseconds{400}) const override;
};
