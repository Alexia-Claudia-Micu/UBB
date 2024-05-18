//
// Created by alexi on 5/2/2023.
//

#ifndef A7_915_MICU_ALEXIACLAUDIA_VALIDATOR_H
#define A7_915_MICU_ALEXIACLAUDIA_VALIDATOR_H
#pragma once
#include <string>

using namespace std;


class Validator {
public:
    static bool validateEventDay(int day);
    static bool validateEventMonth(int month);
    static bool validateEventYear(int year);
    static bool validateEventHour(int hour);
    static bool validateEventMinute(int minute);
    static bool validateEventTitle(string title);
    static bool validateEventDescription(string description);
    static bool validateEventLink(string link);
    static bool validateEventPopulation(int population);
    static bool validateListingMode(string listingMode);

};


#endif //A7_915_MICU_ALEXIACLAUDIA_VALIDATOR_H
