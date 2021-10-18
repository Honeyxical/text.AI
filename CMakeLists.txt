cmake_minimum_required(VERSION 3.20)
project(text_AI)

set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(SOURCE_FILES main.cpp)
add_executable(text_AI main.cpp md5.cpp md5.h)
