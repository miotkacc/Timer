#pragma once

#include <atomic>

#include "IRunnerStrategy.hpp"


class SingleRunnerStrategy: public IRunnerStrategy{
public:
    SingleRunnerStrategy(std::chrono::nanoseconds period=std::chrono::nanoseconds{900});
    void run(const Timer::FunctionInfo&, ITimer* const) override;
    void stop() override;
private:
    std::atomic<bool> stopVar;
    const std::chrono::nanoseconds checkOfElapsedTimePeriod;
};
