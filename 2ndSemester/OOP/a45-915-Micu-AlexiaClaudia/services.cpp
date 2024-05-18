//
// Created by alexi on 3/30/2023.
//
#include "services.h"

using namespace std;

AdministratorService::AdministratorService(){
}

#include "assert.h"
#include "cstring"
#include "iostream"
void administratorServiceTests(){
    AdministratorService administratorService = AdministratorService();
    Event event1, event2, event3;
    event1.setTitle("event1");
    event2.setTitle("e2"); event2.setDescription("d2"); event2.setDateAndTime(2000, 1, 1, 1, 1);
    event3.setTitle("event3");
    assert(administratorService.add("e1", "d1", 2000, 1, 1, 1, 1, 1, "l1") == 1);
    assert(administratorService.add("e1", "d1", 2000, 1, 1, 1, 1, 1, "l1") == 0);
    assert(administratorService.remove("e2", 2000, 1, 1, 1, 1) == 0);
    assert(administratorService.add("e2", "d2", 2000, 1, 1, 1, 1, 1, "l2") == 1);
    assert(administratorService.remove("e2", 2000, 1, 1, 1, 1) == 1);
    assert(administratorService.update("e1", "e3","d3", 2000, 1, 1, 1, 1, 2020, 1, 1, 1, 1, 20, "l3"));
    assert(administratorService.add("e2", "d2", 2000, 1, 1, 1, 1, 1, "l2") == 1);
    assert(administratorService.updatePopulation(event2, 3) == 1);
    assert(administratorService.getDynamicArray().getElement(1).getNumberOfPeople() == 4);
    assert(::strcmp(administratorService.getDynamicArray().getElement(0).getTitle(), "e3") == 0);
    cout<<"Test Administrator Service successful\n";
}

void AdministratorService::runTests(){
    this->dynamicArray.testDynamicArray();
    Event event;
    event.testEventArray();
    event.testEventDeclaration();
    DynamicArrayIterator<Event> arrayIterator = this->dynamicArray.iterator();
    arrayIterator.testDynamicArrayIterator();
    administratorServiceTests();
}

bool AdministratorService::add(char* title, char* description, int year, int month, int day, int hour, int minute, int atendees, char* link)
{
    Event new_event;
    new_event.setTitle(title); new_event.setDescription(description);new_event.setLink(link); new_event.setDateAndTime(year, month, day, hour, minute); new_event.setNumberOfPeople(atendees);
    bool result =  this->dynamicArray.add(new_event);
    return result;
}

bool AdministratorService::remove(char* title, int year, int month, int day, int hour, int minute)
{
    Event new_event;
    new_event.setTitle(title);new_event.setDateAndTime(year, month, day, hour, minute);
    return this->dynamicArray.remove(new_event);
}

bool AdministratorService::update(char *initialTitle, char *newTitle, char *newDescription, int initialYear, int initialMonth, int initialDay, int initialHour, int initialMinute, int newYear, int newMonth, int newDay, int newHour, int newMinute, int newAtendees,
                                  char *newLink) {
    Event new_event, old_event;
    old_event.setTitle(initialTitle); old_event.setDateAndTime(initialYear, initialMonth, initialDay, initialHour, initialMinute);
    int indexOfElementToUpdate = this->dynamicArray.get(old_event);
    new_event.setTitle(newTitle); new_event.setDateAndTime(newYear, newMonth, newDay, newHour, newMinute); new_event.setNumberOfPeople(newAtendees); new_event.setDescription(newDescription); new_event.setLink(newLink);
    return this->dynamicArray.update(indexOfElementToUpdate, new_event);
}

DynamicArrayIterator<Event> AdministratorService::iterator(){
    DynamicArrayIterator<Event> arrayIterator = this->dynamicArray.iterator();
    return arrayIterator;
}

DynamicArray<Event>& AdministratorService::getDynamicArray() {
    return this->dynamicArray;
}

int AdministratorService::updatePopulation(Event event, int population)
{
    int index = this->dynamicArray.get(event), newPopulation = this->dynamicArray.getElement(index).getNumberOfPeople() + population;
    event.setNumberOfPeople(newPopulation);
    this->dynamicArray.update(index, event);
}