cmake_minimum_required(VERSION 3.24)
project(ADT_Frequency_Array)

set(CMAKE_CXX_STANDARD 20)

add_executable(ADT_Frequency_Array main.cpp ExtendedTest.h ShortTest.h FrequencyArray.h ExtendedTest.cpp ShortTest.cpp FrequencyArray.cpp FrequencyArrayIterator.cpp FrequencyArrayIterator.h)
