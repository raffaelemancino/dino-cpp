cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(ioc)

add_subdirectory(mosasaurus)

add_executable(ioc main.cpp)

target_link_libraries(ioc PUBLIC Mosasaurus)