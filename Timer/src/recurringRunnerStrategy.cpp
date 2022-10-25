#include <thread>

#include "recurringRunnerStrategy.hpp"
#include "functionInfo.hpp"
#include "ITimer.hpp"

RecurringRunnerStrategy::RecurringRunnerStrategy(std::chrono::nanoseconds period):
checkOfElapsedTimePeriod{period}
{};

void RecurringRunnerStrategy::stop()
{
    stopVar = true;
}

void RecurringRunnerStrategy::run(const Timer::FunctionInfo& functionInfo, ITimer* const timer){
    int lastIntervalCall{};
    while(not stopVar)
    {
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + checkOfElapsedTimePeriod);
        auto actualInterval = timer->getElapsedTime() / functionInfo.interval;
        bool isTimeElapsed =  lastIntervalCall != actualInterval;
        if(isTimeElapsed){
            functionInfo.funName();
            lastIntervalCall = actualInterval;
        }
    }
}
