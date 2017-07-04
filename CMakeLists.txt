project(mixed_tree)
add_definitions(-std=c++14)
set(sources LeafNode.cpp Node.cpp TreapTree.cpp TreapTree.h)
add_library(bb_tree_lib SHARED ${sources})