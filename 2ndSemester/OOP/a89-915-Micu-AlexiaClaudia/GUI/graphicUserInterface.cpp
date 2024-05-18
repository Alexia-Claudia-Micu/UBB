//
// Created by alexi on 5/16/2023.
//

#include "graphicUserInterface.h"
#include "qformlayout.h"
#include "qgridlayout.h"
#include "csvRepository.h"
#include "htmlRepository.h"
#include "qlabel.h"
#include "iostream"
#include "QMessageBox"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QCoreApplication>

using namespace std;
GraphicUserInterface::GraphicUserInterface(AdministratorService &administratorService1, UserService &userService1,
                                           QWidget *parent) : administratorService(administratorService1), userService(userService1),
                                                              QMainWindow(parent){
    this->initializeGraphicUserInterface();
    this->connectSignalsAndSlotsGUI();
}

void GraphicUserInterface::initializeGraphicUserInterface() {
    QFont buttonsFont("Consolas", 13, true);

    this->listingModeButton = new QPushButton{"Listing mode"};
    this->listingModeButton->setFont(buttonsFont);

    this->administratorModeButton = new QPushButton{"Administrator Mode"};
    this->administratorModeButton->setFont(buttonsFont);

    this->userModeButton = new QPushButton{"User Mode"};
    this->userModeButton->setFont(buttonsFont);

    this->quitButton = new QPushButton{"Quit"};
    this->quitButton->setFont(buttonsFont);

    this->listingComboBox = new QComboBox{};
    this->listingComboBox->setFont(buttonsFont);
    this->listingComboBox->addItem("HTML File");
    this->listingComboBox->addItem("CSV File");

    QVBoxLayout* mainLayout = new QVBoxLayout();

    QLabel *title = new QLabel();
    title->setText("INTERESTING EVENTS NEAR YOU");
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont("Consolas", 20, true, true);
    title->setFont(titleFont);

    QLabel *blankText = new QLabel();
    blankText->setText("");

    QLabel *listingMode = new QLabel();
    listingMode->setText("Choose the listing mode");
    QFont listingModeFont("Consolas", 15, true);
    listingMode->setFont(listingModeFont);

    mainLayout->addWidget(title);
    mainLayout->addWidget(blankText);
    mainLayout->addWidget(blankText);

    QFormLayout* listingDetails = new QFormLayout();
    listingDetails->addRow(listingMode, this->listingComboBox);

    mainLayout->addLayout(listingDetails);

    QGridLayout* buttonLayout = new QGridLayout();
    buttonLayout->addWidget(this->listingModeButton, 0, 0);
    buttonLayout->addWidget(this->administratorModeButton, 1, 0);
    buttonLayout->addWidget(this->userModeButton, 2, 0);
    buttonLayout->addWidget(this->quitButton, 3, 0);

    mainLayout->addLayout(buttonLayout);

    QWidget *mainWindow = new QWidget();
    mainWindow->setLayout(mainLayout);
    setCentralWidget(mainWindow);
}

void GraphicUserInterface::connectSignalsAndSlotsGUI() {
    QObject::connect(this->administratorModeButton, &QPushButton::clicked, this, &GraphicUserInterface::startAdministratorModeGUI);
    QObject::connect(this->userModeButton, &QPushButton::clicked, this, &GraphicUserInterface::startUserModeGUI);
    QObject::connect(this->quitButton, &QPushButton::clicked, this, &Quit);
    QObject::connect(this->listingComboBox, &QComboBox::currentTextChanged, this, &GraphicUserInterface::setListingMode);
}

void GraphicUserInterface::startAdministratorModeGUI() {
    this->setCursor(Qt::WaitCursor);
    AdministratorGraphicUserInterface* administratorGraphicUserInterface = new AdministratorGraphicUserInterface{administratorService};
    this->setCursor(Qt::ArrowCursor);
}

void GraphicUserInterface::startUserModeGUI() {
    this->setCursor(Qt::WaitCursor);
    UserModeGraphicUserInterface* userModeGraphicUserInterface = new UserModeGraphicUserInterface{&userService, administratorService.getElements()};
    this->setCursor(Qt::ArrowCursor);
}

