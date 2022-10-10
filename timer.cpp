#include "timer.hpp"
#include <iostream>


void Timer::start(){
        std::cout<<"start timer"<<std::endl;
        startTime = std::chrono::system_clock::now();
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

std::chrono::milliseconds Timer::get_elapsed_time(std::chrono::time_point<std::chrono::system_clock> start)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
};

std::chrono::milliseconds Timer::get_elapsed_time(){
    return get_elapsed_time(startTime);
}


void Timer::addFunction(FunctionInfo f)
{
    functionsCallInfo.push_back({f});
}

Timer::~Timer()
{
}

void Timer::periodRunner(std::vector<FunctionCallInfo>& functionsCallInfo, std::chrono::time_point<std::chrono::system_clock> start, std::atomic<bool>& stop)
{
    while(not stop)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds{900});
        for(auto& fun: functionsCallInfo)
        {
            if((fun.info.recurred && get_elapsed_time(fun.lastTimeCalled) > fun.info.interval) || not fun.called){

                    fun.info.funName();
                    fun.called = true;
                    fun.lastTimeCalled = std::chrono::system_clock::now();
            }
            
        }
    }
}
