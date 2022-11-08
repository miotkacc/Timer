#pragma once

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <memory>
#include <iostream>

#include "ITimer.hpp"
#include "FunctionInfo.hpp"
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
    SimpleTimer(std::unique_ptr<IRunnerStrategy>);
    friend std::ostream& operator<<(std::ostream& ostream, const ITimer* timer);
    private:
        State state{};
        std::jthread t;
        std::unique_ptr<IRunnerStrategy> strategy;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        std::chrono::time_point<std::chrono::steady_clock> stopTime;
};
