#pragma once

#include <chrono>


struct ITimer{
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual std::chrono::milliseconds getElapsedTime() const = 0;
    friend std::ostream& operator<<(std::ostream&, const ITimer*);
};
