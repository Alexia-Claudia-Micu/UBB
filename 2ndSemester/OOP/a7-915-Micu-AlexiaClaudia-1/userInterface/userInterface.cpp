//
// Created by alexi on 4/2/2023.
//
#include "userInterface.h"
#include <iostream>
#include "administratorService.h"
#include "userService.h"
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#define ADMINISTRATOR_SERVICE_OPTION 1
#define USER_SERVICE_OPTION 2
#define QUIT_COMMAND 0
#define ADD_TO_MAIN_REPOSITORY 1
#define SHOW_EVENTS_AND_ADD_TO_USER 1
#define REMOVE_FROM_REPOSITORY 2
#define REMOVE_FROM_USER_EVENTS 2
#define PRINT_USER_EVENTS 3
#define PRINT_ALL_EVENTS 4
#define UPDATE_AN_EVENT 3
#define DEFAULT_COMMAND 1
#define SHOW_LIST_CHOICE 5

using namespace std;


UserInterface::UserInterface(AdministratorService &administratorService1, UserService &userService1, string listMode): administratorService(administratorService1),
userService(userService1){
    this->listingMode = listMode;
}

UserInterface::~UserInterface() {
}
string readListingMode() {
    string buffer;
    cout<<"Choose a listing mode (html or csv) >";
    cin>>buffer;
    bool isValid = 0;
    while(!isValid){
        try{
            isValid = 1;
            Validator::validateListingMode(buffer);
        }
        catch(ExceptionsValidator& exceptionsValidator){
            cout<<"\nTry again >";
            cin>>buffer;
            isValid = 0;
        }
    }
    return buffer;
}

