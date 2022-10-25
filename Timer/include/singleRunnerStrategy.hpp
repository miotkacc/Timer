#pragma once

#include <atomic>

#include "IRunnerStrategy.hpp"


class SingleRunnerStrategy: public IRunnerStrategy{
public:
    void run(const Timer::FunctionInfo&, ITimer* const) override;
    void stop() override;
private:
    std::atomic<bool> stopVar;
};
