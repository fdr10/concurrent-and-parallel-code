cmake_minimum_required(VERSION 3.22)
project(locally-spinning CXX)
add_definitions(-std=c++20)
add_library(
  ${PROJECT_NAME}
    include/locally-spinning/locally-spinning.h
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC include)



