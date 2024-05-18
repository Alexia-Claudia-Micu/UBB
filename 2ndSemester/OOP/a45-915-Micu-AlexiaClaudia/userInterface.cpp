//
// Created by alexi on 4/2/2023.
//
#include "userInterface.h"
#include <iostream>
#include "services.h"
#include "userService.h"
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#include "dynamicArrayIterator.h"

using namespace std;


UserInterface::UserInterface(AdministratorService &administratorService1, UserService &userService1): administratorService(administratorService1),
                                                                                                      userService(userService1){

}

void UserInterface::menu()
{
    int command = 1;
    while (command != 0)
    {
        cout<<"\n1. Administrator mode\n2. User mode.\n0. Quit\nCommand>";
        cin>>command;
        char title[50], description[100], link[100];
        int attendees, year, month, day, hour, minute;
        switch (command) {
            case 1: {
                cout << "\n1.Add an event.\n2.Remove and event.\n3.Update an event.\n4.Print the events.\nChoice>";
                int choice;
                cin >> choice;
                switch (choice) {
                    case 1: {
                        cout << "\nGive title>";
                        cin.get();
                        cin.getline(title, 50);
                        cout << "\nGive description>";
                        cin.getline(description, 50);
                        cout << "\nGive link>";
                        cin.getline(link, 50);
                        cout << "\nGive number of attendees>";
                        cin >> attendees;
                        cout << "\nGive year, month and day>";
                        cin >> year >> month >> day;
                        cout << "\nGive hour and minute>";
                        cin >> hour >> minute;
                        bool addResult = this->administratorService.add(title, description, year, minute, day, hour, minute, attendees,
                                                                  link);
                        if (!addResult)
                            cout << "\nAddition unsuccessful.\n";
                        break;
                    }
                    case 2: {
                        cout << "\nGive title>";
                        cin.get();
                        cin.getline(title, 50);
                        cout << "\nGive year, month and day>";
                        cin >> year >> month >> day;
                        cout << "\nGive hour and minute>";
                        cin >> hour >> minute;

                        bool removeResult = this->administratorService.remove(title, year, month, day, hour, minute);
                        if (!removeResult)
                            cout << "\nRemoval not successful.\n";
                        break;
                    }
                    case 3: {
                        cout << "\nGive title of event to update>";
                        cin.get();
                        cin.getline(title, 50);
                        cout << "\nGive year, month and day of event to update>";
                        cin >> year >> month >> day;
                        cout << "\nGive hour and minute of event to update>";
                        cin >> hour >> minute;

                        char newTitle[50], newDescription[100], newLink[100];
                        int newYear, newMonth, newDay, newHour, newMinute, newAttendees;
                        cout << "\nGive new title>";
                        cin.get();
                        cin.getline(newTitle, 50);
                        cout << "\nGive new description>";
                        cin.getline(newDescription, 50);
                        cout << "\nGive new link>";
                        cin.getline(newLink, 50);
                        cout << "\nGive new number of attendees>";
                        cin >> newAttendees;
                        cout << "\nGive new year, month and day>";
                        cin >> newYear >> newMonth >> newDay;
                        cout << "\nGive new hour and minute>";
                        cin >> newHour >> newMinute;
                        bool updateResult = this->administratorService.update(title, newTitle, newDescription, year, month, day, hour,
                                                                        minute, newYear, newMonth, newDay, newHour, newMinute,
                                                                        newAttendees, newLink);
                        if (!updateResult)
                            cout << "\nUpdate unsuccessful.\n";
                        break;
                    }
                    case 4: {
                        DynamicArrayIterator<Event> iterateEvents = this->administratorService.iterator();
                        int index = 0;
                        iterateEvents.first();
                        cout << '\n';
                        while (iterateEvents.valid()) {
                            cout << ++index << ". " << iterateEvents.getCurrent().toString();
                            iterateEvents.next();
                        }
                        cout << '\n';
                        break;
                    }
                    default: {
                        cout << "\nIncorrect command. Try again>";
                        break;
                    }
                }
                break;
            }
            case 2: {
                cout << "\n1. Print all events in a given month.\n";
                cout << "\n2. Delete an event from the user's list.\n";
                cout << "\n3. Show the list of events the user wants to attend.\n";
                int choice;
                cin >> choice;
                switch (choice) {
                    case 1:{
                        cout << "\nGive month>";
                        cin >> month;
                        DynamicArrayIterator<Event> arrayIterator = this->userService.getEventsChronologicallyForAMonth(month);
                        arrayIterator.first();
                        while(arrayIterator.valid())
                        {
                            Event eventToPrint = arrayIterator.getCurrent();
                            cout <<'\n'<<eventToPrint.toString();
                            ShellExecuteA(NULL, NULL, "chrome.exe", eventToPrint.getLink(), NULL, SW_SHOWMAXIMIZED);
                            ::system("pause");
                            arrayIterator.next();
                            cout<<"Do you find this event interesting? 1 for yes, 2 for no.";
                            int addEventChoice;
                            cin>>addEventChoice;
                            if(addEventChoice == 1) {
                                if(this->userService.addEvent(eventToPrint)) {
                                    this->administratorService.updatePopulation(eventToPrint, 1);
                                    break;
                                } else
                                    cout<<"\nThis event has already been added.\n";
                            } else{
                                if(!arrayIterator.valid()) {
                                    cout<<"\nThe list has ended, do you want to reshow it? 1 for yes, 2 for no >";
                                    cin>>addEventChoice;
                                    if(addEventChoice == 1)
                                        arrayIterator.first();
                                }
                            }
                        }
                        break;
                    }
                    case 2:{
                        DynamicArrayIterator<Event> arrayIterator = this->userService.getListOfUserEvents();
                        arrayIterator.first();
                        int eventNumber = 1;
                        while(arrayIterator.valid())
                        {
                            Event eventToPrint = arrayIterator.getCurrent();
                            cout <<eventNumber++<<": "<<eventToPrint.toString();
                            arrayIterator.next();
                        }
                        cout<<"Which event do you want to remove >";
                        int eventIndex;
                        cin>>eventIndex;
                        if(eventIndex > eventNumber - 1 || eventIndex < 0)
                            cout<<"\nCannot remove event.\n";
                        else
                        {
                            Event eventToRemoveUserFrom = this->userService.removeEvent(eventIndex - 1);
                            this->administratorService.updatePopulation(eventToRemoveUserFrom, -1);
                            cout<<"\nRemove successful.\n";
                        }
                        break;
                    }
                    case 3:{
                        DynamicArrayIterator<Event> arrayIterator = this->userService.getListOfUserEvents();
                        arrayIterator.first();
                        int eventNumber = 1;
                        while(arrayIterator.valid())
                        {
                            Event eventToPrint = arrayIterator.getCurrent();
                            cout <<eventNumber++<<": "<<eventToPrint.toString();
                            arrayIterator.next();
                        }
                        break;
                    }
                }
                break;
            }
            default:
                return;
        }
    }
}