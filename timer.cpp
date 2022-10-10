#include "timer.hpp"
#include <iostream>


void Timer::start(){
        std::cout<<"start timer"<<std::endl;
        startTime = std::chrono::system_clock::now();
}

void Timer::stop(){
        std::cout<<"start timer"<<std::endl;
        stopTime = std::chrono::system_clock::now();
}

std::chrono::milliseconds Timer::get_elapsed_time(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime);
}

void Timer::startTimeInterval(std::chrono::milliseconds exp_time, std::function<void (void)> fun, bool once)
{
    stopInterval = false;
    threads.append(std::make_unique<std::thread>(periodRunner, exp_time, fun));
}

Timer::~Timer()
{
    for(auto& t: threads)
    {
        if(t1->joinable())
        {
            t1->join();
        }
    }
}

void Timer::periodRunner(std::chrono::milliseconds exp_time, std::function<void (void)> fun, bool once)
{
    do
    {
        std::this_thread::sleep_for(exp_time);
        fun();
    }while(not once);
}
