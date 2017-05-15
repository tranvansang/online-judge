cmake_minimum_required(VERSION 3.7)
project(online_judge)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        qtree/qtree.cc)

add_executable(online_judge ${SOURCE_FILES})