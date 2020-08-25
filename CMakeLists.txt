cmake_minimum_required(VERSION 3.15)
project(Project5_Set)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project5_Set
        main.cpp
        Makefile
        Project5.cpp
        Set.h)
