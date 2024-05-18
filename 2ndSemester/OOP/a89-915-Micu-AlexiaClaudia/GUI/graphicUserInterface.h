//
// Created by alexi on 5/16/2023.
//

#ifndef A89_915_MICU_ALEXIACLAUDIA_GRAPHICUSERINTERFACE_H
#define A89_915_MICU_ALEXIACLAUDIA_GRAPHICUSERINTERFACE_H
#pragma once
#include "administratorService.h"
#include "userService.h"
#include "validator.h"
#include "exceptions.h"
#include <QVBoxLayout>
#include "qwidget.h"
#include "qlistwidget.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include <QComboBox>
#include <QMainWindow>
#include <QDialog>

class GraphicUserInterface: public QMainWindow{
    Q_OBJECT
private:
    string listingMode = "HTML File";
    AdministratorService& administratorService;
    UserService& userService;
    void initializeGraphicUserInterface();

    QComboBox *listingComboBox;
    QPushButton* administratorModeButton, *userModeButton, *quitButton, *listingModeButton;
public:
    GraphicUserInterface(AdministratorService &administratorService1, UserService &userService1, QWidget *parent = 0);
    //~GraphicUserInterface();
    void setListingMode();
    void connectSignalsAndSlotsGUI();
    void startUserModeGUI();
    void startAdministratorModeGUI();
};

class AdministratorGraphicUserInterface: public QDialog{
private:
    AdministratorService& administratorService;
    QListWidget* eventsListWidget;
    QLineEdit* indexLineEdit, *titleLineEdit, *descriptionLineEdit, *attendeesLineEdit, *linkLineEdit;
    QComboBox *dayComboBox, *monthComboBox, *yearComboBox, *minuteComboBox, *hourComboBox;
    QPushButton* quitButton, *addButton, *removeButton, *updateButton, *listWithListingModeButton;
public:
    AdministratorGraphicUserInterface(AdministratorService& administratorService1, QWidget* parent = NULL);
    ~AdministratorGraphicUserInterface(){};
    void connectSignalsAndSlotsAdmin();
    int getSelectedIndexAdmin() const;
    void initializeAdministratorModeGUI();
    void generateInitialEvents();

    void addEvent();
    void removeEvent();
    void updateEvent();
    void listAllWithListingMode();

};

class UserModeGraphicUserInterface: public QDialog{
private:
    int position, month;
    UserService* userService;
    Repository* allEvents;
    QListWidget* eventsListWidget;
    QListWidget* userEventsListWidget;
    QWidget* windowWidget;
    QPushButton* viewAllEventsButton, *removeEventFromUserInterestsButton;
    QPushButton* doneButton, *nextButton, *markAsInterestedButton;
    QLineEdit *monthLineEdit, *eventToRemove;
public:
    UserModeGraphicUserInterface(UserService* userService1, Repository& repository, QWidget* parent = NULL);
    ~UserModeGraphicUserInterface(){};
    void connectSignalsAndSlotsUser();
    void connectSignalsAndSlotsUserViewEvents();
    void initializeUserModeGUI();

    void showEventsInterface();

    void initializeDisplayEvents();
    void displayEventsUserIsInterestedIn();
    void showUserEvents();
    void nextEvent();
    void stopIteratingEvents();
    void markAsInterestedIn();
    void removeFromInterests();
};

static void Quit();

#endif //A89_915_MICU_ALEXIACLAUDIA_GRAPHICUSERINTERFACE_H
