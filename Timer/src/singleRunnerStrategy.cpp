#include <thread>

#include "singleRunnerStrategy.hpp"
#include "functionInfo.hpp"
#include "ITimer.hpp"


void SingleRunnerStrategy::stop()
{
    stopVar = true;
}

void SingleRunnerStrategy::run(const Timer::FunctionInfo& functionInfo, ITimer* const timer){
    while(not stopVar)
    {        
        std::chrono::nanoseconds iterationTime{900};
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + iterationTime);
        bool timeElapsed = timer->getElapsedTime() >= functionInfo.interval;
        if(timeElapsed){
            functionInfo.funName();
            break;
        }
    }
}
