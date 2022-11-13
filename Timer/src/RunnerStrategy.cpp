#include <thread>

#include "RunnerStrategy.hpp"
#include "FunctionInfo.hpp"
#include "ITimer.hpp"

RunnerStrategy::RunnerStrategy(const Timer::FunctionInfo& functionInfo, 
const std::chrono::nanoseconds period):
functionInfo{functionInfo}, checkOfElapsedTimePeriod{period}
{
    if(checkOfElapsedTimePeriod <= std::chrono::nanoseconds{0}){
        checkOfElapsedTimePeriod = std::chrono::nanoseconds{400};
    }
}

void RunnerStrategy::stop(){
    stopVar = true;
}

RunnerStrategy::~RunnerStrategy(){
    stop();
}
