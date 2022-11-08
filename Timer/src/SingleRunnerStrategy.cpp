#include <thread>

#include "SingleRunnerStrategy.hpp"


SingleRunnerStrategy::SingleRunnerStrategy(const Timer::FunctionInfo& functionInfo, 
   const std::chrono::nanoseconds period): RunnerStrategy(functionInfo, period){};

void SingleRunnerStrategy::run(const std::function<std::chrono::milliseconds()> getElapsedTime){
    while(not stopVar)
    {        
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + checkOfElapsedTimePeriod);
        const bool isTimeElapsed = getElapsedTime() >= functionInfo.interval;
        if(isTimeElapsed){
            functionInfo.funName();
            break;
        }
    }
}
