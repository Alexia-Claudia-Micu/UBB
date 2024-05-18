
//
// Created by alexi on 3/30/2023.
//
#include "administratorService.h"

#include "htmlRepository.h"
#include "csvRepository.h"

using namespace std;

AdministratorService::AdministratorService(Repository* repository, FileRepository fileRepository, string listingMode): repository(repository), eventListing(fileRepository) {
    this->setEventListingType(listingMode);
}


AdministratorService::~AdministratorService() {

}

void AdministratorService::setEventListingType(string listingMode) {
    if(listingMode == "html"){
        HtmlRepository htmlRepository = HtmlRepository("events.txt", "tabelEvents.html");
        this->eventListing = htmlRepository;
    }
    else {
        CSVRepository csvRepository = CSVRepository("events.txt", "eventEntities.csv");
        this->eventListing = csvRepository;
    }
}

void AdministratorService::loadListingOfEventsInFormat() {
    this->eventListing.writeToFile();
}

bool AdministratorService::add(string title, string description, int year, int month, int day, int hour, int minute,
                               int attendees, string link) {
    Event new_event;
    new_event.setTitle(title); new_event.setDescription(description);new_event.setLink(link); new_event.setDateAndTime(year, month, day, hour, minute); new_event.setNumberOfPeople(attendees);
    bool result =  this->repository->add(new_event);
    return result;
}

bool AdministratorService::remove(string title, int year, int month, int day, int hour, int minute) {
    Event new_event;
    new_event.setTitle(title);new_event.setDateAndTime(year, month, day, hour, minute);
    return this->repository->remove(new_event);
}

bool AdministratorService::update(int indexOfElementToUpdate, string newTitle, string newDescription, int newYear, int newMonth, int newDay, int newHour, int newMinute, int newAttendees, string newLink){
    Event new_event, old_event;
    new_event.setTitle(newTitle); new_event.setDateAndTime(newYear, newMonth, newDay, newHour, newMinute); new_event.setNumberOfPeople(newAttendees); new_event.setDescription(newDescription); new_event.setLink(newLink);
    return this->repository->update(indexOfElementToUpdate, new_event);
}

vector<Event> AdministratorService::getIterator() {
    return this->repository->getIterator();
}

Event AdministratorService::getElement(int index) {
    return this->repository->getElement(index);
}

Repository& AdministratorService::getElements() {
    return *this->repository;
}

int AdministratorService::updatePopulation(Event event, int population)
{
    int index = this->repository->get(event), newPopulation = this->repository->getElement(index).getNumberOfPeople() + population;
    event.setNumberOfPeople(newPopulation);
    this->repository->update(index, event);
}
