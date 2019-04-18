cmake_minimum_required(VERSION 2.8)
project(enviroment_test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#enable c++ 11
SET(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")


include_directories(${CMAKE_MODULE_PATH}/include ${gmock_SOURCE_DIR}/include)

#add files with new test here
set(test_sources 
	Aerodynamics.cpp)

set(test_header 
	Aerodynamics.hpp)

add_executable(enviroment_test ${test_sources} ${test_header})
target_link_libraries(enviroment_test gtest_main gtest gmock)

