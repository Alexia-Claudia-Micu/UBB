//
// Created by alexi on 3/18/2023.
//
//
// Created by alexi on 3/16/2023.
//
#include "ui.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Service createService()
{
    Service newService;
    newService.countryRepository = createRepository(2);
    generateStartupEntries(&newService.countryRepository);
    newService.currentVersion = -1;
    newService.availableRedos = 0;
    newService.historyOfChanges = (CountryRepository*) malloc(32 * sizeof(CountryRepository));
    updateHistoryOfChanges(&newService);
    return newService;
}

void clearService(Service* service)
{
    clearRepository(&service->countryRepository);
    for(int i = 0; i <= service->currentVersion; i++)
        clearRepository(&service->historyOfChanges[i]);
    for(int i = 1; i <= service->availableRedos; i++)
        clearRepository(&service->historyOfChanges[service->currentVersion + i]);
    free(service->historyOfChanges);
    //free(service);
}

//CountryRepository copyRepository(CountryRepository* countryRepository)
//{
//    CountryRepository newCountryRepository = createRepository(countryRepository->countries->capacity);
//    newCountryRepository.countries->length = countryRepository->countries->length;
//    for (int i = 0; i < newCountryRepository.countries->length; i++) {
//        Country newCountry = createCountry(countryRepository->countries->elements[i].name,
//                                           countryRepository->countries->elements[i].continent,
//                                           countryRepository->countries->elements[i].population);
//        newCountryRepository.countries->elements[i] = newCountry;
//    }
//    return newCountryRepository;
//    //return countryRepository;
//}

void updateHistoryOfChanges(Service* service)
{
    for(int i = 1; i <= service->availableRedos; i++)
        clearRepository(&service->historyOfChanges[service->currentVersion + i]);
    service->availableRedos = 0;
    service->currentVersion ++;
    service->historyOfChanges[service->currentVersion] = copyRepository(&service->countryRepository);
}

int addCountryToRepo(Service* service, char* countryName, char* continent, long int population)
{
    Country newCountry;
    newCountry = createCountry(countryName, continent, population);
    int additionResult = addCountry(&service->countryRepository, &newCountry);
    if(additionResult == 1)
        updateHistoryOfChanges(service);
    //clearCountry(&newCountry);
    return additionResult;
}

int undo(Service* service)
{
    if(service->currentVersion)
    {
        service->currentVersion --;
        CountryRepository newCountryRepository = copyRepository(&service->historyOfChanges[service->currentVersion]);
        clearRepository(&service->countryRepository);
        service->countryRepository = newCountryRepository;
        service->availableRedos ++;
        return 1;
    }
    return 0;
}

int redo(Service* service)
{
    if(service->availableRedos)
    {
        service->currentVersion ++;
        CountryRepository newCountryRepository = copyRepository(&service->historyOfChanges[service->currentVersion]);
        clearRepository(&service->countryRepository);
        service->countryRepository = newCountryRepository;
        service->availableRedos --;
        return 1;
    }
    return 0;
}

int deleteCountryFromRepo(Service* service, char* countryName)
{
    int deleteResult = deleteCountry(&service->countryRepository, countryName);
    if(deleteResult == 1)
        updateHistoryOfChanges(service);
    return deleteResult;
}

int migratePopulation(Service* service, char* fromCountryName, char* toCountryName, long int numberMigrators)
{
    int migrateResult = migrate(&service->countryRepository, fromCountryName, toCountryName, numberMigrators);
    if(migrateResult == 1)
        updateHistoryOfChanges(service);
    return migrateResult;
}

void filterCountriesWithString(Service* service, char* keyString, char* result)
{
    filterCountries(&service->countryRepository, keyString, result);
}

void filterAndSortCountries(Service* service, char* continentName, char* result)
{
    CountryRepository countriesOnSameContinent;
    countriesOnSameContinent = createRepository(service->countryRepository.countries->capacity);
    filterBasedOnContinent(&service->countryRepository, &countriesOnSameContinent, continentName);
    sortCountryRepository(&countriesOnSameContinent);
    filterCountries(&countriesOnSameContinent, "-", result);
    free(countriesOnSameContinent.countries);
    //clearRepository(&countriesOnSameContinent);
}

int testService()
{
    int numberOfErrors = 0;
    Service newService = createService();
    updateHistoryOfChanges(&newService);

    // add
    if(addCountryToRepo(&newService, "Denmark", "Europe", 20000000) == 0)
        numberOfErrors++;
    if(addCountryToRepo(&newService, "Denmark", "Europe", 20000000) == 1)
        numberOfErrors++;

    // delete
    if(deleteCountryFromRepo(&newService, "India") == 0)
        numberOfErrors++;
    if(deleteCountryFromRepo(&newService, "India") == 1)
        numberOfErrors++;

    // version keeping for undo and redo
    if(newService.currentVersion != 3)
        numberOfErrors ++;

    // migrate
    int populationJapanBefore, populationJapanAfter, populationRussiaBefore, populationRussiaAfter;
    Country* japan;
    Country* russia;
    japan = getCountry(&newService.countryRepository, "Japan");
    populationJapanBefore = japan->population;
    russia = getCountry(&newService.countryRepository, "Russia");
    populationRussiaBefore = russia->population;
    migratePopulation(&newService, "Japan", "Russia", 500000);
    populationJapanAfter = populationJapanBefore - 500000;
    populationRussiaAfter = populationRussiaBefore + 500000;
    if(japan->population != populationJapanAfter || russia->population != populationRussiaAfter)
        numberOfErrors++;

    // undo
    undo(&newService);
    japan = getCountry(&newService.countryRepository, "Japan");
    russia = getCountry(&newService.countryRepository, "Russia");
    if(japan->population != populationJapanBefore || russia->population != populationRussiaBefore)
        numberOfErrors++;

    // redo
    redo(&newService);
    japan = getCountry(&newService.countryRepository, "Japan");
    russia = getCountry(&newService.countryRepository, "Russia");
    if(japan->population != populationJapanAfter || russia->population != populationRussiaAfter)
        numberOfErrors++;

    clearService(&newService);
    return numberOfErrors;
}