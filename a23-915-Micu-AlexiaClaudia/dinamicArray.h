//
// Created by alexi on 3/23/2023.
//

#ifndef A23_915_MICU_ALEXIACLAUDIA_DINAMICARRAY_H
#define A23_915_MICU_ALEXIACLAUDIA_DINAMICARRAY_H
#pragma once

#pragma once
#include "country.h"

typedef Country TElement;

typedef struct
{
    TElement* elements;
    int length;			// actual length of the array
    int capacity;
} DynamicArray;

/// <summary>
/// Creates a dynamic array of generic elements, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <returns>A pointer the the created dynamic array.</returns>
DynamicArray* createDynamicArray(int capacity);

/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array to be destoyed.</param>
/// <returns>A pointer the the created dynamic array.</returns>
void clearDynamicArray(DynamicArray* dynamicArray);

/// <summary>
/// Adds a generic element to the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="p">The planet to be added.</param>
int add(DynamicArray* dynamicArray, TElement tElement);

int getLength(DynamicArray* arr);
int getCapacity(DynamicArray* arr);

// Tests
void testDynamicArray();

#endif //A23_915_MICU_ALEXIACLAUDIA_DINAMICARRAY_H
