//
// Created by alexi on 4/2/2023.
//

#ifndef A45_915_MICU_ALEXIACLAUDIA_USERINTERFACE_H
#define A45_915_MICU_ALEXIACLAUDIA_USERINTERFACE_H
#pragma once
#include "userService.h"
#include "administratorService.h"
#include "fstream"
#include "iostream"
#include "validator.h"

using namespace std;

class UserInterface
{
private:
    string listingMode; // html or csv
    AdministratorService administratorService;
    UserService userService;
public:
    UserInterface(AdministratorService &administratorService1, UserService &userService1, string listMode);
    ~UserInterface();
    void menu();
};

string readListingMode();


#endif //A45_915_MICU_ALEXIACLAUDIA_USERINTERFACE_H
