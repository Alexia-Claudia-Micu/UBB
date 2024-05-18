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
    Repository* repository;
protected:
    FileRepository eventListing;
public:
    AdministratorService(Repository* repository, FileRepository fileRepository, string listingMode);
    ~AdministratorService();
    bool add(string title, string description, int year, int month, int day, int hour, int minute, int attendees, string link);
    bool remove(string title, int year, int month, int day, int hour, int minute);
    bool update(int indexOfElementToUpdate, string newTitle, string newDescription, int newYear, int newMonth, int newDay, int newHour, int newMinute, int newAttendees, string newLink);
    vector<Event> getIterator();
    int updatePopulation(Event event, int population);
    Event getElement(int index);
    Repository& getElements();
    void setEventListingType(string listingMode);
    void loadListingOfEventsInFormat();
};

#endif //A45_915_MICU_ALEXIACLAUDIA_SERVICES_H
