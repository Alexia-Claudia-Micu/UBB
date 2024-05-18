//
// Created by alexi on 5/2/2023.
//

#ifndef A7_915_MICU_ALEXIACLAUDIA_EXCEPTIONS_H
#define A7_915_MICU_ALEXIACLAUDIA_EXCEPTIONS_H
#pragma once
#include <string>
#include <exception>
#include <utility>

using namespace std;

class Exceptions : public exception{
protected:
    string message;
public:
    explicit Exceptions(string ExceptionMessage);
    const char* what() const noexcept override;

};

class ExceptionsValidator: public Exceptions{
public:
    explicit ExceptionsValidator(string ExceptionMessage);
};

class ExceptionsRepository: public  Exceptions{
public:
    explicit ExceptionsRepository(string ExceptionMessage);
};

#endif //A7_915_MICU_ALEXIACLAUDIA_EXCEPTIONS_H
