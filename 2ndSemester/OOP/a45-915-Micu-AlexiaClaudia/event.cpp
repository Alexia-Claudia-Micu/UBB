//
// Created by alexi on 3/29/2023.
//
#include "event.h"
#include <exception>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <assert.h>
#include <iostream>

using namespace std;

Event::Event() {
    this->title = new char[50];
    this->description = new char[100];
    this->link = new char[100];
    this->numberOfPeople = 0;
    this->dateAndTime.time.hour = 0;
    this->dateAndTime.time.minute = 0;
    this->dateAndTime.date.year = 0;
    this->dateAndTime.date.month = 0;
    this->dateAndTime.date.day = 0;
}

void * Event::operator new(size_t size) {
    void * pointer = ::operator new(size);

    return pointer;
}

void* Event::operator new[](size_t size) {
    void* pointer = ::operator new[](size);
    return pointer;
}

void Event::operator delete[](void* pointer){
    ::operator delete[](pointer);
}

void Event::operator delete(void* pointer){
    :: delete(pointer);
}

bool Event::operator==(const Event &event) const {
    if(::strcmp(this->title, event.title))
        return false;
    if(this->dateAndTime.date.year == event.dateAndTime.date.year && this->dateAndTime.date.month == event.dateAndTime.date.month && this->dateAndTime.date.day == event.dateAndTime.date.day)
        return true;
    return false;
}

Event& Event::operator=(const Event &event) {
    this->setTitle(event.title);
    this->setDescription(event.description);
    this->setLink(event.link);
    this->setNumberOfPeople(event.numberOfPeople);
    this->setDateAndTime(event.dateAndTime.date.year, event.dateAndTime.date.month, event.dateAndTime.date.day, event.dateAndTime.time.hour, event.dateAndTime.time.minute);
    return *this;
}

dateAndTimeT Event::getDateAndTime() const {
    return this->dateAndTime;
}

char *Event::getTitle() const {
    char* result = new char[100];
    ::strcpy(result, this->title);
    return result;
}

char *Event::getDescription() const {
    char* result = new char[100];
    ::strcpy(result, this->description);
    return result;
}

char *Event::getLink() const {
    char* result = new char[100];
    ::strcpy(result, this->link);
    return result;
}

int Event::getNumberOfPeople() const {
    return this->numberOfPeople;
}

void Event::setDate(int year, int month, int day) {
    this->dateAndTime.date.year = year;
    this->dateAndTime.date.month = month;
    this->dateAndTime.date.day = day;
}

void Event::setTime(int hour, int minute) {
    this->dateAndTime.time.hour = hour;
    this->dateAndTime.time.minute = minute;
}

void Event::setDateAndTime(int year, int month, int day, int hour, int minute) {
    this->setDate(year, month, day);
    this->setTime(hour, minute);
}

void Event::setTitle(char *newTitle) {
    this->title = new char[strlen(newTitle)];
    ::strcpy(this->title, newTitle);
}

void Event::setDescription(char *newDescription) {
    this->description = new char[strlen(newDescription)];
    ::strcpy(this->description, newDescription);
}

void Event::setLink(char *newLink) {
    this->link = new char[strlen(newLink)];
    ::strcpy(this->link, newLink);
}

void Event::setNumberOfPeople(int newNumberOfPeople) {
    this->numberOfPeople = newNumberOfPeople;
}

char* Event::toString() const {
    char* result = new char[200], convertIntegerToArray[10];
    ::strcpy(result, this->title);
    ::strcat(result, ": ");
    ::strcat(result, this->description);
    ::strcat(result, ", date: ");
    itoa(this->getDateAndTime().date.day, convertIntegerToArray, 10);
    ::strcat(result, convertIntegerToArray);
    ::strcat(result, "/");
    itoa(this->getDateAndTime().date.month, convertIntegerToArray, 10);
    ::strcat(result, convertIntegerToArray);
    ::strcat(result, "/");
    itoa(this->getDateAndTime().date.year, convertIntegerToArray, 10);
    ::strcat(result, convertIntegerToArray);
    ::strcat(result, " at ");
    itoa(this->dateAndTime.time.hour, convertIntegerToArray, 10);
    ::strcat(result, convertIntegerToArray);
    ::strcat(result, ":");
    itoa(this->dateAndTime.time.minute, convertIntegerToArray, 10);
    ::strcat(result, convertIntegerToArray);
    ::strcat(result, ", ");
    itoa(this->numberOfPeople, convertIntegerToArray, 10);
    ::strcat(result, convertIntegerToArray);
    ::strcat(result, " attending.\n");
    return result;
}

