#pragma once

#include <iostream>

#include "SimpleTimer.hpp"

template <typename T>
void SimpleTimer<T>::start(){
    if(t and t->joinable())
    { 
        t->join();
    }
    startTime = std::chrono::steady_clock::now();
    t = std::make_unique<std::thread>(&IRunnerStrategy::run, strategy.get(), std::ref(functionInfo));
}

template <typename T>
void SimpleTimer<T>::stop(){
    strategy->stop();
    if(t and t->joinable())
    { 
        t->join();
    }
}

template <typename T>
T SimpleTimer<T>::getElapsedTime() const{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime);
}

template <typename T>
SimpleTimer<T>::~SimpleTimer()
{
    stop();
}

template <typename T>
SimpleTimer<T>::SimpleTimer(Timer::FunctionInfo functionInfo, std::unique_ptr<IRunnerStrategy> inStrategy)
: functionInfo(functionInfo), strategy(std::move(inStrategy))
{
}
