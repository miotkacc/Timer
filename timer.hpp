#include <chrono>

struct Timer{
    void start();
    void stop();
    std::chrono::milliseconds get_elapsed_time();
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> stopTime;
};