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
#include <algorithm>

using namespace std;

Event::Event() {
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

void Event::operator delete(void* pointer){
    :: delete(pointer);
}

bool Event::operator==(const Event &event) const {
    if(this->title.compare(event.title))
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

string Event::getTitle() const {
    return this->title;
}

string Event::getDescription() const {
    return this->description;
}

string Event::getLink() const {
    return this->link;
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

void Event::setTitle(string newTitle) {
    this->title = newTitle;
}

void Event::setDescription(string newDescription) {
    this->description = newDescription;
}

void Event::setLink(string newLink) {
    this->link = newLink;
}

void Event::setNumberOfPeople(int newNumberOfPeople) {
    this->numberOfPeople = newNumberOfPeople;
}

string Event::toString() const {
    string result, convertIntegerToArray;
    result = this->title + ": " + this->description + ", date: ";
    result += to_string(this->getDateAndTime().date.day) + "/";
    result += to_string(this->getDateAndTime().date.month) + "/";
    result += to_string(this->getDateAndTime().date.year) + " at ";
    result += to_string(this->getDateAndTime().time.hour) + ":";
    result += to_string(this->getDateAndTime().time.minute) + ", ";
    result += to_string(this->getNumberOfPeople()) + " attending.\n";
    return result;
}

bool Event::operator<(const Event &event) const{
    return !(*this > event);
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
