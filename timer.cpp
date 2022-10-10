#include "timer.hpp"
#include <iostream>


void Timer::start(){
        std::cout<<"start timer"<<std::endl;
        startTime = std::chrono::steady_clock::now();
        t = std::make_unique<std::thread>(periodRunner, std::ref(functionsCallInfo), startTime, std::ref(stopTimer));
}

void Timer::stop(){
        std::cout<<"stop timer"<<std::endl;
        stopTimer = true;
        if(t and t->joinable())
        { 
            t->join();
        }
}

std::chrono::milliseconds Timer::getElapsedTime(std::chrono::time_point<std::chrono::steady_clock> start)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
};

std::chrono::milliseconds Timer::getElapsedTime() const{
    return getElapsedTime(startTime);
}


void Timer::addFunction(FunctionInfo f)
{
    functionsCallInfo.push_back({f});
}

Timer::~Timer()
{
    stop();
}

void Timer::periodRunner(std::vector<FunctionCallInfo>& functionsCallInfo, std::chrono::time_point<std::chrono::steady_clock> start, std::atomic<bool>& stop)
{
    while(not stop)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds{900});
        for(auto& fun: functionsCallInfo)
        {
            if((fun.info.recurred && getElapsedTime(fun.lastTimeCalled) > fun.info.interval) || not fun.called){

                fun.info.funName();
                fun.called = true;
                fun.lastTimeCalled = std::chrono::steady_clock::now();
            }
            
        }
    }
}
