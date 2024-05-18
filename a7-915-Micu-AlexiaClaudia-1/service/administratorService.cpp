//
// Created by alexi on 3/30/2023.
//
#include "administratorService.h"

#include "htmlRepository.h"
#include "csvRepository.h"

using namespace std;

AdministratorService::AdministratorService(FileRepository fileRepository, string listingMode): repository(fileRepository), eventListing(fileRepository) {
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

bool AdministratorService::add(char* title, char* description, int year, int month, int day, int hour, int minute, int atendees, char* link)
{
    Event new_event;
    new_event.setTitle(title); new_event.setDescription(description);new_event.setLink(link); new_event.setDateAndTime(year, month, day, hour, minute); new_event.setNumberOfPeople(atendees);
    bool result =  this->repository.add(new_event);
    return result;
}

bool AdministratorService::remove(char* title, int year, int month, int day, int hour, int minute)
{
    Event new_event;
    new_event.setTitle(title);new_event.setDateAndTime(year, month, day, hour, minute);
    return this->repository.remove(new_event);
}

bool AdministratorService::update(char *initialTitle, char *newTitle, char *newDescription, int initialYear, int initialMonth, int initialDay, int initialHour, int initialMinute, int newYear, int newMonth, int newDay, int newHour, int newMinute, int newAtendees,
                                  char *newLink) {
    Event new_event, old_event;
    old_event.setTitle(initialTitle); old_event.setDateAndTime(initialYear, initialMonth, initialDay, initialHour, initialMinute);
    int indexOfElementToUpdate = this->repository.get(old_event);
    new_event.setTitle(newTitle); new_event.setDateAndTime(newYear, newMonth, newDay, newHour, newMinute); new_event.setNumberOfPeople(newAtendees); new_event.setDescription(newDescription); new_event.setLink(newLink);
    return this->repository.update(indexOfElementToUpdate, new_event);
}

vector<Event> AdministratorService::getIterator() {
    return this->repository.getIterator();
}

Event AdministratorService::getElement(int index) {
    return this->repository.getElement(index);
}

Repository& AdministratorService::getElements() {
    return this->repository;
}

int AdministratorService::updatePopulation(Event event, int population)
{
    int index = this->repository.get(event), newPopulation = this->repository.getElement(index).getNumberOfPeople() + population;
    event.setNumberOfPeople(newPopulation);
    this->repository.update(index, event);
}

#include "assert.h"
#include "cstring"
#include "iostream"
void administratorServiceTests(){
    FileRepository repository = FileRepository("null.txt");
    AdministratorService administratorService = AdministratorService(repository, "html");
    Event event1, event2, event3;
    event1.setTitle("event1");
    event2.setTitle("e2"); event2.setDescription("d2"); event2.setDateAndTime(2000, 1, 1, 1, 1);
    event3.setTitle("event3");
    assert(administratorService.add("e1", "d1", 2000, 1, 1, 1, 1, 1, "l1") == 1);
    //assert(administratorService.add("e1", "d1", 2000, 1, 1, 1, 1, 1, "l1") == 0);
    //assert(administratorService.remove("e2", 2000, 1, 1, 1, 1) == 0);
    assert(administratorService.add("e2", "d2", 2000, 1, 1, 1, 1, 1, "l2") == 1);
    assert(administratorService.remove("e2", 2000, 1, 1, 1, 1) == 1);
    assert(administratorService.update("e1", "e3","d3", 2000, 1, 1, 1, 1, 2020, 1, 1, 1, 1, 20, "l3"));
    assert(administratorService.add("e2", "d2", 2000, 1, 1, 1, 1, 1, "l2") == 1);
    assert(administratorService.updatePopulation(event2, 3) == 1);
    assert(administratorService.getElement(1).getNumberOfPeople() == 4);
    assert(::strcmp(administratorService.getElement(0).getTitle(), "e3") == 0);
    vector<Event> iterator = administratorService.getIterator();
    assert(iterator.size() == 2);
    cout<<"Test Administrator Service successful\n";
}

void AdministratorService::runTests(){
    Event event;
    event.testEventArray();
    event.testEventDeclaration();
    administratorServiceTests();
}