void GraphicUserInterface::setListingMode() {
    this->listingMode = this->listingComboBox->currentText().toStdString();
    if(this->listingMode == "CSV File")
        this->administratorService.setEventListingType("csv");
    else
        this->administratorService.setEventListingType("html");
}

//_____________________________________________________________________________________________________________________________

AdministratorGraphicUserInterface::AdministratorGraphicUserInterface(AdministratorService &administratorService1,
                                                                     QWidget* parent): administratorService{administratorService1},
                                                                                       QDialog{parent} {
    this->initializeAdministratorModeGUI();
    this->generateInitialEvents();
    this->connectSignalsAndSlotsAdmin();

}

void AdministratorGraphicUserInterface::initializeAdministratorModeGUI() {
    QFont buttonFont("Consolas", 13, true);

    this->eventsListWidget = new QListWidget{};
    this->eventsListWidget->setFont(buttonFont);
    {
        this->minuteComboBox = new QComboBox{};
        this->hourComboBox = new QComboBox{};
        this->dayComboBox = new QComboBox{};
        this->monthComboBox = new QComboBox{};
        this->yearComboBox = new QComboBox{};

        this->yearComboBox->addItem("2020");
//        this->yearComboBox->addItem("2019");
        this->yearComboBox->addItem("2021");
        this->yearComboBox->addItem("2022");
        this->yearComboBox->addItem("2023");
        this->yearComboBox->addItem("2024");

        this->dayComboBox->addItem("1");
        this->dayComboBox->addItem("2");
        this->dayComboBox->addItem("3");
        this->dayComboBox->addItem("4");
        this->dayComboBox->addItem("5");
        this->dayComboBox->addItem("6");
        this->dayComboBox->addItem("7");
        this->dayComboBox->addItem("8");
        this->dayComboBox->addItem("9");
        this->dayComboBox->addItem("10");
        this->dayComboBox->addItem("11");
        this->dayComboBox->addItem("12");
        this->dayComboBox->addItem("13");
        this->dayComboBox->addItem("14");
        this->dayComboBox->addItem("15");
        this->dayComboBox->addItem("16");
        this->dayComboBox->addItem("17");
        this->dayComboBox->addItem("18");
        this->dayComboBox->addItem("19");
        this->dayComboBox->addItem("20");
        this->dayComboBox->addItem("21");
        this->dayComboBox->addItem("22");
        this->dayComboBox->addItem("23");
        this->dayComboBox->addItem("24");
        this->dayComboBox->addItem("25");
        this->dayComboBox->addItem("26");
        this->dayComboBox->addItem("27");
        this->dayComboBox->addItem("28");
        this->dayComboBox->addItem("29");
        this->dayComboBox->addItem("30");
        this->monthComboBox->addItem("1");
        this->monthComboBox->addItem("2");
        this->monthComboBox->addItem("3");
        this->monthComboBox->addItem("4");
        this->monthComboBox->addItem("5");
        this->monthComboBox->addItem("6");
        this->monthComboBox->addItem("7");
        this->monthComboBox->addItem("8");
        this->monthComboBox->addItem("9");
        this->monthComboBox->addItem("10");
        this->monthComboBox->addItem("11");
        this->monthComboBox->addItem("12");
        this->minuteComboBox->addItem("00");
        this->minuteComboBox->addItem("15");
        this->minuteComboBox->addItem("30");
        this->minuteComboBox->addItem("45");
        this->hourComboBox->addItem("12");
        this->hourComboBox->addItem("16");
        this->hourComboBox->addItem("18");
    }

    this->indexLineEdit = new QLineEdit{};
    this->indexLineEdit->setFont(buttonFont);

    this->titleLineEdit = new QLineEdit{};
    this->titleLineEdit->setFont(buttonFont);

    this->descriptionLineEdit = new QLineEdit{};
    this->descriptionLineEdit->setFont(buttonFont);

    this->attendeesLineEdit = new QLineEdit{};
    this->attendeesLineEdit->setFont(buttonFont);

    this->linkLineEdit = new QLineEdit{};
    this->linkLineEdit->setFont(buttonFont);

    this->addButton = new QPushButton{"Add"};
    this->addButton->setFont(buttonFont);

    this->removeButton = new QPushButton{"Remove"};
    this->removeButton->setFont(buttonFont);

    this->updateButton = new QPushButton{"Update"};
    this->updateButton->setFont(buttonFont);

    this->quitButton = new QPushButton{"Quit"};
    this->quitButton->setFont(buttonFont);

    this->listWithListingModeButton = new QPushButton{"List All"};
    this->listWithListingModeButton->setFont(buttonFont);

    QLabel *blank = new QLabel();
    blank->setText("");

    QLabel *events = new QLabel();
    events->setText("Events");
    QFont eventsFont("Consolas", 15, true);
    events->setFont(eventsFont);

    QLabel *indexLabel = new QLabel();
    indexLabel->setText("Index");
    indexLabel->setFont(buttonFont);

    QLabel *title = new QLabel();
    title->setText("Title");
    title->setFont(buttonFont);

    QLabel *description = new QLabel();
    description->setText("Description");
    description->setFont(buttonFont);

    QLabel *link = new QLabel();
    link->setText("Link");
    link->setFont(buttonFont);

    QLabel *attendees = new QLabel();
    attendees->setText("Attendees");
    attendees->setFont(buttonFont);

    QLabel *minute = new QLabel();
    minute->setText("Minute");
    minute->setFont(buttonFont);

    QLabel *hour = new QLabel();
    hour->setText("Hour");
    hour->setFont(buttonFont);

    QLabel *day = new QLabel();
    day->setText("Day");
    day->setFont(buttonFont);

    QLabel *month = new QLabel();
    month->setText("Month");
    month->setFont(buttonFont);

    QLabel *year = new QLabel();
    year->setText("Year");
    year->setFont(buttonFont);

    QVBoxLayout* adminLayout = new QVBoxLayout();
    adminLayout->addWidget(events);
    adminLayout->addWidget(this->eventsListWidget);

    QFormLayout* eventDetails = new QFormLayout();
    eventDetails->addRow(indexLabel, this->indexLineEdit);
    eventDetails->addRow(title, this->titleLineEdit);
    eventDetails->addRow(description, this->descriptionLineEdit);
    eventDetails->addRow(minute, this->minuteComboBox);
    eventDetails->addRow(hour, this->hourComboBox);
    eventDetails->addRow(day, this->dayComboBox);
    eventDetails->addRow(month, this->monthComboBox);
    eventDetails->addRow(year, this->yearComboBox);
    eventDetails->addRow(attendees, this->attendeesLineEdit);
    eventDetails->addRow(link, this->linkLineEdit);

    adminLayout->addLayout(eventDetails);

    QGridLayout* buttonsLayout = new QGridLayout();
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->removeButton, 0, 1);
    buttonsLayout->addWidget(this->updateButton, 0, 2);
    buttonsLayout->addWidget(this->quitButton, 1, 1);

    adminLayout->addLayout(buttonsLayout);

    QWidget* administratorDisplayWindow = new QWidget();
    administratorDisplayWindow->setLayout(adminLayout);
    administratorDisplayWindow->show();
}

