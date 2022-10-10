#include "timer.hpp"
#include <iostream>


void Timer::start(){
        std::cout<<"start timer"<<std::endl;
        startTime = std::chrono::system_clock::now();
        t = std::make_unique<std::thread>(periodRunner, std::ref(functionsInfo), startTime, std::ref(stopTimer));
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
    functionsInfo.push_back(f);
}

Timer::~Timer()
{
}

void Timer::periodRunner(std::vector<FunctionInfo>& functionsInfo, std::chrono::time_point<std::chrono::system_clock> start, std::atomic<bool>& stop)
{
    while(not stop)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds{900});
        for(auto& fun: functionsInfo)
        {
            //std::cout<<get_elapsed_time(start).count()<<"pass"<<std::endl;
            if((fun.recurred && get_elapsed_time(fun.lastTimeCalled) > fun.interval) || not fun.called){

                    fun.funName();
                    fun.called = true;
                    fun.lastTimeCalled = std::chrono::system_clock::now();
            }
            
        }
    }
}
