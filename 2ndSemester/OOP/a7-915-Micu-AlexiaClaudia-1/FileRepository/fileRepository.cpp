//
// Created by alexi on 5/2/2023.
//

#include "fileRepository.h"
#include "exceptions.h"
#define INITIAL_CAPACITY 20

FileRepository::FileRepository( string fileName) {
    this->fileName = fileName;
    this->elements.reserve(INITIAL_CAPACITY);
    this->elements = readFromFile();
}

vector<Event> FileRepository::readFromFile() {
    ifstream inputFile(this->fileName);
    vector<Event> events;
    char name[TITLE_LENGTH], description[DESCRIPTION_LENGTH], link[LINK_LENGTH];
    int population, year, month, day, hour, minute, numberOfEvents;
    inputFile >> numberOfEvents;
    inputFile.get();
    for(int i = 0; i < numberOfEvents; i++)
    {
        inputFile.getline(name, TITLE_LENGTH);
        inputFile.getline(description, DESCRIPTION_LENGTH);
        inputFile >> year >> month >> day >> hour >> minute >> population;
        inputFile.get();
        inputFile.getline(link, LINK_LENGTH);
        Event newEvent;
        newEvent.setDescription(description);newEvent.setLink(link); newEvent.setTitle(name);newEvent.setNumberOfPeople(population); newEvent.setDateAndTime(year, month,day, hour, minute);
        events.push_back(newEvent);
    }
    inputFile.close();
    return events;
}

void FileRepository::writeToFile() {
    ofstream outputFile(this->fileName);
    outputFile << this->elements.size() <<'\n';
    for(int i = 0; i < this->elements.size(); i++)
    {
        outputFile<< this->elements.at(i).getTitle()<<'\n';
        outputFile<< this->elements.at(i).getDescription()<<'\n';
        outputFile<< this->elements.at(i).getDateAndTime().date.year<<" "<<this->elements.at(i).getDateAndTime().date.month<<" "<<this->elements.at(i).getDateAndTime().date.day<<" "<<this->elements.at(i).getDateAndTime().time.hour<<" "<<this->elements.at(i).getDateAndTime().time.minute<<" "<<this->elements.at(i).getNumberOfPeople()<<'\n';
        outputFile<< this->elements.at(i).getLink()<<'\n';
    }
    outputFile.close();
}

bool FileRepository::add(Event newElement) {
    this->elements = readFromFile();
    if(this->exist(newElement))
        throw ExceptionsRepository("The given product already exists!");
    this->elements.push_back(newElement);
    this->writeToFile();
    return true;
}

bool FileRepository::update(int index, Event newElement) {
    this->elements = readFromFile();
    if(index < 0 || index >= this->elements.size())
        throw ExceptionsRepository("Update: Index of element does not exist!");
    this->elements.at(index) = newElement;
    this->writeToFile();
    return true;
}

bool FileRepository::remove(Event element) {
    this->elements = readFromFile();
    if (!this->exist(element))
        throw ExceptionsRepository("The given product does not exist!");
    for(auto i = this->elements.begin(); i != this->elements.end(); ++i) {
        if (*i == element) {
            this->elements.erase(i);
            this->writeToFile();
            return true;
        }
    }
}

vector<Event> &FileRepository::getAll() {
    this->elements = readFromFile();
    return this->elements;
}

vector<Event> FileRepository::getIterator() {
    this->elements = readFromFile();
    return this->elements;
}

bool FileRepository::isFull() {
    this->elements = readFromFile();
    return this->elements.size() == this->elements.capacity();
}

bool FileRepository::isEmpty() {
    this->elements = readFromFile();
    return this->elements.size() == 0;
}

Event FileRepository::getElement(int index) {
    this->elements = readFromFile();
    Event element = Event();
    if(index >= this->elements.size() || index < 0)
        return element;
    return this->elements.at(index);
}

int FileRepository::get(Event element) {
    this->elements = readFromFile();
    if(exist(element) == false)
        return -1;
    auto foundElementIndex = find(this->elements.begin(), this->elements.end(), element);
    return distance(this->elements.begin(), foundElementIndex);
}

int FileRepository::size() {
    this->elements = readFromFile();
    return this->elements.size();
}

bool FileRepository::exist(Event element) {
    this->elements = readFromFile();

    auto foundElement = find(this->elements.begin(), this->elements.end(), element);
    if(foundElement == this->elements.end())
        return false;
    return true;
}


