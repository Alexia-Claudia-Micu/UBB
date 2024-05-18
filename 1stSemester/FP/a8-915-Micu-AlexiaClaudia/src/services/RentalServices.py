from src.domain.rental import Rental
from src.services.service_exception import ServiceException
from datetime import timedelta

class RentalService:
    def __init__(self, book_repo, client_repo, rental_repo):
        self._bookRepo = book_repo
        self._clientRepo = client_repo
        self._repository = rental_repo

    def create_rental(self, rental_id, book_id, client_id, start, end):
        rental = Rental(rental_id, book_id, client_id, start, end)
        self._repository.store(rental)

    def delete_rental(self, rental_id):
        rental = self._repository.delete(rental_id)
        return rental

    def update_return(self, id, return_date):
        rental = self._repository.find(id)
        rental.returned_date = return_date
        self._repository.update(rental)

    def get_all(self):
        return self._repository.get_all()

    def get_book_client(self, b_id, c_id):
        for rental in self._repository.get_all():
            if rental.book_id == b_id and rental.client_id == c_id:
                return rental.id

    def get_rental_date(self, id):
        rental = self._repository.find(id)
        return rental.rented_date

    def get_renturn_date(self, id):
        rental = self._repository.find(id)
        return rental.rented_date

    def list(self):
        print(self._repository)

    def statistic_most_active_clients(self):
        client_ids = {}
        max_rents = 0
        for rental in self._repository.get_all():
            client_ids[rental.client_id] = 0
        for rental in self._repository.get_all():
            x = rental.returned_date - rental.rented_date
            x = x.days
            client_ids[rental.client_id] += x
            max_rents = max(max_rents, client_ids[rental.client_id])
        result = ""
        for i in range(max_rents, 0, -1):
            for elem in client_ids:
                if client_ids[elem] == i:
                    s = self._clientRepo.find(elem)
                    result += str(s) + '\n'
        return result

    def statistic_by_book_rentals(self):
        book_rentals = {}
        max_rents = 0
        for rental in self._repository.get_all():
            book_rentals[rental.book_id] = 0
        for rental in self._repository.get_all():
            book_rentals[rental.book_id] += 1
            max_rents = max(max_rents, book_rentals[rental.book_id])
        result = ""
        for i in range(max_rents, 0, -1):#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            for elem in book_rentals:
                if book_rentals[elem] == i:
                    s = self._bookRepo.find(elem)
                    result += str(s) + '\n'
        return result

    def statistic_most_rented_author(self):
        authors = {"J. K. Rowling": 0, "James Dashner": 0, "Emily Osman": 0, "E. Lockhart": 0, "John Green": 0, "Stephen King": 0}
        max_rentals = 0
        for rental in self._repository.get_all():
            book_id = rental.book_id
            book = self._bookRepo.find(book_id)
            author = book.author
            authors[author] += 1
            max_rentals = max(authors[author], max_rentals)
        result = ""
        while max_rentals >= 0:
            for author in authors:
                if authors[author] == max_rentals:
                    result = result + author + '\n'
            max_rentals -= 1
        return result




