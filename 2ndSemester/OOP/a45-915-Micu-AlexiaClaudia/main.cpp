#include <iostream>
#include "services.h"
#include "userService.h"
#include "userInterface.h"
#include <fstream>

using namespace std;

void readInitialValues(AdministratorService &administratorService)
{
    ifstream inputFile("database.txt");
    char name[50], description[100], link[100];
    int population, year, month, day, hour, minute, nrEvents;
    inputFile >> nrEvents;
    inputFile.get();
    for(int i = 0; i < nrEvents; i++)
    {
        inputFile.getline(name, 50);
        inputFile.getline(description, 100);
        inputFile >> year >> month >> day >> hour >> minute >> population;
        inputFile.get();
        inputFile.getline(link, 100);
        administratorService.add(name, description, year, month, day, hour, minute, population, link);
    }
    inputFile.close();
}

int main()
{
    AdministratorService administratorService = AdministratorService();
    readInitialValues(administratorService);
    UserService userService = UserService(administratorService.getDynamicArray());
    UserInterface userInterface = UserInterface(administratorService, userService);
    userInterface.menu();
    return 0;
}
