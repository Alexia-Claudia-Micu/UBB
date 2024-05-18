//
// Created by alexi on 4/2/2023.
//
#include "userService.h"

UserService::UserService(DynamicArray<Event> &dynamicArray1): dynamicArray(dynamicArray1){
}

#include <iostream>
#include "assert.h"
#include "cstring"
void UserService::runUserTests()
{
    DynamicArray<Event> dynamicArray1 = DynamicArray<Event>(2);
    UserService userService = UserService(dynamicArray1);
    Event event1, event2, event3;
    event2.setTitle("e2"); event2.setDescription("d2"); event2.setDateAndTime(2000, 1, 10, 1, 1); event2.setNumberOfPeople(1);
    event3.setTitle("e3"); event3.setDescription("d3"); event3.setDateAndTime(2000, 1, 1, 1, 1);
    event1.setTitle("e1"); event1.setDescription("d1"); event1.setDateAndTime(2000, 2, 1, 1, 1);
    assert(userService.listOfFilteredEvents.isEmpty() == true);
    assert(userService.listOfFilteredEvents.isFull() == false);
    assert(userService.listOfUserEvents.isEmpty() == true);
    assert(userService.addEvent(event2) == 1);
    assert(userService.addEvent(event2) == 0);
    assert(userService.listOfUserEvents.getElement(0).getNumberOfPeople() == 2);
    assert(userService.removeEvent(0) == event2);
    assert(userService.dynamicArray.add(event1) == 1);
    assert(userService.dynamicArray.add(event2) == 1);
    assert(userService.dynamicArray.add(event3) == 1);
    assert(userService.listOfFilteredEvents.isEmpty() == 1);
    assert(userService.dynamicArray.size() == 3);
    userService.filterEventsForAMonth(1);
    assert(userService.listOfFilteredEvents.size() == 2);
    userService.sortEvents();
    assert(userService.listOfFilteredEvents.getElement(0) == event3);
    std::cout<<"Test User Service successful\n";
}

void UserService::filterEventsForAMonth(int month){
    DynamicArrayIterator<Event> iteratorDynamicArray = this->dynamicArray.iterator();
    iteratorDynamicArray.first();
    while(iteratorDynamicArray.valid()) {
        if (iteratorDynamicArray.getCurrent().getDateAndTime().date.month == month)
            listOfFilteredEvents.add(iteratorDynamicArray.getCurrent());
        iteratorDynamicArray.next();
    }
    if(listOfFilteredEvents.isEmpty() == true) {
        iteratorDynamicArray.first();
        while (iteratorDynamicArray.valid()) {
            listOfFilteredEvents.add(iteratorDynamicArray.getCurrent());
            iteratorDynamicArray.next();
        }
    }
}

void UserService::sortEvents() {
    DynamicArrayIterator<Event> arrayIterator = this->listOfFilteredEvents.iterator();
    int sem = 1;
    while(sem)
    {
        sem = 0;
        arrayIterator.first();
        Event previousEvent = arrayIterator.getCurrent();
        arrayIterator.next();
        while (arrayIterator.valid())
        {
            if(previousEvent > arrayIterator.getCurrent())
            {
                int index1, index2;
                index1 = this->listOfFilteredEvents.get(arrayIterator.getCurrent());
                index2 = this->listOfFilteredEvents.get(previousEvent);
                this->listOfFilteredEvents.update(index2, arrayIterator.getCurrent());
                this->listOfFilteredEvents.update(index1, previousEvent);
                sem = 1;
            }
            previousEvent = arrayIterator.getCurrent();
            arrayIterator.next();
        }
    }
}

DynamicArrayIterator<Event> UserService::getEventsChronologicallyForAMonth(int month)
{
    this->filterEventsForAMonth(month);
    this->sortEvents();
    return this->listOfFilteredEvents.iterator();
}

bool UserService::addEvent(Event newEvent)
{
    newEvent.setNumberOfPeople(newEvent.getNumberOfPeople() + 1);
    return this->listOfUserEvents.add(newEvent);
}

Event UserService::removeEvent(int eventIndex)
{
    Event eventToDelete = this->listOfUserEvents.getElement(eventIndex);
    this->listOfUserEvents.remove(eventToDelete);
    return eventToDelete;
}

DynamicArrayIterator<Event> UserService::getListOfUserEvents()
{
    return this->listOfUserEvents.iterator();
}