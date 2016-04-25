cmake_minimum_required(VERSION 3.5)
project(cs599_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.cpp src/node.cpp src/node.h src/trie.cpp src/trie.h)

add_executable(cs599_project ${SOURCE_FILES})