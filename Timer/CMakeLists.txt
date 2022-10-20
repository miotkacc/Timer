add_library(SimpleTimer src/SimpleTimer.cpp)
target_include_directories(SimpleTimer PUBLIC include)

add_library(RunnerStrategy src/recurringRunnerStrategy.cpp src/singleRunnerStrategy.cpp src/strategyUtils.cpp)

target_include_directories(RunnerStrategy PUBLIC include)

add_library(TimerFactory src/SimpleTimerFactory.cpp src/SimpleTimer.cpp)
target_link_libraries(TimerFactory RunnerStrategy)

target_include_directories(TimerFactory PUBLIC include)
