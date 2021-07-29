cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(cont_ft my_main.cpp)
add_executable(cont_stl my_main.cpp)
target_compile_definitions(cont_stl PUBLIC USE_STL=1)
