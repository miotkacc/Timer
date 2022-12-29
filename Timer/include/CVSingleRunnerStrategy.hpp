#pragma once

#include "IRunnerStrategy.hpp"
#include <mutex>
#include <condition_variable>
#include "FunctionInfo.hpp"


struct CVSingleRunnerStrategy: public IRunnerStrategy{
    void run(const std::function<std::chrono::milliseconds()>) override;
    void stop() override;
    ~CVSingleRunnerStrategy();
    CVSingleRunnerStrategy(const Timer::FunctionInfo& functionInfo);
    const Timer::FunctionInfo functionInfo;
    std::mutex myMutex;
    std::condition_variable cv;
};