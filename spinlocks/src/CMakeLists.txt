cmake_minimum_required(VERSION 3.22)
project(spinlock)


include(FetchContent)

#FetchContent_Declare(
#  jsoncpp 
#  GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git   
#  GIT_TAG 1.9.5 
#)
#
#FetchContent_Declare(
#  fmt  
#  GIT_REPOSITORY https://github.com/fmtlib/fmt.git 
#  GIT_TAG 9.1.0 
#)
#
#FetchContent_MakeAvailable(
#	fmt 
#	jsoncpp
#)



add_subdirectory(naive-spinlock)
add_subdirectory(locally-spinning)
add_executable(${PROJECT_NAME}-1 app1/main.cpp)
#set_target_properties(${PROJECT_NAME}-1 PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(
  ${PROJECT_NAME}-1 
	naive-spinlock 
  locally-spinning
)


