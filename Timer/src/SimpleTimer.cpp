#include <iostream>

#include "SimpleTimer.hpp"


void SimpleTimer::start(){
    if(t and t->joinable())
    { 
        t->join();
    }
    startTime = std::chrono::steady_clock::now();
    t = std::make_unique<std::thread>(&IRunnerStrategy::run, strategy.get(), std::ref(functionInfo));
}

void SimpleTimer::stop(){
    strategy->stop();
    if(t and t->joinable())
    { 
        t->join();
    }
}

std::chrono::milliseconds SimpleTimer::getElapsedTime() const{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime);
}

SimpleTimer::~SimpleTimer()
{
    stop();
}

SimpleTimer::SimpleTimer(Timer::FunctionInfo functionInfo, std::unique_ptr<IRunnerStrategy> inStrategy)
: functionInfo(functionInfo), strategy(std::move(inStrategy))
{
}
