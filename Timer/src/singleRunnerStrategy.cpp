#include <thread>

#include "singleRunnerStrategy.hpp"
#include "functionInfo.hpp"
#include "ITimer.hpp"

SingleRunnerStrategy::SingleRunnerStrategy(std::chrono::nanoseconds period):
checkOfElapsedTimePeriod{period}
{};

void SingleRunnerStrategy::stop()
{
    stopVar = true;
}

void SingleRunnerStrategy::run(const Timer::FunctionInfo& functionInfo, ITimer* const timer){
    while(not stopVar)
    {        
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + checkOfElapsedTimePeriod);
        bool isTimeElapsed = timer->getElapsedTime() >= functionInfo.interval;
        if(isTimeElapsed){
            functionInfo.funName();
            break;
        }
    }
}
