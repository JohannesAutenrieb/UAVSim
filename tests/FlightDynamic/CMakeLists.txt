cmake_minimum_required(VERSION 2.8)
project(enviroment_test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#enable c++ 11
SET(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")

include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)


#add files with new test here
set(test_sources 
	Enviroment_test.cpp
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/tests )
#target_include_directories(enviroment_test PRIVATE ${CMAKE_SOURCE_DIR}/src/Enviroment/)
include_directories(${CMAKE_SOURCE_DIR}/src/Enviroment/)

add_executable(enviroment_test ${test_sources})
target_link_libraries(enviroment_test LibEnviroment gtest_main gtest gmock)


