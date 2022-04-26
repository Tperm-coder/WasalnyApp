cmake_minimum_required(VERSION 3.17)
project(untitled3)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled3 "graphStructure/Node.cpp" "graphStructure/Edge.cpp" "graphStructure/Graph.cpp" main.cpp)