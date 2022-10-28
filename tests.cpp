#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "SimpleTimer.hpp"
#include "SimpleTimerFactory.hpp"
#include "singleRunnerStrategy.hpp"

using namespace testing;

const std::chrono::seconds timeToCall{1};
const std::chrono::seconds waitTime{3};

std::chrono::milliseconds timeBetweenTimerInteractions{100};

class TestTimer: public ::testing::Test{
    protected:
        MockFunction<void(void)> mockCallback;
};

class TestSimpleTimer: public TestTimer
{
};

class TestSimpleTimerFactory: public TestTimer
{
};

TEST_F(TestSimpleTimer, GivenTimerWhenStartIsCalledExpectCallCallback) {
    EXPECT_CALL(mockCallback, Call()); 
    Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall)};
    SimpleTimer timer(functionInfo, std::make_unique<SingleRunnerStrategy>());
    timer.start();
    std::this_thread::sleep_for(waitTime);
}

TEST_F(TestSimpleTimer, GivenTimerWhenStopIsCalledMomentAfterStopAndThereIsWaitExpectGetElapsedTimeReturnMomentTime) {
    Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall)};
    SimpleTimer timer(functionInfo, std::make_unique<SingleRunnerStrategy>());
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.stop();
    std::this_thread::sleep_for(waitTime);
    auto getElapsedTimeCallResult = timer.getElapsedTime();
    auto minimumExpectedWait = timeBetweenTimerInteractions;
    auto maximumExpectedWait = 2*timeBetweenTimerInteractions;
    ASSERT_GE(getElapsedTimeCallResult, minimumExpectedWait);
    ASSERT_LE(getElapsedTimeCallResult, maximumExpectedWait);
}

TEST_F(TestSimpleTimer, GivenTimerWhenStartIsCalledTwoTimesExpectNoCrash) {
    Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall)};
    SimpleTimer timer(functionInfo, std::make_unique<SingleRunnerStrategy>());
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.start();
}

TEST_F(TestSimpleTimer, GivenTimerWhenTimerIsStartedAndStoppedTwoTimesExpectNoCrash) {
    Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall)};
    SimpleTimer timer(functionInfo, std::make_unique<SingleRunnerStrategy>());
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.stop();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.stop();
}

TEST_F(TestSimpleTimer, GivenStartedTimerWhenGetElapsedTimeIsCalledExpectReturnResonableTime) {
    Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall)};
    SimpleTimer timer(functionInfo, std::make_unique<SingleRunnerStrategy>());
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    auto elapsedTime = timer.getElapsedTime();
    auto expectedMinimalElapsedTime = 0.5*timeBetweenTimerInteractions;
    auto expectedMaximalElapsedTime = 1.5*timeBetweenTimerInteractions;
    ASSERT_GE(elapsedTime, expectedMinimalElapsedTime);
    ASSERT_LE(elapsedTime, expectedMaximalElapsedTime);
}

TEST_F(TestSimpleTimerFactory, GivenConstructedTimerWithBuilderWhenStartIsCalledExpectCallCallback) { 
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