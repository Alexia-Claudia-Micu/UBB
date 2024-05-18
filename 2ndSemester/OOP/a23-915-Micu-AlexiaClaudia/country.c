//
// Created by alexi on 3/9/2023.
//
#include "country.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Country createCountry(char* name, char* continent, long int population)
{
    Country new_country;
    new_country.name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(new_country.name, name);
    new_country.continent = (char*)malloc((strlen(continent) + 1) * sizeof(char));
    strcpy(new_country.continent, continent);
    new_country.population = population;

    return new_country;
}

void clearCountry(Country* country)
{
    free(country->name);
    free(country->continent);
    //free(country);
}

char* getName(Country* country)
{
    return country->name;
}

char* getContinent(Country* country)
{
    return country->continent;
}

long int getPopulation(Country* country)
{
    return country->population;
}

void setPopulation(Country* country, int new_population)
{
    country->population = new_population;
}

void toString(Country country, char* string)
{
    sprintf(string, "%s is on continent %s and has a population of %ld.", getName(&country), getContinent(&country), getPopulation(&country));
}

int testCountry()
{
    int numberOfErrors = 0;
    Country newCountry = createCountry("Denmark", "Europe", 20000000);
    char* countryToString;
    countryToString = (char*) malloc(64*sizeof(char ));
    if(strcmp(newCountry.continent, "Europe") != 0)
        return numberOfErrors++;
    if(strcmp(newCountry.name, "Denmark") != 0)
        return numberOfErrors++;
    if(newCountry.population != 20000000)
        return numberOfErrors++;
    setPopulation(&newCountry, 10);
    if(newCountry.population != 10)
        return numberOfErrors++;
    toString(newCountry, countryToString);
    if(strcmp(countryToString, "Denmark is on continent Europe and has a population of 10.") != 0)
        return numberOfErrors++;
    free(countryToString);
    clearCountry(&newCountry);
    return numberOfErrors;

}