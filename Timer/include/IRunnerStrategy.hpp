#pragma once

#include <atomic>

namespace Timer{
    struct FunctionInfo;
}

class IRunnerStrategy{
public:
    virtual void run(Timer::FunctionInfo&) = 0;
    virtual void stop() = 0;
private:
     const std::atomic<bool> stopVar;
};