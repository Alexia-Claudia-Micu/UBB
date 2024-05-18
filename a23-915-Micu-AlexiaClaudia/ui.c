//
// Created by alexi on 3/16/2023.
//
#include "ui.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

UserInterface createUserInterface()
{
    UserInterface newUserInterface;
    newUserInterface.service = createService();
    return newUserInterface;
}

void clearUserInterface(UserInterface* userInterface)
{
    clearService(&userInterface->service);
    //free(userInterface);
}

int continentValidator(char* continent)
{
    if(strcmp("Europe", continent) == 0)
        return 1;
    if(strcmp("Europe", continent) == 0)
        return 1;
    if(strcmp("Asia", continent) == 0)
        return 1;
    if(strcmp("America", continent) == 0)
        return 1;
    if(strcmp("Africa", continent) == 0)
        return 1;
    if(strcmp("Australia", continent) == 0)
        return 1;
    return 0;
}

void ui(Service* service)
{
    int command = 1;
    char* commandString;
    commandString = (char* ) malloc(10 * sizeof(char ));
    while(command != -1)
    {
        printf("\n-----------------------------------\n");
        printf("1. Add a country.\n");
        printf("2. Delete a country.\n");
        printf("3. Update(Migrate).\n");
        printf("4. Display using keyword.\n");
        printf("5. Display countries on given continent in ascending order of population.\n");
        printf("6. Undo.\n");
        printf("7. Redo.\n");
        printf("-1. Exit.\n");
        printf("-----------------------------------\n");
        printf("command >");
        scanf("%s", commandString);
        int validChoice = atoi(commandString);
        while(validChoice == 0) {
            printf("Wrong command!\nInput another >");
            scanf("%s", commandString);
            validChoice = atoi(commandString);
        }
        command = atoi(commandString);
        switch (command) {
            case -1:
                free(commandString);
                return;
            case 1: {
                char* countryName;
                char* continent;
                countryName = (char*) malloc(60 * sizeof (char));
                continent = (char*) malloc(60 * sizeof (char));
                long int population;
                printf("You need to input the country data: name, continent and population.\n");
                printf("Input name >");
                scanf("%s", countryName);
                printf("Input continent >");
                scanf("%s", continent);
                while(continentValidator(continent) == 0)
                {
                    printf("Input valid continent >");
                    scanf("%s", continent);
                }
                printf("Input population >");
                scanf("%ld", &population);
                if(addCountryToRepo(service, countryName, continent, population) == 0)
                    printf("Add operation failed.\n");
                free(countryName);
                free(continent);
                break;
            }
            case 2:{
                char* countryName;
                countryName = (char*) malloc(60 * sizeof (char));
                printf("You need to input the country name.\n");
                printf("Input name >\n");
                scanf("%s", countryName);
                if(deleteCountryFromRepo(service, countryName) == 0)
                    printf("Delete operation failed.\n");
                free(countryName);
                break;
            }
            case 3:{
                char* fromCountryName;
                char* toCountryName;
                fromCountryName =(char*) malloc(60 * sizeof (char));
                toCountryName =(char*) malloc(60 * sizeof (char));
                long int numberMigrators;
                printf("What country are people migrating from >");
                scanf("%s", fromCountryName);
                printf("What country are people migrating to >");
                scanf("%s", toCountryName);
                printf("Input population >");
                scanf("%ld", &numberMigrators);
                if(migratePopulation(service, fromCountryName, toCountryName, numberMigrators) == 0)
                    printf("Migrate operation failed.\n");
                free(toCountryName);
                free(fromCountryName);
                break;
            }
            case 4: {
                char* result;
                char* keyString;
                result = (char*) malloc(10000*sizeof(char ));
                keyString = (char*) malloc(60*sizeof(char ));
                printf("Input key string for criteria by which to search (or - for all) >");
                scanf("%s", keyString);
                filterCountriesWithString(service, keyString, result);
                printf("%s\n", result);
                free(result);
                free(keyString);
                break;
            }
            case 5: {
                char* result;
                char* continentName;
                result = (char*) malloc(10000*sizeof(char ));
                continentName = (char*) malloc(60*sizeof(char ));
                printf("Input continent to display >");
                scanf("%s", continentName);
                while(continentValidator(continentName) == 0)
                {
                    printf("Input valid continent >");
                    scanf("%s", continentName);
                }
                filterAndSortCountries(service, continentName, result);
                printf("%s\n", result);
                free(result);
                free(continentName);
                break;
            }
            case 6:{
                if(undo(service) == 0)
                    printf("Redo service is not available.\n");
                break;
            }
            case 7:
            {
                if(redo(service) == 0)
                    printf("Redo service is not available.\n");
                break;
            }
            default:
                printf("The command does not exist!\n");
        }
    }
}

int main()
{
    UserInterface userInterface = createUserInterface();
    ui(&userInterface.service);
    clearUserInterface(&userInterface);
    /*char result[10000];
    filterCountries(&countryRepository,"land", result);
    printf("%s", result);*/
    printf("%d", _CrtDumpMemoryLeaks());

    return 0;
}
