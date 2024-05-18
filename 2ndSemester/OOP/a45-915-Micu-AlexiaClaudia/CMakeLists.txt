cmake_minimum_required(VERSION 3.24)
project(a45_915_Micu_AlexiaClaudia)

set(CMAKE_CXX_STANDARD 14)

add_executable(a45_915_Micu_AlexiaClaudia
        event.cpp event.h dynamicArray.cpp dynamicArray.h main.cpp dynamicArrayIterator.cpp dynamicArrayIterator.h services.h services.cpp userService.cpp userService.h userInterface.cpp userInterface.h tests.cpp)
