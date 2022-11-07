#pragma once

#include <atomic>

#include "IRunnerStrategy.hpp"
#include "FunctionInfo.hpp"

class RunnerStrategy: public IRunnerStrategy{
public:
    RunnerStrategy(const Timer::FunctionInfo&, std::chrono::nanoseconds period=std::chrono::nanoseconds{400});
    void stop() override;
    ~RunnerStrategy() override;
protected:
    const Timer::FunctionInfo functionInfo;
    std::atomic<bool> stopVar{};
    const std::chrono::nanoseconds checkOfElapsedTimePeriod;
};