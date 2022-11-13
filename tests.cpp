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
    const Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall)};
};

class TestSimpleTimerFactory : public TestTimer
{
};

class TestRecurringTimerFactory : public TestTimer
{
};

class TestSingleRunnerStrategy : public TestTimer
{
public:
    const Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), timeBetweenTimerInteractions};
};

class TestRecurringRunnerStrategy : public TestTimer
{
public:
    const Timer::FunctionInfo functionInfo{mockCallback.AsStdFunction(), timeBetweenTimerInteractions};
    
    void stopTimerAfterSomeDelayInSeparateThread(RecurringRunnerStrategy& recurringRunnerStrategy){
        thread = std::jthread(&TestRecurringRunnerStrategy::stopTimerAfterSomeDelay, this, std::ref(recurringRunnerStrategy));
    }

    void stopTimerAfterSomeDelay(RecurringRunnerStrategy& recurringRunnerStrategy)
    {
        std::this_thread::sleep_for(2*timeBetweenTimerInteractions);
        
        recurringRunnerStrategy.stop();
    }

private:
    std::jthread thread;
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

TEST_F(TestSimpleTimer, GivenTimerWhenStopIsCalledMomentAfterStartAndThereIsWaitThenExpectGetElapsedTimeReturnMomentTime)
{
    SimpleTimer timer(std::make_unique<SingleRunnerStrategy>(functionInfo));
    
    timer.start();
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    timer.stop();
    std::this_thread::sleep_for(waitTime);
    
    const auto getElapsedTimeCallResult = timer.getElapsedTime();
    const auto minimumExpectedWait = timeBetweenTimerInteractions;
    const auto maximumExpectedWait = 2 * timeBetweenTimerInteractions;
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
    const auto resultOfGetElapsedTime = timer.getElapsedTime();
    EXPECT_EQ(resultOfGetElapsedTime, expectedResultOfGetElapsedTime);
}

TEST_F(TestSimpleTimer, GivenStartedTimerWhenGetElapsedTimeIsCalledThenExpectReturnResonableTime)
{
    SimpleTimer timer(std::make_unique<SingleRunnerStrategy>(functionInfo));
    timer.start();
    
    std::this_thread::sleep_for(timeBetweenTimerInteractions);
    const auto elapsedTime = timer.getElapsedTime();
    
    const auto expectedMinimalElapsedTime = 0.5 * timeBetweenTimerInteractions;
    const auto expectedMaximalElapsedTime = 1.5 * timeBetweenTimerInteractions;
    ASSERT_GE(elapsedTime, expectedMinimalElapsedTime);
    ASSERT_LE(elapsedTime, expectedMaximalElapsedTime);
}

TEST_F(TestSimpleTimerFactory, GivenSimpleTimerFactoryWhenCreateRecurringTimerMethodIsCalledThenExpectReccuringTimerSuccesfullyCreated)
{
    const SimpleTimerFactory simpleTimerFactory{};
    auto recurringTimerPtr = simpleTimerFactory.CreateRecurringTimer([]() {}, waitTime);
    EXPECT_NE(recurringTimerPtr.get(), nullptr);
}

TEST_F(TestSimpleTimerFactory, GivenConstructedTimerWithBuilderWhenStartIsCalledThenExpectCallCallback)
{
    EXPECT_CALL(mockCallback, Call());
    const SimpleTimerFactory simpleTimerFactory{};
    auto timer = simpleTimerFactory.CreateOneShotTimer(mockCallback.AsStdFunction(), std::chrono::duration_cast<std::chrono::milliseconds>(timeToCall));
    timer->start();
    std::this_thread::sleep_for(waitTime);
}

TEST_F(TestRecurringTimerFactory, GivenConstructedTimerWithOneMsWithBuilderWhenStartIsCalledThenExpectCallCallbackMultipleTimes)
{
    const SimpleTimerFactory simpleTimerFactory{};
    int timesCalled{};
    const std::chrono::milliseconds myTimeToCall{1};
    auto functionToCall = [&timesCalled]
    { timesCalled++; };
    auto timer = simpleTimerFactory.CreateRecurringTimer(functionToCall, myTimeToCall);
    timer->start();
    const std::chrono::milliseconds myWaitTime{100};
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

TEST_F(TestSingleRunnerStrategy, GivenZeroCheckTimeWhenRunMethodIsCalledThenExpectTimerRun)
{
    SingleRunnerStrategy singleRunnerStrategy(functionInfo, 0ns);
    EXPECT_CALL(mockCallback, Call());
    EXPECT_CALL(getElapsedTimeMock, Call()).Times(AtLeast(1)).WillRepeatedly(Return(2*timeBetweenTimerInteractions));
    singleRunnerStrategy.run(getElapsedTimeMock.AsStdFunction());
}

TEST_F(TestSingleRunnerStrategy, GivenNegativeCheckTimeWhenRunMethodIsCalledThenExpectTimerRun)
{
    SingleRunnerStrategy singleRunnerStrategy(functionInfo, -1ns);
    EXPECT_CALL(mockCallback, Call());
    EXPECT_CALL(getElapsedTimeMock, Call()).Times(AtLeast(1)).WillRepeatedly(Return(2*timeBetweenTimerInteractions));
    singleRunnerStrategy.run(getElapsedTimeMock.AsStdFunction());
}

TEST_F(TestRecurringRunnerStrategy, GivenZeroCheckTimeWhenRunMethodIsCalledThenExpectTimerRun)
{
    RecurringRunnerStrategy recurringRunnerStrategy(functionInfo, 0ns);
    EXPECT_CALL(mockCallback, Call());
    EXPECT_CALL(getElapsedTimeMock, Call()).Times(AtLeast(1)).WillRepeatedly(Return(3*timeBetweenTimerInteractions));
    stopTimerAfterSomeDelayInSeparateThread(recurringRunnerStrategy);
    
    recurringRunnerStrategy.run(getElapsedTimeMock.AsStdFunction());
}

TEST_F(TestRecurringRunnerStrategy, GivenNegativeCheckTimeWhenRunMethodIsCalledThenExpectTimerRun)
{
    RecurringRunnerStrategy recurringRunnerStrategy(functionInfo, -1ns);
    EXPECT_CALL(mockCallback, Call());
    EXPECT_CALL(getElapsedTimeMock, Call()).Times(AtLeast(1)).WillRepeatedly(Return(3*timeBetweenTimerInteractions));
    stopTimerAfterSomeDelayInSeparateThread(recurringRunnerStrategy);
    
    recurringRunnerStrategy.run(getElapsedTimeMock.AsStdFunction());
}



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}