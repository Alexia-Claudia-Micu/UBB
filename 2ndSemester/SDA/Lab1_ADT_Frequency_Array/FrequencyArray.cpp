//
// Created by alexi on 3/27/2023.
//
#include "FrequencyArray.h"
#include "FrequencyArrayIterator.h"
#include <exception>

using namespace std;

FrequencyArray::FrequencyArray() {
    this->elements = new TValue[0];
    this->maxElement = NULL_TVALUE_min;
    this->minElement = NULL_TVALUE_max;
    this->rangeElements = 0;
}

FrequencyArray::~FrequencyArray() {
    delete[] this->elements;
}

int FrequencyArray::normalizeIndex(int index) {
    int normalizedIndex;
    normalizedIndex = index + (0 - this->minElement);
    return normalizedIndex;
}

void FrequencyArray::add(TValue newValue){
    if (newValue > this->maxElement || newValue < this->minElement)
        ;//TODO implement sizeDown
    this->elements[this->normalizeIndex(newValue)] ++;
}

void FrequencyArray::remove(TValue value) {
    this->elements[this->normalizeIndex(value)] ++;
    if(this->elements[this->normalizeIndex(value)] == 0)
        if(value == this->minElement || value == this->maxElement)
            ;//TODO implement sizeUp
}

int FrequencyArray::getFrequency(TValue value) const{
    if(value > this->maxElement || value < this->minElement)
        return NULL_TVALUE_min;
    return this->elements[normalizeIndex(value)];
}