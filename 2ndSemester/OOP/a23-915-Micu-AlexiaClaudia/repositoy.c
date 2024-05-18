//
// Created by alexi on 3/9/2023.
//
#include "repository.h"
#include <string.h>
#include <stdlib.h>

CountryRepository createRepository(int capacity)
{
    CountryRepository newCountryRepository;
    //newCountryRepository.numberOfCountries = 0;
    //newCountryRepository.capacity = capacity;
    newCountryRepository.countries = createDynamicArray(2);
    return newCountryRepository;
}

void clearRepository(CountryRepository* countryRepository)
{
//    for(int i = 0; i < countryRepository->countries->length; i++)
//        clearCountry(&countryRepository->countries->elements[i]);

    clearDynamicArray(&countryRepository->countries);
    //free(countryRepository);
}

CountryRepository copyRepository(CountryRepository* countryRepository)
{
    CountryRepository newCountryRepository = createRepository(countryRepository->countries->capacity);
    for (int i = 0; i < countryRepository->countries->length; i++) {
        Country newCountry = createCountry(countryRepository->countries->elements[i].name,
                                           countryRepository->countries->elements[i].continent,
                                           countryRepository->countries->elements[i].population);
        add(newCountryRepository.countries, newCountry);
    }
    return newCountryRepository;
    //return countryRepository;
}

int existCountry(CountryRepository* countryRepository,Country* checkCountry)
{
    for(int i = 0; i < countryRepository->countries->length; i++)
        if(strcmp(countryRepository->countries->elements[i].name,checkCountry->name) == 0)
            return 1;
    return 0;
}

//void resizeRepository(CountryRepository* countryRepository)
//{
//    Country* countryAuxiliary;
//    countryAuxiliary = (Country*) malloc(countryRepository->capacity * 2 * sizeof (Country));
//    for(int i = 0; i < countryRepository->numberOfCountries; i++)
//        countryAuxiliary[i] = countryRepository->countries[i];
//    free(countryRepository->countries);
//    countryRepository->countries = countryAuxiliary;
//    countryRepository->capacity *= 2;
//}

int addCountry(CountryRepository* countryRepository,Country* newCountry)
{
    if(existCountry(countryRepository, newCountry) != 0)
        return 0;
    if(add(countryRepository->countries, *newCountry) == 0)
        return 0;
    return 1;
//    if(existCountry(countryRepository, newCountry) != 0)
//        return 0;
//    if(countryRepository->capacity == countryRepository->numberOfCountries)
//        resizeRepository(countryRepository);
//    countryRepository->countries[countryRepository->numberOfCountries] = *newCountry;
//    countryRepository->numberOfCountries++;
//    return 1;
}

int deleteCountry(CountryRepository* countryRepository,char* countryToDelete)
{
    for(int i = 0; i < countryRepository->countries->length; i++)
        if(strcmp(countryRepository->countries->elements[i].name, countryToDelete) == 0) {
            countryRepository->countries->length--;
            clearCountry(&countryRepository->countries->elements[i]);
            countryRepository->countries->elements[i] = countryRepository->countries->elements[countryRepository->countries->length];
            return 1;
        }
    return 0;
}

void filterCountries(CountryRepository* countryRepository, char keyString[], char result[])
{
    char* countryToAdd;
    countryToAdd = (char*) malloc(100 * sizeof (char ));
    strcpy(result, "");
    for(int i = 0; i<countryRepository->countries->length; i++)
        if(strstr(countryRepository->countries->elements[i].name, keyString) != NULL || strcmp(keyString, "-") == 0) {
            strcat(result, "\n");
            toString(countryRepository->countries->elements[i], countryToAdd);
            strcat(result, countryToAdd);
        }
    free(countryToAdd);
}

Country* getCountry(CountryRepository* countryRepository, char countryName[])
{
    for( int i = 0; i < countryRepository->countries->length; i++)
        if(strcmp(countryRepository->countries->elements[i].name, countryName) == 0)
            return &countryRepository->countries->elements[i];
    return &countryRepository->countries->elements[0];
}

void sortCountryRepository(CountryRepository* countryRepository)
{
    for(int i = 0; i < countryRepository->countries->length - 1; i++)
        for(int j = i + 1; j < countryRepository->countries->length; j++)
            if(countryRepository->countries->elements[i].population < countryRepository->countries->elements[j].population)
            {
                Country auxiliaryCountry = countryRepository->countries->elements[i];
                countryRepository->countries->elements[i] = countryRepository->countries->elements[j];
                countryRepository->countries->elements[j] = auxiliaryCountry;
            }
}

