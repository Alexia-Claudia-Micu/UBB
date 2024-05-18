cmake_minimum_required(VERSION 3.24)
project(a23_915_Micu_AlexiaClaudia C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(a23_915_Micu_AlexiaClaudia
        country.c
        country.h
        repository.h
        repositoy.c ui.c ui.h service.c service.h tests.c)
