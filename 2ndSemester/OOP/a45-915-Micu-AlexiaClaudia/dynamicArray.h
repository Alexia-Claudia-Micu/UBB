//
// Created by alexi on 3/29/2023.
//

#ifndef A45_915_MICU_ALEXIACLAUDIA_DYNAMICARRAY_H
#define A45_915_MICU_ALEXIACLAUDIA_DYNAMICARRAY_H
#pragma once
#include <utility>
#include "dynamicArrayIterator.h"
#include "event.h"
#include <exception>
#include "assert.h"

using namespace std;

template <typename TElem>
class DynamicArray{

private:
    TElem* elements;
    int numberOfElements;
    int capacity;
    friend class DynamicArrayIterator<TElem>;

    void resize() {
        TElem* newElements = new TElem[this->capacity*2];
        for (int i = 0; i < this->capacity; ++i) {
            newElements[i] = this->elements[i];
        }
        this->capacity *= 2;
        delete[] this->elements;
        this->elements = newElements;
    }
public:

DynamicArray(int capacity) {
    this->numberOfElements = 0;
    this->capacity = capacity;
    this->elements = new TElem[capacity];
}

~DynamicArray(){
    delete[] this->elements;
}

DynamicArray<TElem>& operator=(const DynamicArray &dynamicArray) {
    if(this == &dynamicArray)
        return *this;
    this->capacity = dynamicArray.capacity;
    this->numberOfElements = dynamicArray.numberOfElements;

    delete[] this->elements;
    this->elements = new TElem[this->capacity];
    for(int i = 0; i < this->numberOfElements; i++)
        this->elements[i] = dynamicArray.elements[i];
    return *this;
}

bool add(TElem newElement) {
    if(this->exist(newElement) != false)
        return false;
    if(this->numberOfElements == this->capacity)
        this->resize();
    //this->elements[numberOfElements];
    this->elements[numberOfElements++] = newElement;
    return true;
}

bool remove(TElem element) {
    if (this->exist(element) == false)
        return false;
    for(int i = 0; i < this->numberOfElements; i++)
        if(this->elements[i] == element) {
            this->elements[i] = this->elements[--numberOfElements];
        }
    return true;
}

bool update(int index, TElem newElement) {
    if(index < 0 || index >= this->numberOfElements)
        return false;
    this->elements[index] = newElement;
    return true;
}

int size() const {
    return this->numberOfElements;
}

bool exist(TElem element) {
    for(int i = 0; i < this->numberOfElements; i++)
        if(this->elements[i] == element)
            return true;
    return false;
}

int get(TElem element) {
    if(exist(element) == false)
        return -1;
    for(int i = 0; i < this->numberOfElements; i++)
        if(this->elements[i] == element)
            return i;
    return -1;
}

TElem getElement(int index) const{
    TElem element;
    if(index >= this->numberOfElements || index < 0)
        return element;
    return this->elements[index];
}

bool isEmpty() const {
    return this->numberOfElements == 0;
}

bool isFull() const {
    return this->numberOfElements == this->capacity;
}

DynamicArrayIterator<TElem> iterator() const {
    return DynamicArrayIterator<TElem>(*this);
}

void testDynamicArray()
{
    char title1[] = "CoudFlight", title2[] = "SourCoding", description[] = "Coding Contest", link1[] = "Coding.com", link2[] = "CodingSour.com";
    Event event1, event2;
    event1.setTitle(title1);event1.setDescription(description); event1.setLink(link1); event1.setDateAndTime(2023, 1, 31, 16, 15); event1.setNumberOfPeople(1000);
    event2.setTitle(title2);event2.setDescription(description); event2.setLink(link2); event2.setDateAndTime(2023, 10, 1, 18, 15); event2.setNumberOfPeople(1000);
    DynamicArray dynamicArray = DynamicArray(2);
    assert(dynamicArray.isFull() == false);
    assert(dynamicArray.isEmpty() == true);
    assert(dynamicArray.size() == 0);
    assert(dynamicArray.add(event1) == true);
    assert(dynamicArray.add(event1) == false);
    assert(dynamicArray.exist(event1) == true);
    assert(dynamicArray.size() == 1);
    assert(dynamicArray.isEmpty() == false);
    assert(dynamicArray.exist(event2) == false);
    assert(dynamicArray.add(event2) == true);
    assert(dynamicArray.isFull() == true);
    assert(dynamicArray.get(event2) == 1);
    assert(dynamicArray.get(event1) == 0);
    assert(dynamicArray.remove(event1) == 1);
    assert(dynamicArray.remove(event1) == 0);
    assert(dynamicArray.exist(event1) == 0);
}
};

#endif //A45_915_MICU_ALEXIACLAUDIA_DYNAMICARRAY_H
