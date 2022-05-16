cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (Dino)

add_subdirectory(mongoose-cpp)

add_library(Dino app.cpp module.cpp injectable.cpp)

target_link_libraries(Dino PUBLIC mongoose)