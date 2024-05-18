//
// Created by alexi on 3/18/2023.
//

#ifndef A23_915_MICU_ALEXIACLAUDIA_SERVICE_H
#define A23_915_MICU_ALEXIACLAUDIA_SERVICE_H

#pragma once
#include "repository.h"

typedef struct
{
    CountryRepository countryRepository;
    CountryRepository* historyOfChanges;
    int currentVersion;
    int availableRedos;
}Service;

Service createService();
int addCountryToRepo(Service* service, char* countryName, char* continent, long int population);
int deleteCountryFromRepo(Service* service, char* countryName);
int migratePopulation(Service* service, char* fromCountryName, char* toCountryName, long int numberMigrators);
void filterCountriesWithString(Service* service, char* keyString, char* result);
void filterAndSortCountries(Service* service, char* continentName, char* result);
int redo(Service* service);
int undo(Service* service);
void clearService(Service* service);
void updateHistoryOfChanges(Service* service);
int testService();

#endif //A23_915_MICU_ALEXIACLAUDIA_SERVICE_H
