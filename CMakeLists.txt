project(mixed_tree)
add_definitions(-std=c++14)
set(sources LeafNode.cpp Node.cpp MixedTree.cpp MixedTree.h)
add_library(bb_tree_lib SHARED ${sources})