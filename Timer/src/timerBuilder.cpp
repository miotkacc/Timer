#include "timerBuilder.hpp"
#include "timer.hpp"

SimpleTimer TimerBuilder::CreateOneShotTimer(std::function<void()> function, std::chrono::milliseconds interval)
{
    return SimpleTimer({interval, function, false});
}

SimpleTimer TimerBuilder::CreateRecurringTimer(std::function<void()> function, std::chrono::milliseconds interval)
{
    return SimpleTimer({interval, function, true});
}
