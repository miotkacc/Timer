#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "SimpleTimer.hpp"
#include "SimpleTimerFactory.hpp"
#include "SingleRunnerStrategy.hpp"
#include "RecurringRunnerStrategy.hpp"

using namespace testing;
using namespace std::chrono_literals;

class TestTimer : public ::testing::Test
{
protected:
    MockFunction<void(void)> mockCallback;
    MockFunction<std::chrono::milliseconds()> getElapsedTimeMock;
    const std::chrono::milliseconds timeToCall{400};
    const std::chrono::milliseconds waitTime{1200};
    const std::chrono::milliseconds timeBetweenTimerInteractions{100};
};

class TestSimpleTimer : public TestTimer
{
public:
    Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall)};
};

class TestSimpleTimerFactory : public TestTimer
{
};

class TestRecurringTimerFactory: public TestTimer
{
};

class TestSingleRunnerStrategy : public TestTimer
{
public:
    Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), timeBetweenTimerInteractions};
};

class TestRecurringRunnerStrategy : public TestTimer
{
public:
    Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), timeBetweenTimerInteractions};
};

TEST_F(TestSimpleTimer, GivenTimerWhenStartIsCalledThenExpectCallCallback)
{
    EXPECT_CALL(mockCallback, Call());
    SimpleTimer timer(std::make_unique<SingleRunnerStrategy>(functionInfo));
    timer.start();
    std::this_thread::sleep_for(waitTime);
}

TEST_F(TestSimpleTimer, GivenTimerWithReccuringRunnerStrategyWhenStartIsCalledThenExpectCallCallbackTwoTimes)
{
    EXPECT_CALL(mockCallback, Call()).Times(2); 
    SimpleTimer timer(std::make_unique<RecurringRunnerStrategy>(functionInfo));
    timer.start();
    std::this_thread::sleep_for(2.5 * timeToCall);
}

TEST_F(TestSimpleTimer, GivenTimerWhenStopIsCalledMomentAfterStopAndThereIsWaitThenExpectGetElapsedTimeReturnMomentTime)
{
    SimpleTimer timer(std::make_unique<SingleRunnerStrategy>(functionInfo));
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.stop();
    std::this_thread::sleep_for(waitTime);
    auto getElapsedTimeCallResult = timer.getElapsedTime();
    auto minimumExpectedWait = timeBetweenTimerInteractions;
    auto maximumExpectedWait = 2 * timeBetweenTimerInteractions;
    ASSERT_GE(getElapsedTimeCallResult, minimumExpectedWait);
    ASSERT_LE(getElapsedTimeCallResult, maximumExpectedWait);
}

TEST_F(TestSimpleTimer, GivenTimerWhenStartIsCalledTwoTimesThenExpectNoCrash)
{
    SimpleTimer timer(std::make_unique<SingleRunnerStrategy>(functionInfo));
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.start();
}

TEST_F(TestSimpleTimer, GivenTimerWhenStopIsCalledTwoTimesThenExpectNoCrash)
{
    SimpleTimer timer(std::make_unique<SingleRunnerStrategy>(functionInfo));
    timer.stop();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.stop();
}

TEST_F(TestSimpleTimer, GivenTimerWhenTimerIsStartedAndStoppedTwoTimesThenExpectNoCrash)
{
    SimpleTimer timer(std::make_unique<SingleRunnerStrategy>(functionInfo));
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.stop();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.stop();
}

TEST_F(TestSimpleTimer, GivenNotInitializedTimerWhengetElapsedTimeIsCalledThenExpectReturnZeroMs)
{
    std::chrono::milliseconds expectedResultOfGetElapsedTime{};
    SimpleTimer timer(std::make_unique<SingleRunnerStrategy>(functionInfo));
    auto resultOfGetElapsedTime = timer.getElapsedTime();
    EXPECT_EQ(resultOfGetElapsedTime, expectedResultOfGetElapsedTime);
}

