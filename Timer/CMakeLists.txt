add_library(Timer src/timer.cpp)
target_include_directories(Timer PUBLIC include)

add_library(RunnerStrategy src/recurringRunnerStrategy.cpp src/singleRunnerStrategy.cpp src/strategyUtils.cpp)

target_include_directories(RunnerStrategy PUBLIC include)

add_library(TimerBuilder src/timerBuilder.cpp src/timer.cpp)
target_link_libraries(TimerBuilder RunnerStrategy)

target_include_directories(TimerBuilder PUBLIC include)
