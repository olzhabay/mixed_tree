cmake_minimum_required(VERSION 3.6)
project(mixed_tree)
add_definitions(-std=c++14)
set(sources src/LeafNode.cpp src/Node.cpp src/MixedTree.cpp src/MixedTree.h)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/lib)
add_library(mixed_tree SHARED ${sources})