void AdministratorGraphicUserInterface::generateInitialEvents() {
    this->eventsListWidget->clear();
    vector<Event> allEvents = this->administratorService.getIterator();
    for(auto event = allEvents.begin(); event != allEvents.end(); event++){
        this->eventsListWidget->addItem(QString::fromStdString((*event).toString()));
    }
}

void AdministratorGraphicUserInterface::connectSignalsAndSlotsAdmin() {
    QObject::connect(this->eventsListWidget, &QListWidget::itemSelectionChanged, [this](){
        int selectedIndex = this->getSelectedIndexAdmin();
        if(selectedIndex < 0)
            return;
        Event newEvent = this->administratorService.getElements().getAll().at(selectedIndex);
        this->titleLineEdit->setText(QString::fromStdString(newEvent.getTitle()));
        this->descriptionLineEdit->setText(QString::fromStdString(newEvent.getDescription()));
        this->minuteComboBox->setCurrentText(QString::fromStdString(to_string(newEvent.getDateAndTime().time.minute)));
        this->hourComboBox->setCurrentText(QString::fromStdString(to_string(newEvent.getDateAndTime().time.hour)));
        this->dayComboBox->setCurrentText(QString::fromStdString(to_string(newEvent.getDateAndTime().date.day)));
        this->monthComboBox->setCurrentText(QString::fromStdString(to_string(newEvent.getDateAndTime().date.month)));
        this->yearComboBox->setCurrentText(QString::fromStdString(to_string(newEvent.getDateAndTime().date.year)));
        this->attendeesLineEdit->setText(QString::fromStdString(to_string(newEvent.getNumberOfPeople())));
        this->linkLineEdit->setText(QString::fromStdString(newEvent.getLink()));
    });
    QObject::connect(this->addButton, &QPushButton::clicked, this, &AdministratorGraphicUserInterface::addEvent);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &AdministratorGraphicUserInterface::removeEvent);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdministratorGraphicUserInterface::updateEvent);
    QObject::connect(this->quitButton, &QPushButton::clicked, this, &Quit);
    QObject::connect(this->listWithListingModeButton, &QPushButton::clicked, this, &AdministratorGraphicUserInterface::listAllWithListingMode);
}

