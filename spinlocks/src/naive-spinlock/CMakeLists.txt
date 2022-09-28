cmake_minimum_required(VERSION 3.22)
project(naive-spinlock CXX)
add_definitions(-std=c++20)
add_library(
  ${PROJECT_NAME}
    include/naive-spinlock/naive-spinlock.h
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC include)



