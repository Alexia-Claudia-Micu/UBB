cmake_minimum_required(VERSION 3.24)
project(Lab5_ADT_List)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab5_ADT_List
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        IndexedList.cpp
        IndexedList.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h)