int AdministratorGraphicUserInterface::getSelectedIndexAdmin() const {
    QModelIndexList  selectedIndexes = this->eventsListWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty()){
        this->titleLineEdit->clear();
        this->descriptionLineEdit->clear();
        this->attendeesLineEdit->clear();
        this->linkLineEdit->clear();
        return -1;
    }
    return selectedIndexes.at(0).row();
}

void AdministratorGraphicUserInterface::addEvent() {
    string title = this->titleLineEdit->text().toStdString();
    string description = this->descriptionLineEdit->text().toStdString();
    string link = this->linkLineEdit->text().toStdString();
    int attendees = this->attendeesLineEdit->text().toInt();
    int minute = this->minuteComboBox->currentText().toInt();
    int hour = this->hourComboBox->currentText().toInt();
    int day = this->dayComboBox->currentText().toInt();
    int month = this->monthComboBox->currentText().toInt();
    int year = this->yearComboBox->currentText().toInt();

    if(!Validator::validateEventTitle(title) || !Validator::validateEventDescription(description) || !Validator::validateEventMinute(minute) || !Validator::validateEventHour(hour) || !Validator::validateEventDay(day) || !Validator::validateEventMonth(month) || !Validator::validateEventYear(year) || !Validator::validateEventPopulation(attendees) || !Validator::validateEventLink(link)){
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    } else{
        try{
            this->administratorService.add(title, description, year, month, day, hour, minute, attendees, link);
        }
        catch (ExceptionsRepository){
            QMessageBox::critical(this, "Error", "Could not add product!");
        }
    }
    this->generateInitialEvents();
}

void AdministratorGraphicUserInterface::removeEvent() {
    string title = this->titleLineEdit->text().toStdString();
    string description = this->descriptionLineEdit->text().toStdString();
    string link = this->linkLineEdit->text().toStdString();
    int attendees = this->attendeesLineEdit->text().toInt();
    int minute = this->minuteComboBox->currentText().toInt();
    int hour = this->hourComboBox->currentText().toInt();
    int day = this->dayComboBox->currentText().toInt();
    int month = this->monthComboBox->currentText().toInt();
    int year = this->yearComboBox->currentText().toInt();

    if(!Validator::validateEventTitle(title) ||  !Validator::validateEventMinute(minute) || !Validator::validateEventHour(hour) || !Validator::validateEventDay(day) || !Validator::validateEventMonth(month) || !Validator::validateEventYear(year)){
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    } else{
        try{
            this->administratorService.remove(title, year,  month,day, hour, minute);
        }
        catch (ExceptionsRepository){
            QMessageBox::critical(this, "Error", "Could not remove product!");
        }
    }
    this->generateInitialEvents();
}

