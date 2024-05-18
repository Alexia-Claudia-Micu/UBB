//
// Created by alexi on 5/2/2023.
//

#include "exceptions.h"
#include "validator.h"
#include <ctype.h>
#include <string>
using namespace std;

bool Validator::validateEventDay(int day) {
    if(day > 30 || day < 1)
        throw ExceptionsValidator("Invalid day!");
    return true;
}

bool Validator::validateEventHour(int hour) {
    if(hour > 24 || hour < 0)
        throw ExceptionsValidator("Invalid Hour!");
    return true;
}

bool Validator::validateEventMinute(int minute) {
    if(minute > 60 || minute < 0)
        throw ExceptionsValidator("Invalid Minute!");
    return true;
}

bool Validator::validateEventMonth(int month) {
    if(month > 12 || month < 1)
        throw ExceptionsValidator("Invalid Month!");
    return true;
}

bool Validator::validateEventYear(int year) {
    if(year > 2025 || year < 2022)
        throw ExceptionsValidator("Invalid year!");
    return true;
}

bool Validator::validateEventPopulation(int population) {
    if(population > 3000000 || population < 1)
        throw ExceptionsValidator("Invalid population!");
    return true;
}

bool Validator::validateEventLink(string link) {
    if(link.length() < 13)
        throw ExceptionsValidator("Invalid link!");
    if(link[0] != 'h' || link[1] != 't' || link[2] != 't' || link[3] != 'p' ||
       link[4] != 's' || link[5] != ':' || link[6] != '/' || link[7] != '/')
        throw ExceptionsValidator("Invalid link!");
    if(link.find(".com") == std::string::npos && link.find(".ro") == std::string::npos)
        throw ExceptionsValidator("Invalid link!");
    return true;
}

bool Validator::validateEventTitle(string title) {
    return true;
}

bool Validator::validateEventDescription(string description) {
    return true;
}

bool Validator::validateListingMode(string listingMode) {
    if(!(listingMode == "csv" || listingMode == "html"))
        throw ExceptionsValidator("Invalid listing mode!");
    return true;
}