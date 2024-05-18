cmake_minimum_required(VERSION 3.24)
project(Lab2_ADT_Sorted_MultiMap)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab2_ADT_Sorted_MultiMap
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h)
