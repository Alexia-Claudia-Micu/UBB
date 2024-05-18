//
// Created by alexi on 4/11/2023.
//

#ifndef A45_915_MICU_ALEXIACLAUDIA_REPOSITORY_H
#define A45_915_MICU_ALEXIACLAUDIA_REPOSITORY_H
#pragma once
#include <utility>
#include "event.h"
#include <exception>
#include "assert.h"
#include "vector"
#include <bits/stdc++.h>
#include "exceptions.h"

using namespace std;

class Repository {
protected:
    vector<Event> elements;
public:
    Repository() {
        this->elements.reserve(50);
    }

    ~Repository() {
        this->elements.clear();
    }

    virtual bool add(Event newElement) {
        if (this->exist(newElement) != false)
            throw ExceptionsRepository("The given product already exists!");
        this->elements.push_back(newElement);
        return true;
    }

    virtual bool remove(Event element) {
        if (this->exist(element) == false)
            throw ExceptionsRepository("The given product does not exist!");
        for (auto i = this->elements.begin(); i != this->elements.end(); ++i) {
            if (*i == element) {
                this->elements.erase(i);
                return true;
            }
        }
    }

    virtual bool exist(Event element) {
        auto foundElement = find(this->elements.begin(), this->elements.end(), element);
        if (foundElement == this->elements.end())
            return false;
        return true;
    }

    virtual bool update(int index, Event newElement) {
        if (index < 0 || index >= this->elements.size())
            throw ExceptionsRepository("Update: Index of element does not exist!");
        this->elements.at(index) = newElement;
        return true;
    }

    virtual int size() {
        return this->elements.size();
    }

    virtual int get(Event element) {
        if (exist(element) == false)
            return -1;
        auto foundElementIndex = find(this->elements.begin(), this->elements.end(), element);
        return distance(this->elements.begin(), foundElementIndex);
    }

    virtual Event getElement(int index) {
        Event element = Event();
        if (index >= this->elements.size() || index < 0)
            return element;
        return this->elements.at(index);
    }

    virtual bool isEmpty() {
        return this->elements.size() == 0;
    }

    virtual bool isFull() {
        return this->elements.size() == this->elements.capacity();
    }

    virtual vector<Event> getIterator() {
        return this->elements;
    }

    virtual vector<Event> &getAll() {
        return this->elements;
    }
};

class FakeRepository: public Repository{
public:
    static bool addReturnValue;
    void setAddReturnValue(bool newValue) {
        addReturnValue = newValue;
    }
    FakeRepository() {};
    ~FakeRepository(){};
    bool add(Event newElement) override{return this->addReturnValue;}

};
#endif //A45_915_MICU_ALEXIACLAUDIA_REPOSITORY_H
