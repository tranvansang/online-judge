cmake_minimum_required(VERSION 3.7)
project(online_judge)

set(CMAKE_CXX_STANDARD 11)

add_executable(qtree qtree/qtree.cc)
add_executable(qtree-sol qtree/qtree-sol.cc)
add_executable(qtree-gen qtree/gen.cc)

add_executable(qtree2 qtree2/qtree2.cc)

add_executable(ads ads/main.cpp)

add_executable(assign1 assign1/main.cpp)