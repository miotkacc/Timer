#pragma once

#include "IRunnerStrategy.hpp"

class RecurringRunnerStrategy: public IRunnerStrategy{
public:
    void run(Timer::FunctionInfo&) override;
    void stop() override;
};
