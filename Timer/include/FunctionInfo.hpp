#pragma once

#include <chrono>
#include <functional>

namespace Timer{
    struct FunctionInfo
    {
        const std::function<void (void)> funName;
        std::chrono::milliseconds interval;
    };
}
