#pragma once

#include "IRunnerStrategy.hpp"


class RecurringRunnerStrategy: public IRunnerStrategy{
public:
    void run(const Timer::FunctionInfo&) override;
    void stop() override;
private:
    std::atomic<bool> stopVar;
};
