#pragma once

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <memory>

#include "ITimer.hpp"
#include "functionInfo.hpp"
#include "IRunnerStrategy.hpp"

struct SimpleTimer : ITimer{
    void start() override;
    void stop() override;
    std::chrono::milliseconds getElapsedTime() const override;
    ~SimpleTimer();
    SimpleTimer(Timer::FunctionInfo functionInfo, std::unique_ptr<IRunnerStrategy>);
    private:
        std::unique_ptr<std::thread> t;
        std::unique_ptr<IRunnerStrategy> strategy;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        Timer::FunctionInfo functionInfo;
};
