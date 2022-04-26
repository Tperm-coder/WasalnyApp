cmake_minimum_required(VERSION 3.17)
project(untitled3)

set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
add_executable(untitled3 "graphStructure/Node.cpp" "graphStructure/Edge.cpp" "graphStructure/Graph.cpp" main.cpp)
include_directories(c:/SFML/includes)

target_link_libraries(untitled3 sfml-system sfml-window sfml-graphics sfml-audio)