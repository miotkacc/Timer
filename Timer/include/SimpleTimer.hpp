#pragma once

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <memory>

#include "ITimer.hpp"
#include "functionInfo.hpp"
#include "IRunnerStrategy.hpp"


enum struct State{
    notInitialized,
    start,
    stop
};


struct SimpleTimer : ITimer{
    void start() override;
    void stop() override;
    
    std::chrono::milliseconds getElapsedTime() const override;
    ~SimpleTimer();
    SimpleTimer(Timer::FunctionInfo functionInfo, std::unique_ptr<IRunnerStrategy>);
    private:
        State state{};
        std::unique_ptr<std::thread> t;
        std::unique_ptr<IRunnerStrategy> strategy;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        std::chrono::time_point<std::chrono::steady_clock> stopTime;
        Timer::FunctionInfo functionInfo;
};
