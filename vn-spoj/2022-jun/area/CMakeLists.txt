cmake_minimum_required(VERSION 3.7)
project(area)

set(CMAKE_CXX_STANDARD 23)

add_executable(main main.cpp)
add_executable(gen gen.cpp)
add_executable(ans ans.cpp)

add_test(NAME main COMMAND ./main <0.inp)
