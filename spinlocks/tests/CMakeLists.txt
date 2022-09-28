cmake_minimum_required(VERSION 3.22)
project(tests CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
include(FetchContent)
#GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.12.0 
)

#GoogleBenchmark
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.7.0
) # need master for benchmark::benchmark
# Make fetched content available
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest googlebenchmark)
enable_testing()
add_executable(${PROJECT_NAME}-naive-spinlock tests-naive-spinlock.cpp)
target_link_libraries(${PROJECT_NAME}-naive-spinlock PRIVATE GTest::gtest_main benchmark::benchmark naive-spinlock)

add_executable(${PROJECT_NAME}-locally-spinning tests-locally-spinning.cpp)
target_link_libraries(${PROJECT_NAME}-locally-spinning PRIVATE GTest::gtest_main benchmark::benchmark locally-spinning)



include(GoogleTest)
#gtest_discover_tests(${PROJECT_NAME}-locally-spinning)




