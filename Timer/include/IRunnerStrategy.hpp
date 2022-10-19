#pragma once

#include <atomic>


namespace Timer{
    struct FunctionInfo;
}

class IRunnerStrategy{
public:
    virtual void run(const Timer::FunctionInfo&) = 0;
    virtual void stop() = 0;    
};
