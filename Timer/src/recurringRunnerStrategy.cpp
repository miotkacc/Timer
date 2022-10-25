#include <thread>

#include "recurringRunnerStrategy.hpp"
#include "functionInfo.hpp"
#include "ITimer.hpp"

void RecurringRunnerStrategy::stop()
{
    stopVar = true;
}

void RecurringRunnerStrategy::run(const Timer::FunctionInfo& functionInfo, ITimer* const timer){
    int lastIntervalCall{};
    while(not stopVar)
    {        
        std::chrono::nanoseconds iterationTime{900};
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + iterationTime);
        auto actualInterval = timer->getElapsedTime() / functionInfo.interval;
        bool timeElapsed =  lastIntervalCall != actualInterval;
        if(timeElapsed){
            functionInfo.funName();
            lastIntervalCall = actualInterval;
        }
    }
}
