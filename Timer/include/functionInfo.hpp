#pragma once

#include <chrono>
#include <functional>

namespace Timer{
    struct FunctionInfo
    {
        std::function<void (void)> funName;
        std::chrono::milliseconds interval;
    };
}