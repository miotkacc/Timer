#pragma once

#include <atomic>

#include "RunnerStrategy.hpp"
#include "FunctionInfo.hpp"



class RecurringRunnerStrategy: public RunnerStrategy{
public:
    void run(const std::function<std::chrono::milliseconds()>) override;
    RecurringRunnerStrategy(const Timer::FunctionInfo&, 
       const std::chrono::nanoseconds period=std::chrono::nanoseconds{400});
};
