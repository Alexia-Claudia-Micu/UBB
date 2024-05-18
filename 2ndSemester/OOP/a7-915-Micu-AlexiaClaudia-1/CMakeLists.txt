cmake_minimum_required(VERSION 3.24)
project(a7_915_Micu_AlexiaClaudia)

set(CMAKE_CXX_STANDARD 14)

include_directories(domain)
include_directories(repository)
include_directories(service)
include_directories(userInterface)
include_directories(Validation)
include_directories(Exceptions)
include_directories(FileRepository)

add_executable(a7_915_Micu_AlexiaClaudia
        userInterface/main.cpp
        domain/event.h
        domain/event.cpp
        service/administratorService.cpp
        service/administratorService.h
        userInterface/userInterface.cpp
        userInterface/userInterface.h
        service/userService.cpp
        service/userService.h
        repository/repository.h
        service/administratorService.h Exceptions/exceptions.cpp Exceptions/exceptions.h Validation/validator.cpp Validation/validator.h FileRepository/fileRepository.cpp FileRepository/fileRepository.h FileRepository/htmlRepository.cpp FileRepository/htmlRepository.h FileRepository/csvRepository.cpp FileRepository/csvRepository.h)