void filterBasedOnContinent(CountryRepository* countryRepository, CountryRepository* countriesOnSameContinent, char* continentName)
{
    for(int i = 0; i < countryRepository->countries->length; i++)
        if(strstr(countryRepository->countries->elements[i].continent, continentName))
            addCountry(countriesOnSameContinent, &countryRepository->countries->elements[i]);
    if(countriesOnSameContinent->countries->length == 0) {
        for(int i = 0; i < countryRepository->countries->length; i++)
            addCountry(countriesOnSameContinent, &countryRepository->countries->elements[i]);
    }
}

//------------------------------------------------------------------------------------------------

int migrate(CountryRepository* countryRepository, char* fromName, char* toName, int numberOfMigrators){
    int fromCountryIndex = -1, toCountryIndex = -1;
    for(int i = 0; i < countryRepository->countries->length; i++)
        if(strcmp(countryRepository->countries->elements[i].name, fromName) == 0)
            fromCountryIndex = i;
        else
            if(strcmp(countryRepository->countries->elements[i].name, toName) == 0)
                toCountryIndex = i;
    if( fromCountryIndex != -1 && toCountryIndex != -1)
    {
        countryRepository->countries->elements[fromCountryIndex].population -= numberOfMigrators;
        countryRepository->countries->elements[toCountryIndex].population += numberOfMigrators;
        return 1;
    }
    return 0;
}

//------------------------------------------------------------------------------------------------

void generateStartupEntries(CountryRepository* countryRepository)
{
    Country new_country = createCountry("Romania", "Europe", 18000000);
    Country new_country1 = createCountry("England", "Europe", 118000000);
    Country new_country2 = createCountry("Argentina", "America", 1000000);
    Country new_country3 = createCountry("Korea", "Asia", 700000000);
    Country new_country4 = createCountry("Australia", "Australia", 300000000);
    Country new_country5 = createCountry("India", "Asia", 2000000000);
    Country new_country6 = createCountry("Turkey", "Asia", 150000000);
    Country new_country7 = createCountry("Japan", "Asia", 400000000);
    Country new_country8 = createCountry("Germany", "Europe", 350000000);
    Country new_country9 = createCountry("Canada", "America", 200000000);
    Country new_country10 = createCountry("Sweden", "Europe", 7800000);
    Country new_country11 = createCountry("Russia", "Europe", 140000000);
    addCountry(countryRepository,&new_country);
    addCountry(countryRepository,&new_country1);
    addCountry(countryRepository,&new_country2);
    addCountry(countryRepository,&new_country3);
    addCountry(countryRepository,&new_country4);
    addCountry(countryRepository,&new_country5);
    addCountry(countryRepository,&new_country6);
    addCountry(countryRepository,&new_country7);
    addCountry(countryRepository,&new_country8);
    addCountry(countryRepository,&new_country9);
    addCountry(countryRepository,&new_country10);
    addCountry(countryRepository,&new_country11);
}

//------------------------------------------------------------------------------------------------

int testRepository()
{
    CountryRepository newRepository = createRepository(2);
    generateStartupEntries(&newRepository);
    int numberOfErrors = 0;

    // delete and exist
    int existCountry1, existCountry2;
    Country countryKorea = createCountry("Korea", "Asia", 700000000);
    existCountry1 = existCountry(&newRepository, &countryKorea);
    deleteCountry(&newRepository,"Korea");
    existCountry2 = existCountry(&newRepository, &countryKorea);
    clearCountry(&countryKorea);
    if(existCountry1 == 0 || existCountry2 == 1)
        numberOfErrors++;

    // add and exist
    Country countryDenmark = createCountry("Denmark", "Europe", 20000000);
    existCountry1 = existCountry(&newRepository, &countryDenmark);
    addCountry(&newRepository, &countryDenmark);
    existCountry2 = existCountry(&newRepository, &countryDenmark);
    //clearCountry(&countryDenmark);
    if(existCountry1 == 1 || existCountry2 == 0)
        numberOfErrors++;

    // capacity
    if(newRepository.countries->capacity != 16)
        numberOfErrors++;

    // country counter
    if(newRepository.countries->length != 12)
        numberOfErrors++;

    // sorting
    sortCountryRepository(&newRepository);
    for(int i = 0; i < newRepository.countries->length - 1; i++)
        if(newRepository.countries->elements[i].population < newRepository.countries->elements[i+1].population)
            numberOfErrors++;

    clearRepository(&newRepository);
    return numberOfErrors;
}