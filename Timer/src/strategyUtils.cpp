#include "strategyUtils.hpp"

std::chrono::milliseconds getElapsedTime(const std::chrono::time_point<std::chrono::steady_clock>& start)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
}