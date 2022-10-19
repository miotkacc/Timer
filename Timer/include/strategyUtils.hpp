#pragma once

#include <chrono>

std::chrono::milliseconds getElapsedTime(const std::chrono::time_point<std::chrono::steady_clock>&);