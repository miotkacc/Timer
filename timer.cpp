#include "timer.hpp"
#include <iostream>

void Timer::start(){
        std::cout<<"start timer"<<std::endl;
        //startTime = ;
        startTime = std::chrono::system_clock::now();
}
void Timer::stop(){
        std::cout<<"start timer"<<std::endl;
        stopTime = std::chrono::system_clock::now();
}

std::chrono::milliseconds Timer::get_elapsed_time(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime);
}