cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (Mosasaurus)

add_subdirectory(mongoose-cpp)

add_library(Mosasaurus app.cpp module.cpp models.cpp)

target_link_libraries(Mosasaurus PUBLIC mongoose)