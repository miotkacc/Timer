#pragma once

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <memory>

#include "ITimer.hpp"


namespace Timer{
    struct FunctionInfo
    {
        std::chrono::milliseconds interval;
        std::function<void (void)> funName;
        bool recurred;
    };

    struct FunctionCallInfo
    {
        FunctionInfo info;
        bool called{};
        std::chrono::time_point<std::chrono::steady_clock> lastTimeCalled{};
    };
}
struct SimpleTimer : ISimpleTimer{
    void start() override;
    void stop() override;
    std::chrono::milliseconds getElapsedTime() const override;
    ~SimpleTimer();
    SimpleTimer(Timer::FunctionInfo functionInfo);
    private:
        std::unique_ptr<std::thread> t;
        std::atomic<bool> stopTimer{false};
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        Timer::FunctionCallInfo functionCallInfo;
        std::chrono::milliseconds getElapsedTime(const std::chrono::time_point<std::chrono::steady_clock>&) const ;
        void periodRunner();
};
