#include <gmock/gmock.h>
#include "IRunnerStrategy.hpp"

class MockRunnerStrategy : public IRunnerStrategy {
public:
    MOCK_METHOD(void, run, (const std::function<std::chrono::milliseconds()>));
    MOCK_METHOD(void, stop, ());
};
