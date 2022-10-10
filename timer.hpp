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
    std::chrono::time_point<std::chrono::system_clock> lastTimeCalled{};
};

struct Timer{
    void start();
    void stop();
    std::chrono::milliseconds get_elapsed_time();
    ~Timer();
    std::unique_ptr<std::thread> t;
    void addFunction(FunctionInfo);
    private:
        std::atomic<bool> stopTimer{false};
        std::chrono::time_point<std::chrono::system_clock> startTime;
        std::vector<FunctionCallInfo> functionsCallInfo;
        static std::chrono::milliseconds get_elapsed_time(std::chrono::time_point<std::chrono::system_clock>);
        static void periodRunner(std::vector<FunctionCallInfo>& functions, std::chrono::time_point<std::chrono::system_clock>, std::atomic<bool>& );
};
