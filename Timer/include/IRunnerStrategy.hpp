#pragma once


namespace Timer{
    struct FunctionInfo;
}
struct ITimer;

class IRunnerStrategy{
public:
    virtual void run(const Timer::FunctionInfo&, ITimer* const) = 0;
    virtual void stop() = 0;    
};
