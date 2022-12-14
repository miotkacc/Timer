CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project(Timers)
add_compile_options(-Werror -Wall -Wextra)
SET(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(Timer)

add_executable(main main.cpp)

target_link_libraries(main TimerFactory)


add_executable(tests tests.cpp)
target_link_libraries(tests SimpleTimer TimerFactory GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(tests)
