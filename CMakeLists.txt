cmake_minimum_required(VERSION 3.7)
project(online_judge)

set(CMAKE_CXX_STANDARD 11)

add_executable(qtree qtree/qtree.cc)
add_executable(qtree-sol qtree/qtree-sol.cc)
add_executable(qtree-gen qtree/gen.cc)

add_executable(qtree2 qtree2/qtree2.cc)

add_executable(ads ads/main.cpp)

add_executable(assign1 assign1/main.cpp)

add_executable(baove baove/main.cpp)

add_executable(line/2022/track line/2022/track/main.cpp)

add_executable(qmax qmax/main.cpp)

add_executable(gss gss/main.cpp)

add_executable(match2 match2/main.cpp)

add_executable(floyd floyd/main.cpp)
