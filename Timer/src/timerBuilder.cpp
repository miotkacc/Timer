#include "timerBuilder.hpp"
#include "timer.hpp"
#include "singleRunnerStrategy.hpp"
#include "recurringRunnerStrategy.hpp"


SimpleTimer TimerBuilder::CreateOneShotTimer(std::function<void()> function, std::chrono::milliseconds interval)
{
    return SimpleTimer({function, interval}, std::make_unique<SingleRunnerStrategy>());
}

SimpleTimer TimerBuilder::CreateRecurringTimer(std::function<void()> function, std::chrono::milliseconds interval)
{
    return SimpleTimer({function, interval}, std::make_unique<RecurringRunnerStrategy>());
}
