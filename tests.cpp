#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "timer.hpp"
using namespace testing;



TEST(TestTimer, GivenTimerWhenStartIsCalledExpectCallCallback) { 
    const std::chrono::seconds timeToCall{1};
    const std::chrono::seconds waitTime{5};
    MockFunction<void(void)> mockCallback;
    EXPECT_CALL(mockCallback, Call()); 
    Timer::FunctionInfo functionInfo{std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall), mockCallback.AsStdFunction(),  false};
    SimpleTimer timer(functionInfo);
    timer.start();
    std::this_thread::sleep_for(waitTime);
}

 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}