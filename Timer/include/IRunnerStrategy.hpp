#pragma once

#include <functional>

namespace Timer{
    struct FunctionInfo;
}
struct ITimer;

class IRunnerStrategy{
public:
    virtual void run(const Timer::FunctionInfo&, const std::function<std::chrono::milliseconds()>) = 0;
    virtual void stop() = 0;    
};
