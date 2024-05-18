//
// Created by Alexia RTX Top on 5/17/2023.
//
#include <QApplication>
#include <QPushButton>
#include "graphicUserInterface.h"
#include "administratorService.h"
#include "userService.h"
#include "validator.h"

int main(int argc, char *argv[]) {
    Validator::test_add_ValidEvent_ReturnsTrue();
    Validator::test_add_ValidEvent_ReturnsFalse();
    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();

    auto *repository = new FileRepository("events.txt");
    AdministratorService administratorService = AdministratorService(repository, *repository, "html");

    UserService userService = UserService(administratorService.getElements());

    GraphicUserInterface graphicUserInterface(administratorService, userService);
    graphicUserInterface.setStyleSheet("QMainWindow {background: 'gray';}");
    graphicUserInterface.show();

    return QApplication::exec();

}