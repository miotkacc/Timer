#pragma once

#include <atomic>

#include "IRunnerStrategy.hpp"
#include "FunctionInfo.hpp"



class RecurringRunnerStrategy: public IRunnerStrategy{
public:
    RecurringRunnerStrategy(const Timer::FunctionInfo&, std::chrono::nanoseconds period=std::chrono::nanoseconds{900});
    ~RecurringRunnerStrategy() override;
    void run(const std::function<std::chrono::milliseconds()>) override;
    void stop() override;
private:
    const Timer::FunctionInfo functionInfo;
    std::atomic<bool> stopVar{};
    const std::chrono::nanoseconds checkOfElapsedTimePeriod;
};
