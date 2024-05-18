from src.services.ClientServices import ClientService
from src.services.BookServices import BookService
from src.services.RentalServices import RentalService
from src.ui.ui_exception import UserInterfaceException
from src.repository.repository_exception import RepositoryException
from src.services.service_exception import ServiceException
from datetime import date

def validate_date(year, month, day):
    year = int(year)
    month = int(month)
    day = int(day)

    if year > 2022 or year < 2019:
        raise UserInterfaceException("Invalid year")
    if month < 1 or month > 12:
        raise UserInterfaceException("Invalid month")
    if day < 1 or day > 31:
        raise UserInterfaceException("Invalid day")

    return date(year, month, day)

def read_date():
    while True:
        try:
            year = int(input("Give year > "))
            month = int(input("Give month > "))
            day = int(input("Give day > "))
            validate_date(year, month, day)
        except UserInterfaceException as uie:
            print(f"There was a {str(type(uie))}, with message: {str(uie)}")
        except ValueError as ve:
            print(f"There was a {str(type(ve))}, with message: {str(ve)}")
        except TypeError as ve:
            print(f"There was a {str(type(ve))}, with message: {str(ve)}")
        else:
            return date(year, month, day)

def get_string( message: str):
    s = ""
    while True:
        try:
            s = input(f"Give {message} > ")
            if len(s) < 3:
                raise UserInterfaceException(f"Given string cannot be a {message}")
        except UserInterfaceException as uie:
            print(f"There was a {str(type(uie))}, with message: {str(uie)}")
        else: return s

