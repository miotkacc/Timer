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

RecurringRunnerStrategy::~RecurringRunnerStrategy()
{
    stop();
}

void RecurringRunnerStrategy::run(const Timer::FunctionInfo& functionInfo, const std::function<std::chrono::milliseconds ()> getElapsedTime){
    int lastIntervalCall{};
    while(not stopVar)
    {
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + checkOfElapsedTimePeriod);
        auto actualInterval = getElapsedTime() / functionInfo.interval;
        bool isTimeElapsed =  lastIntervalCall != actualInterval;
        if(isTimeElapsed){
            functionInfo.funName();
            lastIntervalCall = actualInterval;
        }
    }
}
