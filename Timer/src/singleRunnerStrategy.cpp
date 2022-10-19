#include <thread>

#include "singleRunnerStrategy.hpp"
#include "functionInfo.hpp"
#include "strategyUtils.hpp"

void SingleRunnerStrategy::stop()
{
    stopVar = true;
}

void SingleRunnerStrategy::run(const Timer::FunctionInfo& functionInfo){
    auto runStartTime = std::chrono::steady_clock::now();
    while(not stopVar)
    {        
        std::chrono::nanoseconds iterationTime{900};
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + iterationTime);
        bool timeElapsed = getElapsedTime(runStartTime) >= functionInfo.interval;
        if(timeElapsed){
            functionInfo.funName();
            break;
        }
    }
}
