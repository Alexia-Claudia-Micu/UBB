//
// Created by alexi on 3/15/2023.
//

#ifndef A23_915_MICU_ALEXIACLAUDIA_REPOSITORY_H
#define A23_915_MICU_ALEXIACLAUDIA_REPOSITORY_H
#pragma once
#include "country.h"
#include "dinamicArray.h"

typedef struct
{
    DynamicArray* countries;
    //int numberOfCountries;
    //int capacity;
}CountryRepository;

CountryRepository createRepository();
int addCountry(CountryRepository* countryRepository, Country* newCountry);
int existCountry(CountryRepository* countryRepository, Country* checkCountry);
int deleteCountry(CountryRepository* countryRepository,char* countryToDelete);
Country* getCountry(CountryRepository* countryRepository, char countryName[]);
void sortCountryRepository(CountryRepository* countryRepository);
void filterBasedOnContinent(CountryRepository* countryRepository, CountryRepository* countriesOnSameContinent, char* continentName);
int migrate(CountryRepository* countryRepository, char* fromName, char* toName, int numberOfMigrators);
void generateStartupEntries(CountryRepository* countryRepository);
void filterCountries(CountryRepository* countryRepository, char keyString[], char result[]);
void clearRepository(CountryRepository* countryRepository);
CountryRepository copyRepository(CountryRepository* countryRepository);
int testRepository();

#endif //A23_915_MICU_ALEXIACLAUDIA_REPOSITORY_H
