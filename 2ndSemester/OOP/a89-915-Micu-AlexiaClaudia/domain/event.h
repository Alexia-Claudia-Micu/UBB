//
// Created by alexi on 3/29/2023.
//

#ifndef A45_915_MICU_ALEXIACLAUDIA_EVENT_H
#define A45_915_MICU_ALEXIACLAUDIA_EVENT_H
#pragma once
#include "stdlib.h"
#define LINK_LENGTH 100
#define DESCRIPTION_LENGTH 100
#define TITLE_LENGTH 50
#define STRING_LENGTH 200
#define ATOI_LENGTH 10
#define EVENT_ARRAY_LENGTH 20
#define INITIAL_CAPACITY
#include <cstring>
#include "string"

using namespace std;

struct dateT{
    int year, month, day;
};
struct timeT{
    int hour, minute;
};
struct dateAndTimeT{
    dateT date;
    timeT time;
};

class Event{
private:
    string title;
    string description;
    dateAndTimeT dateAndTime;
    int numberOfPeople;
    string link;
public:
    Event();
    //Event(const Event& event);
    void* operator new(size_t size);
    Event& operator=(const Event& event);
    void operator delete(void* pointer);
    void* operator new[] (size_t size);
    bool operator==(const Event& event) const;
    bool operator>(const Event& event) const;
    bool operator<(const Event& event) const;
    dateAndTimeT getDateAndTime() const;
    string getTitle() const;
    string getDescription() const;
    string getLink() const;
    int getNumberOfPeople() const;
    void setDate(int year, int month, int day);
    void setTime(int hour, int minute);
    void setDateAndTime(int year, int month, int day, int hour, int minute);
    void setTitle(string newTitle);
    void setDescription(string newDescription);
    void setLink(string newLink);
    void setNumberOfPeople(int newNumberOfPeople);
    string toString() const;
    void testEventDeclaration();
    void testEventArray();
};

#endif //A45_915_MICU_ALEXIACLAUDIA_EVENT_H