TEST_F(TestSimpleTimer, GivenStartedTimerWhenGetElapsedTimeIsCalledThenExpectReturnResonableTime)
{
    SimpleTimer timer(std::make_unique<SingleRunnerStrategy>(functionInfo));
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    auto elapsedTime = timer.getElapsedTime();
    auto expectedMinimalElapsedTime = 0.5 * timeBetweenTimerInteractions;
    auto expectedMaximalElapsedTime = 1.5 * timeBetweenTimerInteractions;
    ASSERT_GE(elapsedTime, expectedMinimalElapsedTime);
    ASSERT_LE(elapsedTime, expectedMaximalElapsedTime);
}

TEST_F(TestSimpleTimerFactory, GivenSimpleTimerFactoryWhenCreateRecurringTimerMethodIsCalledThenExpectReccuringTimerSuccesfullyCreated)
{
    SimpleTimerFactory simpleTimerFactory{};
    auto recurringTimerPtr = simpleTimerFactory.CreateRecurringTimer([]() {}, waitTime);
    EXPECT_NE(recurringTimerPtr.get(), nullptr);
}

TEST_F(TestSimpleTimerFactory, GivenConstructedTimerWithBuilderWhenStartIsCalledThenExpectCallCallback)
{
    EXPECT_CALL(mockCallback, Call());
    SimpleTimerFactory simpleTimerFactory{};
    auto timer = simpleTimerFactory.CreateOneShotTimer(mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall));
    timer->start();
    std::this_thread::sleep_for(waitTime);
}

TEST_F(TestRecurringTimerFactory, GivenConstructedTimerWithOneMsWithBuilderWhenStartIsCalledThenExpectCallCallbackMultipleTimes)
{
    SimpleTimerFactory simpleTimerFactory{};
    int timesCalled{};
    std::chrono::milliseconds myTimeToCall{1};
    auto functionToCall = [&timesCalled]{timesCalled++;};
    auto timer = simpleTimerFactory.CreateRecurringTimer(functionToCall, myTimeToCall);
    timer->start();
    std::chrono::milliseconds myWaitTime{100};
    std::this_thread::sleep_for(myWaitTime);
    timer->stop();
    EXPECT_GE(timesCalled, 40);
    EXPECT_LE(timesCalled, 120);
}

TEST_F(TestSingleRunnerStrategy, GivenSimpleRunnerStrategyWhenRunIsCalledThenExpectMethodBeCalled)
{
    SingleRunnerStrategy singleRunnerStrategy{functionInfo};
    EXPECT_CALL(getElapsedTimeMock, Call()).WillOnce(Return(2 * timeBetweenTimerInteractions));
    EXPECT_CALL(mockCallback, Call());
    singleRunnerStrategy.run(getElapsedTimeMock.AsStdFunction());
    std::this_thread::sleep_for(2 * timeBetweenTimerInteractions);
}

TEST_F(TestSingleRunnerStrategy, GivenZeroCheckTimeWhenConstructorIsCalledThenExpectThrow)
{
    EXPECT_THROW(SingleRunnerStrategy(functionInfo, 0ns), std::invalid_argument);
}

TEST_F(TestSingleRunnerStrategy, GivenNegativeCheckTimeWhenConstructorIsCalledThenExpectThrow)
{
    EXPECT_THROW(SingleRunnerStrategy(functionInfo, -1ns), std::invalid_argument);
}

TEST_F(TestRecurringRunnerStrategy, GivenZeroCheckTimeWhenConstructorIsCalledThenExpectThrow)
{
    EXPECT_THROW(RecurringRunnerStrategy(functionInfo, 0ns), std::invalid_argument);
}

TEST_F(TestRecurringRunnerStrategy, GivenNegativeCheckTimeWhenConstructorIsCalledThenExpectThrow)
{
    EXPECT_THROW(RecurringRunnerStrategy(functionInfo, -1ns), std::invalid_argument);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}