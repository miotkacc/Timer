#pragma once

#include <atomic>

#include "IRunnerStrategy.hpp"


class RecurringRunnerStrategy: public IRunnerStrategy{
public:
    RecurringRunnerStrategy(std::chrono::nanoseconds=std::chrono::nanoseconds{900});
    ~RecurringRunnerStrategy();
    void run(const Timer::FunctionInfo&, const std::function<std::chrono::milliseconds()> getElapsedTime) override;
    void stop() override;
private:
    std::atomic<bool> stopVar{};
    const std::chrono::nanoseconds checkOfElapsedTimePeriod;
};
