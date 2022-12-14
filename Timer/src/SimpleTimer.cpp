#include "SimpleTimer.hpp"


SimpleTimer::SimpleTimer(std::unique_ptr<IRunnerStrategy> inStrategy)
: strategy(std::move(inStrategy))
{}

void SimpleTimer::start(){
    if(state==State::start)
    {
        return;
    }
    if(t.joinable())
    { 
        t.join();
    }
    startTime = std::chrono::steady_clock::now();
    t = std::jthread(&IRunnerStrategy::run, strategy.get(), std::bind(&SimpleTimer::getElapsedTime, this));
    state = State::start;
}

void SimpleTimer::stop(){
    if(state==State::stop)
    {
        return;
    }

    strategy->stop();
    
    if(t.joinable())
    { 
        t.join();
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
{}

std::ostream& operator<<(std::ostream& ostream, const ITimer* timer){
    const auto elapsedTime = timer->getElapsedTime();
    ostream<<"Elapsed ";
    ostream<<std::chrono::duration<double, std::ratio<1>>(elapsedTime).count();
    ostream<<" seconds"<<std::endl;
    return ostream;
}