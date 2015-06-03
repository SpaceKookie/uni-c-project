cmake_minimum_required(VERSION 3.2)
project(uni_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(uni_project ${SOURCE_FILES} containers.c rbtree.h rbtree.c)