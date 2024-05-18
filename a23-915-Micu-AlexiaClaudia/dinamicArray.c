//
// Created by alexi on 3/23/2023.
//
#include "dinamicArray.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity)
{
    DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));

    if (dynamicArray == NULL)
        return NULL;

    dynamicArray->capacity = capacity;
    dynamicArray->length = 0;

    dynamicArray->elements = malloc(capacity * sizeof(TElement));
    if (dynamicArray->elements == NULL)
        return NULL;

    return dynamicArray;
}

void clearDynamicArray(DynamicArray* dynamicArray)
{
    if (dynamicArray == NULL)
        return;
    free(dynamicArray->elements);
    dynamicArray->elements = NULL;
    //free(dynamicArray);
}

void resize(DynamicArray* dynamicArray)
{
    TElement* tElementArray;
    tElementArray = (TElement*) malloc(dynamicArray->capacity * 2 * sizeof (TElement));
    for(int i = 0; i < dynamicArray->length; i++)
       tElementArray[i] = dynamicArray->elements[i];
    free(dynamicArray->elements);
    dynamicArray->elements = tElementArray;
    dynamicArray->capacity *= 2;
}

int add(DynamicArray* dynamicArray, TElement tElement)
{
    if (dynamicArray == NULL)
        return 0;
    if (dynamicArray->elements == NULL)
        return 0;

    if (dynamicArray->length == dynamicArray->capacity)
        resize(dynamicArray);
    dynamicArray->elements[dynamicArray->length] = tElement;
    dynamicArray->length++;
    return 1;
}

int getLength(DynamicArray* arr)
{
    if (arr == NULL)
        return 0;
    return arr->length;
}

int getCapacity(DynamicArray* arr)
{
    if (arr == NULL)
        return 0;
    return arr->capacity;
}

void testDynamicArray()
{
    DynamicArray* dynamicArray = createDynamicArray(2);
    if (dynamicArray == NULL)
        assert(0);

    assert(getCapacity(dynamicArray) == 2);
    assert(getLength(dynamicArray) == 0);

    Country country1 = createCountry("Denmark", "Europe", 20000000);
    add(dynamicArray, country1);
    assert(getLength(dynamicArray) == 1);

    Country country2 = createCountry("Honduras", "America", 5000000);
    add(dynamicArray, country2);
    assert(getLength(dynamicArray) == 2);

    Country country3 = createCountry("Peru", "America", 1500000);
    add(dynamicArray, country3);
    assert(getLength(dynamicArray) == 3);

    clearDynamicArray(dynamicArray);
}