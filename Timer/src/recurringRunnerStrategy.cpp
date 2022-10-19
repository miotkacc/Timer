#include <thread>

#include "recurringRunnerStrategy.hpp"
#include "functionInfo.hpp"
#include "strategyUtils.hpp"


void RecurringRunnerStrategy::stop()
{
    stopVar = true;
}

void RecurringRunnerStrategy::run(const Timer::FunctionInfo& functionInfo){
    auto lastTimeCalled = std::chrono::steady_clock::now();
    while(not stopVar)
    {        
        std::chrono::nanoseconds iterationTime{900};
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + iterationTime);
        bool timeElapsed = getElapsedTime(lastTimeCalled) >= functionInfo.interval;
        if(timeElapsed){
            functionInfo.funName();
            lastTimeCalled = std::chrono::steady_clock::now();
        }
    }
}
