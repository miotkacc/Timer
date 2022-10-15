#pragma once

#include "timer.hpp"

struct TimerBuilder
{
    static SimpleTimer CreateOneShotTimer(std::function<void()>, std::chrono::milliseconds);
    static SimpleTimer CreateRecurringTimer(std::function<void()>, std::chrono::milliseconds);
};