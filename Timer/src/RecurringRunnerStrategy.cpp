#include <thread>

#include "RecurringRunnerStrategy.hpp"


RecurringRunnerStrategy::RecurringRunnerStrategy(const Timer::FunctionInfo& functionInfo, 
    std::chrono::nanoseconds period): RunnerStrategy(functionInfo, period){};

void RecurringRunnerStrategy::run(const std::function<std::chrono::milliseconds()> getElapsedTime){
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
