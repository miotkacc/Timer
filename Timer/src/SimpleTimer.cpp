#include "SimpleTimer.hpp"


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
    t = std::jthread(&IRunnerStrategy::run, strategy.get(), std::ref(functionInfo), std::bind(&SimpleTimer::getElapsedTime, this));
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
{
}

SimpleTimer::SimpleTimer(Timer::FunctionInfo functionInfo, std::unique_ptr<IRunnerStrategy> inStrategy)
: functionInfo(functionInfo), strategy(std::move(inStrategy))
{
}

std::ostream& operator<<(std::ostream& ostream, ITimer* timer){
    auto elapsedTime = timer->getElapsedTime();
    ostream<<"Elapsed ";
    ostream<<std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count();
    ostream<<".";
    ostream<<elapsedTime.count()%1000;
    ostream<<" seconds"<<std::endl;
    return ostream;
}