void UserInterface::menu()
{
    int command = DEFAULT_COMMAND;
    while (command != QUIT_COMMAND)
    {
        cout<<"\n1. Administrator mode\n2. User mode.\n0. Quit\nCommand>";
        cin>>command;
        char title[TITLE_LENGTH], description[DESCRIPTION_LENGTH], link[LINK_LENGTH];
        int attendees, year, month, day, hour, minute;
        switch (command) {
            case ADMINISTRATOR_SERVICE_OPTION: {
                cout << "\n1.Add an event.\n2.Remove an event.\n3.Update an event.\n4.Print the events.\n5.Show events listed.\nChoice>";
                int choice;
                cin >> choice;
                switch (choice) {
                    case ADD_TO_MAIN_REPOSITORY: {
                        cout << "\nGive title>";
                        cin.get();
                        cin.getline(title, TITLE_LENGTH);
                        cout << "\nGive description>";
                        cin.getline(description, DESCRIPTION_LENGTH);
                        cout << "\nGive link>";
                        cin.getline(link, LINK_LENGTH);
                        cout << "\nGive number of attendees>";
                        cin >> attendees;
                        cout << "\nGive year, month and day>";
                        cin >> year >> month >> day;
                        cout << "\nGive hour and minute>";
                        cin >> hour >> minute;
                        try {
                            Validator::validateEventTitle(title);
                            Validator::validateEventDescription(description);
                            Validator::validateEventLink(link);
                            Validator::validateEventPopulation(attendees);
                            Validator::validateEventYear(year);
                            Validator::validateEventMonth(month);
                            Validator::validateEventDay(day);
                            Validator::validateEventHour(hour);
                            Validator::validateEventMinute(minute);
                        }
                        catch (ExceptionsValidator){
                            cout<<"Invalid input!\n";
                            break;
                        }
                        try {
                            bool addResult = this->administratorService.add(title, description, year, minute, day, hour,
                                                                            minute, attendees,
                                                                            link);
                        }
                        catch (ExceptionsRepository){
                            cout << "\nAddition unsuccessful.\n";
                        }
                        break;
                    }
                    case REMOVE_FROM_REPOSITORY: {
                        try {
                            cout << "\nGive title>";
                            cin.get();
                            cin.getline(title, TITLE_LENGTH);
                            Validator::validateEventTitle(title);
                            cout << "\nGive year, month and day>";
                            cin >> year >> month >> day;
                            Validator::validateEventYear(year);
                            Validator::validateEventMonth(month);
                            Validator::validateEventDay(day);
                            cout << "\nGive hour and minute>";
                            cin >> hour >> minute;
                            Validator::validateEventHour(hour);
                            Validator::validateEventMinute(minute);
                        }
                        catch (ExceptionsValidator){
                            cout<<"Invalid input!\n";
                            break;
                        }
                        try {
                            bool removeResult = this->administratorService.remove(title, year, month, day, hour,
                                                                                  minute);
                        }
                        catch (ExceptionsRepository){
                            cout<<"Removal unsuccessful!\n";
                        }
                        break;
                    }
                    case UPDATE_AN_EVENT: {
                        cout << "\nGive title of event to update>";
                        cin.get();
                        cin.getline(title, TITLE_LENGTH);
                        cout << "\nGive year, month and day of event to update>";
                        cin >> year >> month >> day;
                        cout << "\nGive hour and minute of event to update>";
                        cin >> hour >> minute;
                        try {
                            Validator::validateEventTitle(title);
                            Validator::validateEventYear(year);
                            Validator::validateEventMonth(month);
                            Validator::validateEventDay(day);
                            Validator::validateEventHour(hour);
                            Validator::validateEventMinute(minute);
                        }
                        catch (ExceptionsValidator){
                            cout<<"Invalid input!\n";
                            break;
                        }

                        char newTitle[TITLE_LENGTH], newDescription[DESCRIPTION_LENGTH], newLink[LINK_LENGTH];
                        int newYear, newMonth, newDay, newHour, newMinute, newAttendees;
                        cout << "\nGive new title>";
                        cin.get();
                        cin.getline(newTitle, TITLE_LENGTH);
                        cout << "\nGive new description>";
                        cin.getline(newDescription, DESCRIPTION_LENGTH);
                        cout << "\nGive new link>";
                        cin.getline(newLink, LINK_LENGTH);
                        cout << "\nGive new number of attendees>";
                        cin >> newAttendees;
                        cout << "\nGive new year, month and day>";
                        cin >> newYear >> newMonth >> newDay;
                        cout << "\nGive new hour and minute>";
                        cin >> newHour >> newMinute;
                        try{
                            Validator::validateEventTitle(newTitle);;
                            Validator::validateEventDescription(newDescription);
                            Validator::validateEventLink(newLink);
                            Validator::validateEventPopulation(newAttendees);
                            Validator::validateEventYear(newYear);
                            Validator::validateEventMonth(newMonth);
                            Validator::validateEventDay(newDay);
                            Validator::validateEventHour(newHour);
                            Validator::validateEventMinute(newMinute);
                        }
                        catch (ExceptionsValidator){
                            cout<<"Invalid input!\n";
                            break;
                        }
                        try {
                            bool updateResult = this->administratorService.update(title, newTitle, newDescription, year,
                                                                                  month, day, hour,
                                                                                  minute, newYear, newMonth, newDay,
                                                                                  newHour, newMinute, newAttendees,
                                                                                  newLink);
                        }
                        catch (ExceptionsRepository){
                            cout << "\nUpdate unsuccessful.\n";
                        }
                        break;
                    }
                    case PRINT_ALL_EVENTS: {
                        vector<Event> eventsToIterate = this->administratorService.getIterator();
                        //for_each(eventsToIterate.begin(), eventsToIterate.end(), print);
                        int eventNumber = 1;
                        cout << '\n';
                        for(auto iterator = eventsToIterate.begin(); iterator != eventsToIterate.end(); iterator++, eventNumber++) {
                            cout << eventNumber << ". " << (*iterator).toString();
                        }
                        cout << '\n';
                        break;
                    }
                    case SHOW_LIST_CHOICE:{
                        this->administratorService.loadListingOfEventsInFormat();
                        if(this->listingMode == "html"){
                            std::string url = R"(C:\Users\alexi\Documents\GitHub\a7-915-Micu-AlexiaClaudia-1\cmake-build-debug\tabelEvents.html)"; // Replace with the actual file path
                            std::string command = "start chrome " + url;
                            system(command.c_str());
                        }
                        else{
                            std::string file_path = "C:\\Users\\alexi\\Documents\\GitHub\\a7-915-Micu-AlexiaClaudia-1\\cmake-build-debug\\eventEntities.csv"; // Replace with the actual file path
                            std::string command = "start excel.exe " + file_path;
                            system(command.c_str());
                        }
                        break;
                    }
                    default: {
                        cout << "\nIncorrect command. Try again>";
                        break;
                    }
                }
                break;
            }
            case USER_SERVICE_OPTION: {
                cout << "\n1. Print all events in a given month.\n";
                cout << "\n2. Delete an event from the user's list.\n";
                cout << "\n3. Show the list of events the user wants to attend.\n";
                int choice;
                cout << "\nChoose a command >";
                cin >> choice;
                switch (choice) {
                    case SHOW_EVENTS_AND_ADD_TO_USER:{
                        cout << "\nGive month>";
                        cin >> month;
                        try {
                            Validator::validateEventMonth(month);
                        }
                        catch (ExceptionsValidator){
                            cout<<"Invalid input!\n";
                            break;
                        }
                        vector<Event> eventsToIterate = this->userService.getEventsChronologicallyForAMonth(month);
                        for(auto iterator = eventsToIterate.begin(); iterator != eventsToIterate.end(); iterator++)
                        {
                            cout <<'\n'<<(*iterator).toString();
                            ShellExecuteA(NULL, NULL, "chrome.exe", (*iterator).getLink(), NULL, SW_SHOWMAXIMIZED);
                            ::system("pause");
                            cout<<"Do you find this event interesting? 1 for yes, 2 for no.";
                            int addEventChoice;
                            cin>>addEventChoice;
                            if(addEventChoice == 1) {
                                if(this->userService.addEvent((*iterator))) {
                                    this->administratorService.updatePopulation((*iterator), 1);
                                    break;
                                } else
                                    cout<<"\nThis event has already been added.\n";
                            } else{
                                if(iterator+1 == eventsToIterate.end()) {
                                    cout<<"\nThe list has ended, do you want to reshow it? 1 for yes, 2 for no >";
                                    cin>>addEventChoice;
                                    if(addEventChoice == 1)
                                        iterator = eventsToIterate.begin();
                                }
                            }
                        }
                        break;
                    }
                    case REMOVE_FROM_USER_EVENTS:{
                        vector<Event> eventsToIterate = this->userService.getListOfUserEvents();
                        int eventNumber = 1;
                        for(auto iterator = eventsToIterate.begin(); iterator != eventsToIterate.end(); iterator++)
                        {
                            Event eventToPrint = *iterator;
                            cout <<eventNumber++<<": "<<eventToPrint.toString();
                        }
                        cout<<"Which event do you want to remove >";
                        int eventIndex;
                        cin>>eventIndex;
                        if(eventIndex > eventNumber - 1 || eventIndex < 0)
                            throw ExceptionsValidator("Invalid index!");
                        else
                        {
                            Event eventToRemoveUserFrom = this->userService.removeEvent(eventIndex - 1);
                            this->administratorService.updatePopulation(eventToRemoveUserFrom, -1);
                            cout<<"\nRemove successful.\n";
                        }
                        break;
                    }
                    case PRINT_USER_EVENTS:{
                        vector<Event> eventsToIterate = this->userService.getListOfUserEvents();
                        int eventNumber = 1;
                        for(auto iterator = eventsToIterate.begin(); iterator != eventsToIterate.end(); iterator++)
                        {
                            Event eventToPrint = (*iterator);
                            cout <<eventNumber++<<": "<<eventToPrint.toString();
                        }
                        break;
                    }
                }
                break;
            }
            case QUIT_COMMAND: return;
            default:
                cout<<"\nOption does not exist.\n";
        }
    }
}