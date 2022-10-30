#include <thread>

#include "SingleRunnerStrategy.hpp"
#include "FunctionInfo.hpp"
#include "ITimer.hpp"

SingleRunnerStrategy::SingleRunnerStrategy(std::chrono::nanoseconds period):
checkOfElapsedTimePeriod{period}
{};

void SingleRunnerStrategy::stop()
{
    stopVar = true;
}

SingleRunnerStrategy::~SingleRunnerStrategy()
{
    stop();
}

void SingleRunnerStrategy::run(const Timer::FunctionInfo& functionInfo, const std::function<std::chrono::milliseconds()> getElapsedTime){
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