void AdministratorGraphicUserInterface::updateEvent() {
    string title = this->titleLineEdit->text().toStdString();
    string description = this->descriptionLineEdit->text().toStdString();
    string link = this->linkLineEdit->text().toStdString();
    int attendees = this->attendeesLineEdit->text().toInt();
    int index = this->indexLineEdit->text().toInt();
    int minute = this->minuteComboBox->currentText().toInt();
    int hour = this->hourComboBox->currentText().toInt();
    int day = this->dayComboBox->currentText().toInt();
    int month = this->monthComboBox->currentText().toInt();
    int year = this->yearComboBox->currentText().toInt();

    if(!Validator::validateEventTitle(title) || !Validator::validateEventDescription(description) || !Validator::validateEventMinute(minute) || !Validator::validateEventHour(hour) || !Validator::validateEventDay(day) || !Validator::validateEventMonth(month) || !Validator::validateEventYear(year) || !Validator::validateEventPopulation(attendees) || !Validator::validateEventLink(link)){
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    } else{
        try{
            this->administratorService.update(index, title, description, year, month, day, hour, minute , attendees, link);
        }
        catch (ExceptionsRepository){
            QMessageBox::critical(this, "Error", "Could not update product!");
        }
    }
    this->generateInitialEvents();
}

void AdministratorGraphicUserInterface::listAllWithListingMode() {

}

//------------------------------------------------------------------------------------------------

UserModeGraphicUserInterface::UserModeGraphicUserInterface(UserService *userService1, Repository &repository,
                                                           QWidget *parent): userService(userService1), allEvents(&repository), QDialog(parent){
    this->initializeUserModeGUI();
    this->connectSignalsAndSlotsUser();
    this->displayEventsUserIsInterestedIn();
}

void UserModeGraphicUserInterface::initializeUserModeGUI() {
    QFont buttonFont("Consolas", 13, true);

    this->userEventsListWidget = new QListWidget{};
    this->userEventsListWidget->setFont(buttonFont);

    this->viewAllEventsButton = new QPushButton{"View all events"};
    this->viewAllEventsButton->setFont(buttonFont);

    this->removeEventFromUserInterestsButton = new QPushButton{"Remove an event"};
    this->removeEventFromUserInterestsButton->setFont(buttonFont);

    QLabel *blank = new QLabel();
    blank->setText("");

    this->monthLineEdit = new QLineEdit{};
    this->monthLineEdit->setFont(buttonFont);

    this->eventToRemove = new QLineEdit{};
    this->eventToRemove->setFont(buttonFont);

    QLabel *indexLabel = new QLabel();
    indexLabel->setText("Index");
    indexLabel->setFont(buttonFont);

    QLabel *month = new QLabel();
    month->setText("Month");
    month->setFont(buttonFont);

    QFormLayout* eventDetails = new QFormLayout();
    eventDetails->addRow(month, this->monthLineEdit);
    eventDetails->addRow(indexLabel, this->eventToRemove);


    QLabel *interestingEventsLabel = new QLabel();
    interestingEventsLabel->setText("Events you're interested in");
    QFont eventsFont("Consolas", 15, true);
    interestingEventsLabel->setFont(eventsFont);

    QVBoxLayout* userLayout = new QVBoxLayout(this);
    userLayout->addWidget(interestingEventsLabel);
    userLayout->addWidget(this->userEventsListWidget);

    QGridLayout* buttonsLayout = new QGridLayout();
    buttonsLayout->addWidget(this->viewAllEventsButton, 0, 0);
    //buttonsLayout->addWidget(this->showUserEventsButton, 1, 0);
    buttonsLayout->addWidget(this->removeEventFromUserInterestsButton, 1, 0);

    userLayout->addLayout(eventDetails);
    userLayout->addLayout(buttonsLayout);

    QWidget *userDisplayWindow = new QWidget();
    userDisplayWindow->setLayout(userLayout);
    userDisplayWindow->show();
}

void UserModeGraphicUserInterface::connectSignalsAndSlotsUser() {
    QObject::connect(this->viewAllEventsButton, &QPushButton::clicked, this, &UserModeGraphicUserInterface::showEventsInterface);
    //QObject::connect(this->showUserEventsButton, &QPushButton::clicked, this, &UserModeGraphicUserInterface::showUserEvents);
    QObject::connect(this->removeEventFromUserInterestsButton, &QPushButton::clicked, this, &UserModeGraphicUserInterface::removeFromInterests);

}

