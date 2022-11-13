#pragma once

#include <atomic>

#include "IRunnerStrategy.hpp"
#include "FunctionInfo.hpp"

class RunnerStrategy: public IRunnerStrategy{
public:
    RunnerStrategy(const Timer::FunctionInfo&, const std::chrono::nanoseconds period=std::chrono::nanoseconds{400});
    void stop() override;
    ~RunnerStrategy() override;
protected:
    const Timer::FunctionInfo functionInfo;
    std::atomic<bool> stopVar{};
    std::chrono::nanoseconds checkOfElapsedTimePeriod;
};