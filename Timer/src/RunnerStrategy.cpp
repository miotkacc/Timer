#include <thread>

#include "RunnerStrategy.hpp"
#include "FunctionInfo.hpp"
#include "ITimer.hpp"

RunnerStrategy::RunnerStrategy(const Timer::FunctionInfo& functionInfo, 
const std::chrono::nanoseconds period):
functionInfo{functionInfo}, checkOfElapsedTimePeriod{period}
{
    if(checkOfElapsedTimePeriod <= std::chrono::nanoseconds{0}){
        std::__throw_invalid_argument("check of elapsed time period must be greater than 0");
    }
}

void RunnerStrategy::stop(){
    stopVar = true;
}

RunnerStrategy::~RunnerStrategy(){
    stop();
}
