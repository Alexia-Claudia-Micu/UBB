//
// Created by alexi on 3/29/2023.
//

#ifndef A45_915_MICU_ALEXIACLAUDIA_EVENT_H
#define A45_915_MICU_ALEXIACLAUDIA_EVENT_H
#pragma once
#include "stdlib.h"

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
    char* title;
    char* description;
    dateAndTimeT dateAndTime;
    int numberOfPeople;
    char* link;
public:
    Event();
    //Event(const Event& event);
    void* operator new(size_t size);
    Event& operator=(const Event& event);
    void operator delete[](void* pointer);
    void operator delete(void* pointer);
    void* operator new[] (size_t size);
    bool operator==(const Event& event) const;
    bool operator>(const Event& event) const;
    dateAndTimeT getDateAndTime() const;
    char* getTitle() const;
    char* getDescription() const;
    char* getLink() const;
    int getNumberOfPeople() const;
    void setDate(int year, int month, int day);
    void setTime(int hour, int minute);
    void setDateAndTime(int year, int month, int day, int hour, int minute);
    void setTitle(char* newTitle);
    void setDescription(char* newDescription);
    void setLink(char* newLink);
    void setNumberOfPeople(int newNumberOfPeople);
    char* toString() const;
    void testEventDeclaration();
    void testEventArray();
};

#endif //A45_915_MICU_ALEXIACLAUDIA_EVENT_H
