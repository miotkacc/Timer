#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <memory>
#include <vector>


struct Timer{
    void start();
    void stop();
    std::chrono::milliseconds get_elapsed_time();
    void startTimeInterval(std::chrono::milliseconds , std::function<void (void)>, bool); 
    ~Timer();

    private:
        std::atomic<bool> stopInterval;
        std::chrono::time_point<std::chrono::system_clock> startTime;
        std::chrono::time_point<std::chrono::system_clock> stopTime;
        std::vector<std::thread> threads;
        static void periodRunner(std::chrono::milliseconds, std::function<void (void)>, bool);
};
