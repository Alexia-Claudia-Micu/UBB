//
// Created by alexi on 5/2/2023.
//

#include "exceptions.h"
#include <utility>

Exceptions::Exceptions(string ExceptionMessage) {
    this->message = move(ExceptionMessage);
}

const char *Exceptions::what() const noexcept {
    return this->message.c_str();
}

ExceptionsValidator::ExceptionsValidator(string ExceptionMessage) : Exceptions(move(ExceptionMessage)){

}

ExceptionsRepository::ExceptionsRepository(string ExceptionMessage) : Exceptions(move(ExceptionMessage)){

}