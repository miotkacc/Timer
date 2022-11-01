#include <thread>

#include "RecurringRunnerStrategy.hpp"
#include "FunctionInfo.hpp"
#include "ITimer.hpp"

RecurringRunnerStrategy::RecurringRunnerStrategy(std::chrono::nanoseconds period):
checkOfElapsedTimePeriod{period}
{
    if(checkOfElapsedTimePeriod <= std::chrono::nanoseconds{0}){
        std::__throw_invalid_argument("check of elapsed time period must be greater than 0");
    }
};

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
