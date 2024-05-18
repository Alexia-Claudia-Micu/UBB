//
// Created by alexi on 3/22/2023.
//
#include <stdio.h>
#include "country.h"
#include "repository.h"
#include "service.h"
#include "dinamicArray.h"

int mainy()
{
    printf("%d - errors for testing Country entity.\n", testCountry());
    printf("%d - errors for testing Repository entity.\n", testRepository());
    printf("%d - errors for testing Service entity.\n", testService());
    testDynamicArray();

    return 1;
}