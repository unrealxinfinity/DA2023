cmake_minimum_required(VERSION 3.23)
project(untitled4)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled4 main.cpp Source/graph.cpp Source/Station.cpp Source/Network.cpp)
target_include_directories(untitled4 PUBLIC Header/)
