CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project(Timers)

add_subdirectory(Timer)

add_executable(main main.cpp)

target_link_libraries(main Timer)
