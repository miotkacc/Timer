CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project(Timers)

add_subdirectory(Timer)

add_executable(main main.cpp)

target_link_libraries(main Timer)

find_package(GTest REQUIRED)
find_package(GMock REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

add_executable(tests tests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} Timer)