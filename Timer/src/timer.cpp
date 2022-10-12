#include <iostream>

#include "timer.hpp"


void SimpleTimer::start(){
        startTime = std::chrono::steady_clock::now();
        t = std::make_unique<std::thread>(periodRunner, std::ref(functionCallInfo), std::ref(stopTimer));
}

void SimpleTimer::stop(){
        stopTimer = true;
        if(t and t->joinable())
        { 
            t->join();
        }
}

std::chrono::milliseconds SimpleTimer::getElapsedTime(const std::chrono::time_point<std::chrono::steady_clock>& start)
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

SimpleTimer::SimpleTimer(FunctionInfo functionInfo)
{
    functionCallInfo = FunctionCallInfo{functionInfo};
}

void SimpleTimer::periodRunner(FunctionCallInfo& fun, std::atomic<bool>& stop)
{
    fun.lastTimeCalled = std::chrono::steady_clock::now();
    while(not stop)
    {        
        std::this_thread::sleep_for(std::chrono::nanoseconds{900});
        if(getElapsedTime(fun.lastTimeCalled) >= fun.info.interval && (fun.info.recurred || not fun.called)){
            std::thread t(fun.info.funName);
            t.detach();
            fun.called = true;
            fun.lastTimeCalled = std::chrono::steady_clock::now();
        }
    }
}
