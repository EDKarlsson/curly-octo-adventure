cmake_minimum_required(VERSION 3.5)
project(red_black_tree_dictionary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RedBlackTree.cpp RedBlackTree.h RBNode.h RBNode.cpp)
add_executable(red_black_tree_dictionary ${SOURCE_FILES})
