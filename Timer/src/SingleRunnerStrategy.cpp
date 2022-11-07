#include <thread>

#include "SingleRunnerStrategy.hpp"


SingleRunnerStrategy::SingleRunnerStrategy(const Timer::FunctionInfo& functionInfo, 
    std::chrono::nanoseconds period): RunnerStrategy(functionInfo, period){};

void SingleRunnerStrategy::run(const std::function<std::chrono::milliseconds()> getElapsedTime){
    while(not stopVar)
    {        
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + checkOfElapsedTimePeriod);
        bool isTimeElapsed = getElapsedTime() >= functionInfo.interval;
        if(isTimeElapsed){
            functionInfo.funName();
            break;
        }
    }
}
