add_library(SimpleTimer src/SimpleTimer.cpp)
target_include_directories(SimpleTimer PUBLIC include)

add_library(RunnerStrategy src/RecurringRunnerStrategy.cpp src/SingleRunnerStrategy.cpp 
src/IRunnerStrategy.cpp src/RunnerStrategy.cpp src/CVSingleRunnerStrategy.cpp)

target_include_directories(RunnerStrategy PUBLIC include)

add_library(TimerFactory src/SimpleTimerFactory.cpp src/SimpleTimer.cpp)

target_link_libraries(TimerFactory RunnerStrategy)

target_include_directories(TimerFactory PUBLIC include)
