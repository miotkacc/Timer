#include <memory>

#include "SimpleTimerFactory.hpp"
#include "SimpleTimer.hpp"
#include "SingleRunnerStrategy.hpp"
#include "RecurringRunnerStrategy.hpp"
#include "FunctionInfo.hpp"


std::unique_ptr<ITimer> SimpleTimerFactory::CreateOneShotTimer(const std::function<void()> function, const std::chrono::duration<double, std::ratio<1,1>> interval, const std::chrono::nanoseconds checktime) const
{
    return std::make_unique<SimpleTimer>(std::make_unique<SingleRunnerStrategy>(Timer::FunctionInfo{function, std::chrono::duration_cast<std::chrono::milliseconds>(interval)}, checktime));
}

std::unique_ptr<ITimer> SimpleTimerFactory::CreateRecurringTimer(const std::function<void()> function, const std::chrono::duration<double, std::ratio<1,1>> interval, const std::chrono::nanoseconds checktime) const
{
    return std::make_unique<SimpleTimer>(std::make_unique<RecurringRunnerStrategy>(Timer::FunctionInfo{function, std::chrono::duration_cast<std::chrono::milliseconds>(interval)}, checktime));
}
