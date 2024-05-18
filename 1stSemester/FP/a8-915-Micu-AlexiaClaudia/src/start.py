from src.repository.repo import Repository
from src.services.BookServices import BookService
from src.services.ClientServices import ClientService
from src.services.RentalServices import RentalService
from src.repository.repository_exception import RepositoryException
from src.domain.book import Book
from src.domain.client import Client
from src.domain.rental import Rental
from src.ui.ui import UserInterface
from random import choice, randint
from datetime import date

def add_rand_book(self, id):
    prefixes = ["The", "Some", "A few"]
    nouns = ['Whale', 'Cyclone', 'Wave', 'Giraffe', 'Monkeys', 'Umbrella', "Dreams", "Chamber", "Secrets"]
    connectors = ["and", "with"]
    title = choice(prefixes) + " " + choice(nouns) + " " + choice(connectors) + " " + choice(prefixes) + " " + choice(
        nouns)

    authors = ["J. K. Rowling", "James Dashner", "Emily Osman", "E. Lockhart", "John Green", "Stephen King"]
    author = choice(authors)

    new_book = Book(id, title, author)
    self.store(new_book)

def add_books(self, nr: int):
    for i in range(nr):
        add_rand_book(self, i)

def add_rand_clients(self, id):
    names = {"First Name": ["Olivia", "Emma", "Charlotte", "Amelia", "Ava", "Sophia", "Jude", "Milo", "Malachi",
                            "Charlie", "Ira", "Molly", "Paul", "Bailey", "Rebecca", "Sage", "Ezekiel", "Brianna",
                            "Elora", "Simon", "Leon"],
             'Last Name': ["Smith", "Johnson", "Williams", "Miller", "Davis", "Garcia", "Brown", "Evans", "Moore",
                           "Taylor", "Walker", "Baker"]}
    name = choice(names['First Name']) + " " + choice(names["Last Name"])
    client = Client(id, name)
    self.store(client)

def add_clients(self, nr: int):
    for i in range(nr):
        add_rand_clients(self, i)

def rand_rentals(self, id):
    book_id = randint(0, 19)
    client_id = randint(0, 19)
    start_date = 1
    end_date = 0
    while start_date > end_date:
        start_date = date(randint(2020, 2022), randint(1, 12), randint(1, 28))
        end_date = date(randint(2022, 2022), randint(1, 12), randint(1, 28))
    # while end_date - start_date > 60:
    #    end_date = date(randint(start_date.year, 2022), randint(start_date.month + 1, 12), randint(1, 28))
    new_rental = Rental(id, book_id, client_id, start_date, end_date)
    return new_rental

def add_rentals(self, nr: int):
    book_rents = {}
    for i in range(nr):
        sem = 0
        while sem == 0:
            rental = rand_rentals(self, i)
            rez = book_rents.keys()
            expr = rental.book_id in rez
            if expr == False:
                book_rents[rental.book_id] = []
                sem = 1
            else:
                for r in book_rents[rental.book_id]:
                    ok = 1
                    if rental.rented_date < r.rented_date and rental.returned_date > r.rented_date:
                        ok = 0
                    elif rental.rented_date > r.rented_date and rental.rented_date < r.returned_date:
                        ok = 0
                    sem = ok
        book_rents[rental.book_id].append(rental)
        self.store(rental)

if __name__ == "__main__":
    print("915 - Micu Alexia-Claudia")

    book_repo = Repository()
    client_repo = Repository()
    rental_repo = Repository()
    add_books(book_repo, 20)
    add_rentals(rental_repo, 20)
    add_clients(client_repo, 20)

    book_services = BookService(book_repo, client_repo, rental_repo)
    client_services = ClientService(book_repo, client_repo, rental_repo)
    rental_services = RentalService(book_repo, client_repo, rental_repo)

    UI = UserInterface(book_services, client_services, rental_services)
    UI.menu()