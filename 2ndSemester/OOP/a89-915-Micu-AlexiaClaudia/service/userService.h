//
// Created by alexi on 4/2/2023.
//

#ifndef A45_915_MICU_ALEXIACLAUDIA_USERSERVICE_H
#define A45_915_MICU_ALEXIACLAUDIA_USERSERVICE_H
#pragma once
#include "vector"
#include "event.h"
#include "repository.h"
#include <bits/stdc++.h>

using namespace::std;

class UserService
{
private:
    Repository &eventArray;
    Repository listOfUserEvents = Repository();
    Repository listOfFilteredEvents = Repository();
public:
    UserService(Repository &repository1);
    ~UserService();
    void filterEventsForAMonth(int month);
    vector<Event> getEventsChronologicallyForAMonth(int month);
    void sortEvents();
    vector<Event> getListOfUserEvents();
    bool addEvent(Event newEvent);
    Event removeEvent(int eventIndex);
};


#endif //A45_915_MICU_ALEXIACLAUDIA_USERSERVICE_H
