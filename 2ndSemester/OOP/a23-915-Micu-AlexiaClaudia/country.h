//
// Created by alexi on 3/9/2023.
//

#ifndef A23_915_MICU_ALEXIACLAUDIA_COUNTRY_H
#define A23_915_MICU_ALEXIACLAUDIA_COUNTRY_H

#pragma once

typedef struct
{
    char* name;
    char* continent;
    long int population;
}Country;

Country createCountry(char name[], char continent[], long int population);
char* getName(Country* country);
char* getContinent(Country* country);
long int getPopulation(Country* country);
void setPopulation(Country* country, int new_population);
void toString(Country country, char* string);
void clearCountry(Country* country);
int testCountry();

#endif //A23_915_MICU_ALEXIACLAUDIA_COUNTRY_H
