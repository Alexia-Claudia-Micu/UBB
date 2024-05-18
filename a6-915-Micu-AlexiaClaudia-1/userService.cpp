//
// Created by alexi on 4/2/2023.
//
#include "userService.h"

UserService::UserService(Repository &repository1): eventArray(repository1){
}

UserService::~UserService() {
}

void UserService::filterEventsForAMonth(int month){
    while (this->listOfFilteredEvents.isEmpty() == 0)
        this->listOfFilteredEvents.remove(this->listOfFilteredEvents.getElement(0));
    for(int i = 0; i < this->eventArray.size(); i++)
        if(this->eventArray.getElement(i).getDateAndTime().date.month == month)
            listOfFilteredEvents.add(this->eventArray.getElement(i));
    if(this->listOfFilteredEvents.isEmpty() == true)
        for(int i = 0; i < this->eventArray.size(); i++)
            listOfFilteredEvents.add(this->eventArray.getElement(i));
}

void UserService::sortEvents() {
    sort(this->listOfFilteredEvents.getAll().begin(), this->listOfFilteredEvents.getAll().end());
}

vector<Event> UserService::getEventsChronologicallyForAMonth(int month)
{
    this->filterEventsForAMonth(month);
    this->sortEvents();
    return this->listOfFilteredEvents.getIterator();
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

vector<Event> UserService::getListOfUserEvents()
{
    return this->listOfUserEvents.getIterator();
}

#include <iostream>
#include "assert.h"
#include "cstring"
void UserService::runUserTests()
{
    Repository repository1 = Repository(2);
    UserService userService = UserService(repository1);
    Event event1, event2, event3;
    event2.setTitle("e2"); event2.setDescription("d2"); event2.setDateAndTime(2000, 1, 10, 1, 1); event2.setNumberOfPeople(1);
    event3.setTitle("e3"); event3.setDescription("d3"); event3.setDateAndTime(2000, 1, 1, 1, 1);
    event1.setTitle("e1"); event1.setDescription("d1"); event1.setDateAndTime(2000, 2, 15, 1, 1);
    assert(userService.listOfFilteredEvents.isEmpty() == true);
    assert(userService.listOfFilteredEvents.isFull() == false);
    assert(userService.listOfUserEvents.isEmpty() == true);
    assert(userService.addEvent(event2) == 1);
    assert(userService.addEvent(event2) == 0);
    assert(userService.listOfUserEvents.getElement(0).getNumberOfPeople() == 2);
    assert(userService.removeEvent(0) == event2);
    assert(userService.eventArray.add(event1) == 1);
    assert(userService.eventArray.add(event2) == 1);
    assert(userService.eventArray.add(event3) == 1);
    assert(userService.listOfFilteredEvents.isEmpty() == 1);
    assert(userService.eventArray.size() == 3);
    userService.filterEventsForAMonth(1);
    assert(userService.listOfFilteredEvents.size() == 2);
    userService.sortEvents();
    assert(userService.listOfFilteredEvents.getElement(0) == event3);
    userService.filterEventsForAMonth(12);
    assert(userService.listOfFilteredEvents.size() == 3);
    userService.sortEvents();
    userService.getListOfUserEvents();
    userService.getEventsChronologicallyForAMonth(1);
    std::cout<<"Test User Service successful\n";
}