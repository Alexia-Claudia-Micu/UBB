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
