#include <chrono>


struct ISimpleTimer{
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual std::chrono::milliseconds getElapsedTime() const = 0;
};