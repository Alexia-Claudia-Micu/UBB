//
// Created by alexi on 3/16/2023.
//

#ifndef A23_915_MICU_ALEXIACLAUDIA_UI_H
#define A23_915_MICU_ALEXIACLAUDIA_UI_H

#pragma once
#include "service.h"

typedef struct
{
    Service service;
}UserInterface;

UserInterface createUserInterface();
void ui(Service* service);

#endif //A23_915_MICU_ALEXIACLAUDIA_UI_H
