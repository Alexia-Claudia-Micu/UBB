//
// Created by alexi on 3/30/2023.
//

#ifndef A45_915_MICU_ALEXIACLAUDIA_SERVICES_H
#define A45_915_MICU_ALEXIACLAUDIA_SERVICES_H
#pragma once
#include "repository.h"
#include "event.h"
#include "fileRepository.h"

class AdministratorService
{
private:
    FileRepository repository;
protected:
    FileRepository eventListing;
public:
    AdministratorService(FileRepository fileRepository, string listingMode);
    ~AdministratorService();
    bool add(char* title, char* description, int year, int month, int day, int hour, int minute, int atendees, char* link);
    bool remove(char* title, int year, int month, int day, int hour, int minute);
    bool update(char *initialTitle, char *newTitle, char *newDescription, int initialYear, int initialMonth, int initialDay, int initialHour, int initialMinute, int newYear, int newMonth, int newDay, int newHour, int newMinute, int newAtendees,
                char *newLink);
    vector<Event> getIterator();
    int updatePopulation(Event event, int population);
    Event getElement(int index);
    Repository& getElements();
    void setEventListingType(string listingMode);
    void loadListingOfEventsInFormat();
    void runTests();
};

#endif //A45_915_MICU_ALEXIACLAUDIA_SERVICES_H
