#include <chrono>
#include <functional>

namespace Timer{
    struct FunctionInfo
    {
        std::function<void (void)> funName;
        std::chrono::milliseconds interval;
        std::chrono::time_point<std::chrono::steady_clock> lastTimeCalled{};
    };
}