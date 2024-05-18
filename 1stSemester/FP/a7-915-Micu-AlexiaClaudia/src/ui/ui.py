from src.services.student_services import *


class UserInterfaceException(Exception):

    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message


class UserInterface:

    def __init__(self, service):
        self._service = service

    def add(self, student: Student):
        self._service.add(student)

    def display(self):
        for student in self._service.return_all():
            print(str(student))
        print("\n")

    def filter(self, group):
        self._service.filter(group)

    def undo(self):
        if self._service.operations == 0:
            raise ServiceException("Nothing to undo")
        self._service.undo()

    def menu(self):

        while True:
            print("1.Add a new student")
            print("2.Display the list of student")
            print("3.Filter by a specified group")
            print("4.Undo")
            print("0.Exit")
            print("\n")
            command = input("Select a command > ")

            if command == "1":
                id = int(input("ID: "))
                name = input("Student name: ")
                group = int(input("Group: "))
                self.add(Student(id, name, group))

            elif command == "2":
                self.display()

            elif command == "3":
                group = int(input("Select the group > "))
                self.filter(group)

            elif command == "4":
                self.undo()

            elif command == "0":
                return
