//
// Created by alexi on 5/2/2023.
//

#ifndef A7_915_MICU_ALEXIACLAUDIA_FILEREPOSITORY_H
#define A7_915_MICU_ALEXIACLAUDIA_FILEREPOSITORY_H
#pragma once
#include "repository.h"
#include "fstream"
using namespace std;

class FileRepository: public Repository{
protected:
    string fileName;
private:
    vector<Event> readFromFile();
public:
    virtual void writeToFile();
    FileRepository(string fileName);

    bool add(Event newElement) override;
    bool remove(Event element) override;
    bool update(int index, Event newElement) override;
    bool exist(Event element) override;
    int size() override;
    int get(Event element) override;
    Event getElement(int index) override;
    bool isEmpty() override;
    bool isFull() override;
    vector<Event> getIterator() override;
    vector<Event>& getAll() override;
};


#endif //A7_915_MICU_ALEXIACLAUDIA_FILEREPOSITORY_H
