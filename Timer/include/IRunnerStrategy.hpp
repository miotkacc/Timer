#pragma once

#include <functional>
#include <chrono>


namespace Timer{
    struct FunctionInfo;
}
struct ITimer;

class IRunnerStrategy{
public:
    virtual void run(const std::function<std::chrono::milliseconds()>) = 0;
    virtual void stop() = 0;
    virtual ~IRunnerStrategy() = 0;
};