class UserInterface:
    def __init__(self, book_services: BookService, client_services: ClientService, rental_services: RentalService):
        self._book_services = book_services
        self._client_services = client_services
        self._rental_services = rental_services

    def add_book(self):
        try:
            id = self.get_book_id(1)
            title= get_string("title")
            author = get_string("author")
            self._book_services.add(id, title, author)
        except RepositoryException as re:
            print(f"There was a {str(type(re))}, with message: {str(re)}")

    def add_client(self):
        try:
            id = self.get_client_id(1)
            name = get_string("name")
            self._client_services.add(id, name)
        except RepositoryException as re:
            print(f"There was a {str(type(re))}, with message: {str(re)}")

    def remove_book(self):
        book = self.get_book_id(0)
        self._book_services.delete_book(book)
        to_eliminate = []
        for rental in self._rental_services.get_all():
            if rental.book_id == book:
                to_eliminate.append(rental.id)
        for id in to_eliminate:
            self._rental_services.delete_rental(id)

    def remove_client(self):
        client = self.get_client_id(0)
        self._client_services.delete_client(client)
        to_eliminate = []
        for rental in self._rental_services.get_all():
            if rental.client_id == client:
                to_eliminate.append(rental.id)
        for id in to_eliminate:
            self._rental_services.delete_rental(id)

    def remove_rental(self, rental):
        self._rental_services.delete_rental(rental)

    def update_book(self):
        id = self.get_book_id(0)
        title= get_string("title")
        author = get_string("author")
        self._book_services.update(id, title, author)

    def update_client(self):
        id = self.get_client_id(0)
        name = get_string("name")
        self._client_services.update(id, name)

    def list_books(self):
        self._book_services.list()

    def list_clients(self):
        self._client_services.list()

    def list_rentals(self):
        self._rental_services.list()

    def search_client(self):
        try:
            choose_field = input("Choose field: id or name > ")
            if choose_field not in ["id", "name"]:
                raise UserInterfaceException("Inexistent field")
        except UserInterfaceException as uie:
            print(f"There was a {str(type(uie))}, with message: {str(uie)}")
        if choose_field == "id":
            id = self.get_client_id(0)
            print(self._client_services.search_by_id(id))
        elif choose_field == "name":
            name = get_string("name")
            print(self._client_services.search_by_name(name))

    def search_book(self):
        try:
            choose_field = input("Choose field: id, title or author > ")
            if choose_field not in ["id", "title", "author"]:
                raise UserInterfaceException("Inexistent field")
        except UserInterfaceException as uie:
            print(f"There was a {str(type(uie))}, with message: {str(uie)}")
        if choose_field == "id":
            id = self.get_book_id(0)
            print(self._book_services.search_by_id(id))
        elif choose_field == "title":
            title = get_string("title")
            print(self._book_services.search_by_title(title))
        elif choose_field == "author":
            author = get_string("author")
            print(self._book_services.search_by_author(author))

    def check_rental_date(self, book_id, new_date):
        for rental in self._rental_services.get_all():
            if rental.book_id == book_id:
                if rental.returned_date == None:
                    raise ServiceException("Cannot rent a book that has already been rented")
                if new_date > rental.rented_date and new_date < rental.returned_date:
                    raise ServiceException("Cannot rent a book that has already been rented")

    def check_date(self, book_id, s_date, e_date):
        for rental in self._rental_services.get_all():
            if rental.book_id == book_id:
                if s_date < rental.rented_date and e_date > rental.rented_date:
                    raise ServiceException("Cannot rent a book that has already been rented")
                if s_date > rental.rented_date and s_date < rental.returned_date:
                    raise ServiceException("Cannot rent a book that has already been rented")

    def check_already_rented(self, id):
        for rental in self._rental_services.get_all():
            if rental.returned_date == date(1000,1,1) and rental.id == id:
                raise ServiceException("Cannot rent a book that has not been returned")

    def rent_book(self):
        book_id = self.get_book_id(0)
        client_id = self.get_client_id(0)
        id = self._rental_services._repository.find_unused_id()
        try:
            self.check_already_rented(book_id)
            rental_date = read_date()
            self.check_rental_date(book_id, rental_date)
        except UserInterfaceException as uie:
            print(f"There was a {str(type(uie))}, with message: {str(uie)}")
        except ServiceException as se:
            print(f"There was a {str(type(se))}, with message: {str(se)}")
        else:
            self._rental_services.create_rental(id, book_id, client_id, rental_date, None)

    def return_book(self):
        book_id = self.get_book_id(0)
        client_id = self.get_client_id(0)
        rental = self._rental_services.get_book_client(book_id, client_id)
        try:
            if rental == None:
                raise ServiceException("Cannot return a book that has not been rented")
            return_date = read_date()
            rental_date = self._rental_services.get_rental_date(rental)
            if return_date < rental_date:
                raise ServiceException("Return date cannot be before rental date")
            self.check_date(book_id, rental_date, return_date)
        except UserInterfaceException as uie:
            print(f"There was a {str(type(uie))}, with message: {str(uie)}")
        except ServiceException as se:
            print(f"There was a {str(type(se))}, with message: {str(se)}")
        else:
            self._rental_services.update_return(rental, return_date)

    def get_client_id(self, unique):
        client_id = 0
        while True:
            try:
                client_id = int(input("Give client id > "))
                if self._client_services.search_by_id(client_id) == None and unique == 0:
                    raise ServiceException("Client id does not exist")
                elif self._client_services.search_by_id(client_id) == None and unique == 1:
                    raise ServiceException("Duplicate client id")
            except UserInterfaceException as uie:
                print(f"There was a {str(type(uie))}, with message: {str(uie)}")
            except ValueError as ve:
                print(f"There was a {str(type(ve))}, with message: {str(ve)}")
            except TypeError as ve:
                print(f"There was a {str(type(ve))}, with message: {str(ve)}")
            except ServiceException as se:
                print(f"There was a {str(type(se))}, with message: {str(se)}")
            else:
                return client_id
    def get_book_id(self, unique):
        book_id = 0
        while True:
            try:
                book_id = int(input("Give book id > "))
                if self._book_services.search_by_id(book_id) == None and unique == 0:
                    raise UserInterfaceException("Book id does not exist")
            except UserInterfaceException as uie:
                print(f"There was a {str(type(uie))}, with message: {str(uie)}")
            except ValueError as ve:
                print(f"There was a {str(type(ve))}, with message: {str(ve)}")
            except TypeError as ve:
                print(f"There was a {str(type(ve))}, with message: {str(ve)}")
            except ServiceException as se:
                print(f"There was a {str(type(se))}, with message: {str(se)}")
            else:
                return book_id

    def menu(self):
        command = 0
        while command != '0':
            commands = ['1a', '1b', '1c', '2a', '2b', '3a', '3b', '4a', '4b', '5a', '5b', '6a', '6b', '7','8', '9', '0']
            print("--------------------------------------")
            print("1a. List books")
            print("1b. List clients")
            print("1c. List rentals")
            print("2a. Remove books")
            print("2b. Remove clients")
            print("3a. Update books")
            print("3b. Update clients")
            print("4a. Add books")
            print("4b. Add clients")
            print("5a. Search books")
            print("5b. Search clients")
            print("6a. Rent book")
            print("6b. Return book")
            print("7. Statistics for book rentals")
            print("8. Statistics for most active client")
            print("9. Statistics for most rented author")
            print("0. Exit")
            print("--------------------------------------")
            try:
                command = input("Give command > ")
                if command not in commands:
                    raise UserInterfaceException("Command does not exist. ")
            except UserInterfaceException as uie:
                print(f"There was a {str(type(uie))}, with message: {str(uie)}")
            else:
                print("--------------------------------------")

                if command == "1a":
                    self.list_books()
                elif command == "1b":
                    self.list_clients()
                elif command == "1c":
                    self.list_rentals()
                elif command == "2a":
                    self.remove_book()
                elif command == "2b":
                    self.remove_client()
                elif command == "3a":
                    self.update_book()
                elif command == "3b":
                    self.update_client()
                elif command == "4a":
                    self.add_book()
                elif command == "4b":
                    self.add_client()
                elif command == "5a":
                    self.search_book()
                elif command == "5b":
                    self.search_client()
                elif command == "6a":
                    self.rent_book()
                elif command == "6b":
                    self.return_book()
                elif command == "7":
                    print(self._rental_services.statistic_by_book_rentals())
                elif command == "8":
                    print(self._rental_services.statistic_most_active_clients())
                elif command == "9":
                    print(self._rental_services.statistic_most_rented_author())

