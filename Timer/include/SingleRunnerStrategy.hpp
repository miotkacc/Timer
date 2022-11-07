#pragma once

#include <atomic>

#include "RunnerStrategy.hpp"
#include "FunctionInfo.hpp"


class SingleRunnerStrategy: public RunnerStrategy{
public:
    void run(const std::function<std::chrono::milliseconds()>);
    SingleRunnerStrategy(const Timer::FunctionInfo& functionInfo, 
        std::chrono::nanoseconds period=std::chrono::nanoseconds{400});
};
