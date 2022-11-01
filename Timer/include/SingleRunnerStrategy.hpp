#pragma once

#include <atomic>

#include "IRunnerStrategy.hpp"
#include "FunctionInfo.hpp"


class SingleRunnerStrategy: public IRunnerStrategy{
public:
    SingleRunnerStrategy(const Timer::FunctionInfo&, std::chrono::nanoseconds period=std::chrono::nanoseconds{900});
    ~SingleRunnerStrategy() override;
    void run(const std::function<std::chrono::milliseconds()>) override;
    void stop() override;
private:
    const Timer::FunctionInfo functionInfo;
    std::atomic<bool> stopVar{};
    const std::chrono::nanoseconds checkOfElapsedTimePeriod;
};
