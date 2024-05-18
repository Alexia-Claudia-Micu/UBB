from datetime import date
from src.domain.domain_exception import DomainException

class Rental:
    '''
    Each rental must have:
        -> a valid id (unique, integer)
        -> book_id
        -> client_id
        -> rented_date
        -> returned_date
    '''
    def __init__(self, id: int, book_id: int, client_id: int, rented_date: date, returned_date: date):
        self.__id = id
        self.__book_id = book_id
        self.__client_id = client_id
        self.__rented_date = rented_date
        if returned_date != None:
            self.__returned_date = returned_date
        else:
            self.__returned_date = date(1000, 1, 1)

    @property
    def id(self):
        return self.__id

    @property
    def book_id(self):
        return self.__book_id

    @property
    def client_id(self):
        return self.__client_id

    @property
    def rented_date(self):
        return self.__rented_date

    @property
    def returned_date(self):
        return self.__returned_date

    @id.setter
    def id(self, value: int):
        self.__id = value

    @book_id.setter
    def book_id(self, value: int):
        self.__book_id = value

    @client_id.setter
    def client_id(self, value: int):
        self.__client_id = value

    @rented_date.setter
    def rented_date(self, value: date):
        self.__rented_date = value

    @returned_date.setter
    def returned_date(self, value: date):
        self.__returned_date = value

    def __str__(self):
        if self.__returned_date == date(1000, 1, 1):
            return f"Rental {str(self.id)}: book: {str(self.book_id)} by client {str(self.client_id)}, ({self.rented_date} - not yet returned)"
        return f"Rental {str(self.id)}: book: {str(self.book_id)} by client {str(self.client_id)}, ({self.rented_date} -> {str(self.returned_date)})"

def test_rental():
    sd = date(2022, 4, 10)
    ed = date(2022, 8, 1)
    new_rental = Rental(1, 2, 5, sd, ed)
    assert new_rental.id == 1
    assert new_rental.book_id == 2
    assert new_rental.client_id == 5
    assert new_rental.rented_date == sd
    assert new_rental.returned_date == ed
    assert str(new_rental) == "Rental 1: book: 2 by client 5, (2022-04-10 -> 2022-08-01)"
    new_rental.id = 5
    assert new_rental.id == 5
    assert str(new_rental) == "Rental 5: book: 2 by client 5, (2022-04-10 -> 2022-08-01)"

if __name__ == "__main__":
    rental = Rental(1, 2, 3, date(2022, 12, 2), None)
    print(str(rental))
    test_rental()