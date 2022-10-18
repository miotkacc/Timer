#include <iostream>

#include "timer.hpp"


void SimpleTimer::start(){
    if(t and t->joinable())
    { 
        t->join();
    }
    startTime = std::chrono::steady_clock::now();
    t = std::make_unique<std::thread>(&SimpleTimer::periodRunner, this);
}

void SimpleTimer::stop(){
    stopTimer = true;
    if(t and t->joinable())
    { 
        t->join();
    }
}

std::chrono::milliseconds SimpleTimer::getElapsedTime(const std::chrono::time_point<std::chrono::steady_clock>& start) const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
}

std::chrono::milliseconds SimpleTimer::getElapsedTime() const{
    return getElapsedTime(startTime);
}

SimpleTimer::~SimpleTimer()
{
    stop();
}

SimpleTimer::SimpleTimer(Timer::FunctionInfo functionInfo, std::unique_ptr<IRunnerStrategy> inStrategy)
: strategy(std::move(inStrategy)), functionInfo{functionInfo}
{
}

void SimpleTimer::periodRunner()
{
    functionInfo.lastTimeCalled = std::chrono::steady_clock::now();
    while(not stopTimer)
    {        
        std::chrono::nanoseconds iterationTime{900};
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + iterationTime);
        bool timeElapsed = getElapsedTime(functionInfo.lastTimeCalled) >= functionCallInfo.info.interval;
        bool canBeCalled = functionCallInfo.info.recurred || not functionCallInfo.called;
        if(timeElapsed && canBeCalled){
            functionCallInfo.info.funName();
            functionCallInfo.called = true;
            functionCallInfo.lastTimeCalled = std::chrono::steady_clock::now();
        }
    }
}
