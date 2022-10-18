add_library(Timer src/timer.cpp)
target_include_directories(Timer PUBLIC include)

add_library(TimerBuilder src/timerBuilder.cpp src/timer.cpp)



target_include_directories(TimerBuilder PUBLIC include)

add_library(RunnerStrategy src/recurringRunnerStrategy.cpp src/singleRunnerStrategy.cpp)

target_include_directories(RunnerStrategy PUBLIC include)