void Event::testEventDeclaration()
{
    Event event;
    ifstream fin("database.txt");
    char name[50], description[100], link[100];
    int population, year, month, day, hour, minute, numberOfEvents;
    fin>>numberOfEvents;
    fin.get();
    fin.getline(name, 50);
    fin.getline(description, 100);
    fin>>year>>month>>day>>hour>>minute>>population;
    fin.get();
    fin.getline(link, 100);

    event.setTitle(name);
    event.setDescription(description);
    event.setDateAndTime(year, month, day, hour, minute);
    event.setNumberOfPeople(population);
    event.setLink(link);

    assert(::strcmp(event.getTitle(), name) == 0);
    assert(::strcmp(event.getDescription(), description) == 0);
    assert(::strcmp(event.getLink(), link) == 0);
    ::strcat(name, ": ");
    char* convertIntegerToArray = new char[10];
    ::strcat(name, description);
    ::strcat(name, ", date: ");
    itoa(day, convertIntegerToArray, 10);
    ::strcat(name, convertIntegerToArray);
    ::strcat(name, "/");
    itoa(month, convertIntegerToArray, 10);
    ::strcat(name, convertIntegerToArray);
    ::strcat(name, "/");
    itoa(year, convertIntegerToArray, 10);
    ::strcat(name, convertIntegerToArray);
    ::strcat(name, " at ");
    itoa(hour, convertIntegerToArray, 10);
    ::strcat(name, convertIntegerToArray);
    ::strcat(name, ":");
    itoa(minute, convertIntegerToArray, 10);
    ::strcat(name, convertIntegerToArray);
    ::strcat(name, ", ");
    itoa(population, convertIntegerToArray, 10);
    ::strcat(name, convertIntegerToArray);
    ::strcat(name, " attending.\n");
    assert(::strcmp(event.toString(), name) == 0);
    assert(event.getNumberOfPeople() == population);
    assert(event.getDateAndTime().date.year == year);
    assert(event.getDateAndTime().date.month == month);
    assert(event.getDateAndTime().date.day == day);
    assert(event.getDateAndTime().time.hour == hour);
    assert(event.getDateAndTime().time.minute == minute);
    fin.close();
    cout<<"Test Event Declaration\n";
}

bool Event::operator>(const Event &event) const {
    if(this->dateAndTime.date.year > event.dateAndTime.date.year)
        return true;
    else
        if(this->dateAndTime.date.year < event.dateAndTime.date.year)
            return false;
        else
        {
            if(this->dateAndTime.date.month > event.dateAndTime.date.month)
                return true;
            else
                if(this->dateAndTime.date.month < event.dateAndTime.date.month)
                    return false;
                else
                {
                    if(this->dateAndTime.date.day > event.dateAndTime.date.day)
                        return true;
                    else
                        if(this->dateAndTime.date.day < event.dateAndTime.date.day)
                            return false;
                        else
                        {
                            if(this->dateAndTime.time.hour > event.dateAndTime.time.hour)
                                return true;
                            else
                                if(this->dateAndTime.time.hour < event.dateAndTime.time.hour)
                                    return false;
                                else
                                {
                                    if(this->dateAndTime.time.minute > event.dateAndTime.time.minute)
                                        return true;
                                    return false;
                                }
                        }
                }
        }
}

void Event::testEventArray()
{
    Event* events = new Event[20];
    ifstream fin("database.txt");
    char name[50], description[100], link[100];
    int population, year, month, day, hour, minute, nrEvents;
    fin>>nrEvents; fin.get();
    for(int i = 0; i < nrEvents; i++)
    {
        Event event;
        fin.getline(name, 50);
        fin.getline(description, 100);
        fin>>year>>month>>day>>hour>>minute>>population;
        fin.get();
        fin.getline(link, 100);

        event.setTitle(name);
        event.setDescription(description);
        event.setDateAndTime(year, month, day, hour, minute);
        event.setNumberOfPeople(population);
        event.setLink(link);
        events[i] = event;
        assert(events[i] == event);
        if(i > 0)
            assert(!(events[i] == events[i-1]));
    }
    fin.close();
    cout<<"Test Event Array\n";
}