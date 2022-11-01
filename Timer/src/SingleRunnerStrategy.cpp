#include <thread>

#include "SingleRunnerStrategy.hpp"
#include "FunctionInfo.hpp"
#include "ITimer.hpp"

SingleRunnerStrategy::SingleRunnerStrategy(const Timer::FunctionInfo& functionInfo, 
 std::chrono::nanoseconds period):
functionInfo{functionInfo}, checkOfElapsedTimePeriod{period}
{
    if(checkOfElapsedTimePeriod <= std::chrono::nanoseconds{0}){
        std::__throw_invalid_argument("check of elapsed time period must be greater than 0");
    }
}

void SingleRunnerStrategy::stop(){
    stopVar = true;
}

SingleRunnerStrategy::~SingleRunnerStrategy(){
    stop();
}

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
