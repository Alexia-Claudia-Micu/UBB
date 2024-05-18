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
#include "assert.h"
#include <bits/stdc++.h>

using namespace std;

class Repository{
private:

    vector<Event> elements;

    void resize(){
        this->elements.reserve(this->elements.capacity()*2);
    }
public:
    Repository(int capacity){
        this->elements.reserve(capacity);
    }
    ~Repository(){
        this->elements.clear();
    }
    bool add(Event newElement) {
        if(this->exist(newElement) != false)
            return false;
        if(this->elements.capacity() == this->elements.size())
            this->resize();
        this->elements.push_back(newElement);
        return true;
    }
    bool remove(Event element) {
        if (this->exist(element) == false)
            return false;
        for(auto i = this->elements.begin(); i != this->elements.end(); ++i) {
            if (*i == element) {
                this->elements.erase(i);
                return true;
            }
        }
    }
    bool exist(Event element) {
        auto foundElement = find(this->elements.begin(), this->elements.end(), element);
        if(foundElement == this->elements.end())
            return false;
        return true;
    }
    bool update(int index, Event newElement){
        if(index < 0 || index >= this->elements.size())
            return false;
        this->elements.at(index) = newElement;
        return true;
    }
    int size() const{
        return this->elements.size();
    }
    int get(Event element) {
        if(exist(element) == false)
            return -1;
        auto foundElementIndex = find(this->elements.begin(), this->elements.end(), element);
        return distance(this->elements.begin(), foundElementIndex);
    }
    Event getElement(int index) const{
        Event element = Event();
        if(index >= this->elements.size() || index < 0)
            return element;
        return this->elements.at(index);
    }
    bool isEmpty() const {
        return this->elements.size() == 0;
    }
    bool isFull() const {
        return this->elements.size() == this->elements.capacity();
    }
    vector<Event> getIterator(){
        return this->elements;
    }
    vector<Event>& getAll(){
        return this->elements;
    }
    void repositoryTests(){
        Repository repository = Repository(2);
        Event event1, event2, event3, event4;
        event4 = Event();
        event1.setTitle("event1");
        event2.setTitle("e2"); event2.setDescription("d2"); event2.setDateAndTime(2000, 1, 1, 1, 1);
        event3.setTitle("event3");
        assert(repository.exist(event2) == false);
        assert(repository.add(event2) == true);
        assert(repository.isEmpty() == false);
        assert(repository.add(event2) == false);
        assert(repository.exist(event2) == true);
        assert(repository.remove(event1) == false);
        assert(repository.remove(event2) == true);
        assert(repository.isEmpty() == true);
        repository.add(event2);
        assert(repository.update(0, event3) == true);
        assert(repository.update(-3, event3) == false);
        assert(repository.size() == 1);
        assert(repository.get(event3) == 0);
        assert(repository.get(event1) == -1);
    }
};
#endif //A45_915_MICU_ALEXIACLAUDIA_REPOSITORY_H
