#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <memory>
#include <vector>


struct FunctionInfo
{
    std::chrono::milliseconds interval;
    std::function<void (void)> funName;
    bool recurred;
};

struct FunctionCallInfo
{
    FunctionInfo info;
    bool called{};
    std::chrono::time_point<std::chrono::steady_clock> lastTimeCalled{};
};

struct SimpleTimer{
    void start();
    void stop();
    std::chrono::milliseconds getElapsedTime() const;
    ~SimpleTimer();
    std::unique_ptr<std::thread> t;
    void addFunction(FunctionInfo);
    private:
        std::atomic<bool> stopTimer{false};
        std::chrono::time_point<std::chrono::steady_clock> startTime;
        std::vector<FunctionCallInfo> functionsCallInfo;
        static std::chrono::milliseconds getElapsedTime(std::chrono::time_point<std::chrono::steady_clock>);
        static void periodRunner(std::vector<FunctionCallInfo>& functions, std::chrono::time_point<std::chrono::steady_clock>, std::atomic<bool>& );
};
