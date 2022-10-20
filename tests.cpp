#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "SimpleTimer.hpp"
#include "SimpleTimerFactory.hpp"
#include "singleRunnerStrategy.hpp"

using namespace testing;

const std::chrono::seconds timeToCall{1};
const std::chrono::seconds waitTime{3};

TEST(TestTimer, GivenTimerWhenStartIsCalledExpectCallCallback) {
    MockFunction<void(void)> mockCallback;
    EXPECT_CALL(mockCallback, Call()); 
    Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall)};
    SimpleTimer timer(functionInfo, std::make_unique<SingleRunnerStrategy>());
    timer.start();
    std::this_thread::sleep_for(waitTime);
}

TEST(TestTimerBuilder, GivenConstructedTimerWithBuilderWhenStartIsCalledExpectCallCallback) { 
    MockFunction<void(void)> mockCallback;
    EXPECT_CALL(mockCallback, Call());
    SimpleTimerFactory simpleTimerFactory{}; 
    auto timer = simpleTimerFactory.CreateOneShotTimer(mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall));
    timer->start();
    std::this_thread::sleep_for(waitTime);
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}