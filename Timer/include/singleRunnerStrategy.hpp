#pragma once

#include "IRunnerStrategy.hpp"


class SingleRunnerStrategy: public IRunnerStrategy{
public:
    void run(Timer::FunctionInfo&) override;
    void stop() override;
};
