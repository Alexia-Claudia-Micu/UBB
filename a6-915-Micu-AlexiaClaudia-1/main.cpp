#include <iostream>
#include "administratorService.h"
#include "userService.h"
#include "userInterface.h"
#include "crtdbg.h"
#include <fstream>

using namespace std;

void readInitialValue(AdministratorService &administratorService)
{
    ifstream inputFile("database.txt");
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
        administratorService.add(name, description, year, month, day, hour, minute, population, link);
    }
    inputFile.close();
}

int main()
{
    AdministratorService administratorService = AdministratorService();
    readInitialValue(administratorService);
    UserService userService = UserService(administratorService.getElements());
    UserInterface userInterface = UserInterface(administratorService, userService);
    userInterface.menu();
    cout<<"\n";
    userService.runUserTests();
    administratorService.runTests();
    administratorService.getElements().repositoryTests();
    cout<<"Tests successful\n";
    printf("\nResult of memory dumps: %d\n", _CrtDumpMemoryLeaks());
    return 0;
}