void UserModeGraphicUserInterface::connectSignalsAndSlotsUserViewEvents() {
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserModeGraphicUserInterface::nextEvent);
    QObject::connect(this->markAsInterestedButton, &QPushButton::clicked, this, &UserModeGraphicUserInterface::markAsInterestedIn);
    QObject::connect(this->doneButton, &QPushButton::clicked, this, &UserModeGraphicUserInterface::stopIteratingEvents);
}

void UserModeGraphicUserInterface::displayEventsUserIsInterestedIn() {
    this->userEventsListWidget->clear();
    vector<Event> allEvents = this->userService->getListOfUserEvents();
    for(auto event = allEvents.begin(); event != allEvents.end(); event++){
        this->userEventsListWidget->addItem(QString::fromStdString((*event).toString()));
    }
}

void UserModeGraphicUserInterface::showEventsInterface() {
    this->month = this->monthLineEdit->text().toInt();
    this->initializeDisplayEvents();
    this->connectSignalsAndSlotsUserViewEvents();
    this->position = -1;
    this->nextEvent();
}

void UserModeGraphicUserInterface::nextEvent() {
    if(this->position+1 == this->userService->getEventsChronologicallyForAMonth(month).size())
        this->position = -1;
    this->eventsListWidget->clear();
    this->position++;
    auto eventsForMonth = this->userService->getEventsChronologicallyForAMonth(month).at(this->position);
    this->eventsListWidget->addItem(QString::fromStdString(eventsForMonth.toString()));
    string link_to_open = "start chrome ";
    link_to_open += eventsForMonth.getLink();
    const char* charPtr = link_to_open.c_str();
    system(charPtr);
    //ShellExecuteA(NULL, "open", "chrome.exe", "https://untold.com/", NULL, SW_NORMAL);
}

void UserModeGraphicUserInterface::stopIteratingEvents() {
    this->windowWidget->close();
}

void UserModeGraphicUserInterface::markAsInterestedIn() {
    this->userService->addEvent(this->userService->getEventsChronologicallyForAMonth(this->month).at(this->position));
    this->stopIteratingEvents();
    this->displayEventsUserIsInterestedIn();
}

void UserModeGraphicUserInterface::removeFromInterests() {
    int indexToRemove = this->eventToRemove->text().toInt();
    this->userService->removeEvent(indexToRemove);
    this->displayEventsUserIsInterestedIn();
}

void UserModeGraphicUserInterface::initializeDisplayEvents() {
    QFont buttonsFont("Consolas", 13, true);

    this->eventsListWidget = new QListWidget{};
    this->eventsListWidget->setFont(buttonsFont);

    this->nextButton = new QPushButton{"Next"};
    this->nextButton->setFont(buttonsFont);

    this->markAsInterestedButton = new QPushButton{"Interesting"};
    this->markAsInterestedButton->setFont(buttonsFont);

    this->doneButton = new QPushButton{"Done"};
    this->doneButton->setFont(buttonsFont);

    QLabel *eventsText = new QLabel();
    eventsText->setText("Events");
    QFont eventsFont("Consolas", 15, true);
    eventsText->setFont(eventsFont);

    QVBoxLayout* displayLayout = new QVBoxLayout();
    displayLayout->addWidget(eventsText);
    displayLayout->addWidget(this->eventsListWidget);

    QGridLayout* buttonsLayout = new QGridLayout();
    buttonsLayout->addWidget(this->nextButton, 0, 0);
    buttonsLayout->addWidget(this->markAsInterestedButton, 0, 1);
    buttonsLayout->addWidget(this->doneButton, 0, 2);

    displayLayout->addLayout(buttonsLayout);
    QWidget *mainDisplayWindow = new QWidget();
    mainDisplayWindow->setLayout(displayLayout);
    this->windowWidget = mainDisplayWindow;
    mainDisplayWindow->show();
}

void UserModeGraphicUserInterface::showUserEvents() {
    this->displayEventsUserIsInterestedIn();
}

void Quit() {
    QCoreApplication::quit();
}
