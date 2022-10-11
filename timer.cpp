#include "timer.hpp"
#include <iostream>


void SimpleTimer::start(){
        std::cout<<"start timer"<<std::endl;
        startTime = std::chrono::steady_clock::now();
        t = std::make_unique<std::thread>(periodRunner, std::ref(functionCallInfo), startTime, std::ref(stopTimer));
}

void SimpleTimer::stop(){
        std::cout<<"stop timer"<<std::endl;
        stopTimer = true;
        if(t and t->joinable())
        { 
            t->join();
        }
}

std::chrono::milliseconds SimpleTimer::getElapsedTime(std::chrono::time_point<std::chrono::steady_clock> start)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
};

std::chrono::milliseconds SimpleTimer::getElapsedTime() const{
    return getElapsedTime(startTime);
}



SimpleTimer::~SimpleTimer()
{
    stop();
}

SimpleTimer::SimpleTimer(FunctionInfo functionInfo)
{
    functionCallInfo = FunctionCallInfo{functionInfo};
}

void SimpleTimer::periodRunner(FunctionCallInfo& fun, std::chrono::time_point<std::chrono::steady_clock> start, std::atomic<bool>& stop)
{
    fun.lastTimeCalled = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::nanoseconds{900});
    while(not stop)
    {        
        if(getElapsedTime(fun.lastTimeCalled) > fun.info.interval && (fun.info.recurred || not fun.called)){

            fun.info.funName(); //to do -> start separate thread here
            fun.called = true;
            fun.lastTimeCalled = std::chrono::steady_clock::now();
        }
    }
}
