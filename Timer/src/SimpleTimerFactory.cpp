#include <memory>

#include "SimpleTimerFactory.hpp"
#include "SimpleTimer.hpp"
#include "SingleRunnerStrategy.hpp"
#include "RecurringRunnerStrategy.hpp"
#include "FunctionInfo.hpp"

std::unique_ptr<ITimer> SimpleTimerFactory::CreateOneShotTimer(std::function<void()> function, std::chrono::duration<double, std::ratio<1,1>> interval)
{
    return std::make_unique<SimpleTimer>(Timer::FunctionInfo{function, std::chrono::duration_cast<std::chrono::milliseconds>(interval)}, std::make_unique<SingleRunnerStrategy>());
}

std::unique_ptr<ITimer> SimpleTimerFactory::CreateRecurringTimer(std::function<void()> function, std::chrono::duration<double, std::ratio<1,1>> interval)
{
    return std::make_unique<SimpleTimer>(Timer::FunctionInfo{function, std::chrono::duration_cast<std::chrono::milliseconds>(interval)}, std::make_unique<RecurringRunnerStrategy>());
}
