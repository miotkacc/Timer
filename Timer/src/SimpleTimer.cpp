#include "SimpleTimer.hpp"


void SimpleTimer::start(){
    if(state==State::start)
    {
        return;
    }
    if(t and t->joinable())
    { 
        t->join();
    }
    startTime = std::chrono::steady_clock::now();
    t = std::make_unique<std::thread>(&IRunnerStrategy::run, strategy.get(), std::ref(functionInfo), this);
    state = State::start;
}

void SimpleTimer::stop(){
    if(state==State::stop)
    {
        return;
    }

    strategy->stop();
    
    if(t and t->joinable())
    { 
        t->join();
    }

    stopTime = std::chrono::steady_clock::now();
    state = State::stop;
}

std::chrono::milliseconds SimpleTimer::getElapsedTime() const{
    using ms = std::chrono::milliseconds;
    if(state == State::stop)
    {
        return std::chrono::duration_cast<ms>(stopTime - startTime);
    }
    if(state == State::notInitialized)
    {
        return ms{0}; 
    }
    return std::chrono::duration_cast<ms>(std::chrono::steady_clock::now() - startTime);
}

SimpleTimer::~SimpleTimer()
{
    if(state==State::start)
    {
        stop();
    }
}

SimpleTimer::SimpleTimer(Timer::FunctionInfo functionInfo, std::unique_ptr<IRunnerStrategy> inStrategy)
: functionInfo(functionInfo), strategy(std::move(inStrategy))
{
}
