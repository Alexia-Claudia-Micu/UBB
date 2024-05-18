//
// Created by alexi on 3/27/2023.
//

#ifndef ADT_FREQUENCY_ARRAY_FREQUENCYARRAYITERATOR_H
#define ADT_FREQUENCY_ARRAY_FREQUENCYARRAYITERATOR_H
#pragma once
#include "FrequencyArray.h"
class FrequencyArrayIterator
{
    friend class FrequencyArray;
private:
    const FrequencyArray& map;
    int currentPosition;
    FrequencyArrayIterator(const FrequencyArray& m);
public:
    void first();
    void next();
    TElem getCurrent();
    bool valid() const;
};


#endif //ADT_FREQUENCY_ARRAY_FREQUENCYARRAYITERATOR_H
