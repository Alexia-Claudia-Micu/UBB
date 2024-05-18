//
// Created by alexi on 4/2/2023.
//

#ifndef A45_915_MICU_ALEXIACLAUDIA_USERSERVICE_H
#define A45_915_MICU_ALEXIACLAUDIA_USERSERVICE_H
#pragma once
#include "dynamicArray.h"
#include "dynamicArrayIterator.h"
#include "event.h"

template <typename Event>
class DynamicArray;
template <typename Event>
class DynamicArrayIterator;

class UserService
{
private:
    DynamicArray<Event> &dynamicArray;
    DynamicArray<Event> listOfUserEvents = DynamicArray<Event>(2);
    DynamicArray<Event> listOfFilteredEvents = DynamicArray<Event>(2);
public:
    UserService(DynamicArray<Event> &dynamicArray);
    void filterEventsForAMonth(int month);
    DynamicArrayIterator<Event> getEventsChronologicallyForAMonth(int month);
    void sortEvents();
    DynamicArrayIterator<Event> getListOfUserEvents();
    bool addEvent(Event newEvent);
    Event removeEvent(int eventIndex);
    void runUserTests();
};


#endif //A45_915_MICU_ALEXIACLAUDIA_USERSERVICE_H
