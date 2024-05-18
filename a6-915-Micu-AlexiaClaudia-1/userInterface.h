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

using namespace std;

class UserInterface
{
private:
    AdministratorService administratorService;
    UserService userService;
    void print(Event event);
public:
    UserInterface(AdministratorService &administratorService1, UserService &userService1);
    ~UserInterface();
    void menu();
};

#endif //A45_915_MICU_ALEXIACLAUDIA_USERINTERFACE_H
