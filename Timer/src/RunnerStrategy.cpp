#include <thread>

#include "RunnerStrategy.hpp"
#include "FunctionInfo.hpp"
#include "ITimer.hpp"

RunnerStrategy::RunnerStrategy(const Timer::FunctionInfo& functionInfo, 
const std::chrono::nanoseconds period):
functionInfo{functionInfo}, checkOfElapsedTimePeriod{period}
{
    if(checkOfElapsedTimePeriod <= std::chrono::nanoseconds{0}){
        checkOfElapsedTimePeriod = defaultCheckOfElapsedTimePeriod;
    }
}

void RunnerStrategy::stop(){
    stopVar = true;
}

RunnerStrategy::~RunnerStrategy(){
    stop();
}
