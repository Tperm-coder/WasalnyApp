cmake_minimum_required(VERSION 3.20)
project(untitled3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

set(SOURCE_FILES main.cpp)
add_executable(untitled3 "graphStructure/Node.cpp" "graphStructure/Edge.cpp" "graphStructure/Graph.cpp" main.cpp graphStructure/Dijkstra.cpp graphStructure/Dijkstra.h)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(untitled3 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
