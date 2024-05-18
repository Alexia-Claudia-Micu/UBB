//
// Created by alexi on 3/27/2023.
//

#ifndef ADT_FREQUENCY_ARRAY_FREQUENCYARRAY_H
#define ADT_FREQUENCY_ARRAY_FREQUENCYARRAY_H
#pragma once
#include <utility>

typedef int TValue;
#define NULL_TVALUE_min -111111
#define NULL_TVALUE_max 111111
class FrequencyArrayIterator;

class FrequencyArray{
    friend class FrequencyArrayIterator;

private:
    TValue *elements;
    int rangeElements;
    int minElement;
    int maxElement;
    int normalizeIndex(int index);

public:
    FrequencyArray();
    void add(TValue v);
    int getFrequency(TValue v) const;
    void remove(TValue v);
    int size() const;
    bool isEmpty() const;
    bool isFull() const;
    FrequencyArrayIterator iterator() const;
    ~FrequencyArray();

};

#endif //ADT_FREQUENCY_ARRAY_FREQUENCYARRAY_H
