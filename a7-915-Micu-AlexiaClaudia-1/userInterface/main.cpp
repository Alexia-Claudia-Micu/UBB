#include <iostream>
#include "administratorService.h"
#include "userService.h"
#include "userInterface.h"
#include "crtdbg.h"
#include <fstream>

using namespace std;

int main()
{
    FileRepository repository = FileRepository("events.txt");
    string listMode = readListingMode();
    AdministratorService administratorService = AdministratorService(repository, listMode);
    //readInitialValue(administratorService);
    UserService userService = UserService(administratorService.getElements());
    UserInterface userInterface = UserInterface(administratorService, userService, listMode);
    userInterface.menu();
    cout<<"\n";
    //userService.runUserTests();
    //administratorService.runTests();
    //administratorService.getElements().repositoryTests();
    cout<<"Tests successful\n";
    printf("\nResult of memory dumps: %d\n", _CrtDumpMemoryLeaks());
    return 0;
}
