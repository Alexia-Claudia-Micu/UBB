//
// Created by alexi on 3/29/2023.
//

#ifndef A45_915_MICU_ALEXIACLAUDIA_DYNAMICARRAYITERATOR_H
#define A45_915_MICU_ALEXIACLAUDIA_DYNAMICARRAYITERATOR_H
#pragma once
#include "dynamicArray.h"
#include "event.h"
#include <exception>
#include "assert.h"
#include "cstring"
#include "iostream"
using namespace std;

template <typename TElem>
class DynamicArray;

template <typename TElem>
class DynamicArrayIterator{
    friend class DynamicArray<TElem>;

private:
    const DynamicArray<TElem>& dynamicArray;
    int current;

public:

DynamicArrayIterator(const DynamicArray<TElem>& dynamicArray1): dynamicArray(dynamicArray1){
    this->current = 0;
}

void first() {
    this->current = 0;
}

void next() {
    if(this->current > this->dynamicArray.numberOfElements)
        throw exception();
    else
        this->current++;
}

bool valid() const {
    if(this->current < this->dynamicArray.numberOfElements)
        return true;
    return false;
}

TElem  getCurrent() const {
    if(this->current > this->dynamicArray.numberOfElements)
        throw exception();
    else
        return this->dynamicArray.elements[current];
}

void testDynamicArrayIterator()
{
    this->first();
    assert(this->current == 0);
    this->next();
    assert(this->current == 1);
    assert(::strcmp(this->getCurrent().getTitle(), "WizzAir Marathon") == 0);
    while(this->current < 14)
    {
        assert(this->valid() == 1);
        this->next();
    }
    assert(this->valid() == 0);
    cout<<"Test dynamic array iterator successful\n";
}
};

#endif //A45_915_MICU_ALEXIACLAUDIA_DYNAMICARRAYITERATOR_H
