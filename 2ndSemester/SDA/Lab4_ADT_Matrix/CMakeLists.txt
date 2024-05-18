cmake_minimum_required(VERSION 3.24)
project(Lab4_ADT_Matrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab4_ADT_Matrix
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Matrix.cpp
        Matrix.h
        ShortTest.cpp
        ShortTest.h)
