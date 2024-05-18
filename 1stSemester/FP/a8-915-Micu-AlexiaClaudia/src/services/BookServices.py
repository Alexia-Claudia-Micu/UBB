from src.domain.book import Book
from src.services.service_exception import ServiceException

def match_string(large_str, small_str):
    n = len(small_str)
    m = len(large_str)
    small_str = small_str.lower()
    large_str = large_str.lower()
    if n > m:
        return False
    for i in range(m):
        if(large_str[i: i + n] == small_str):
            return True
    return False

class BookService:
    def __init__(self, book_repo, client_repo, rental_repo):
        self._repository = book_repo
        self._client_repo = client_repo
        self._rental_repo = rental_repo

    def create_book(self, book_id, title, author):
        book = Book(book_id, title, author)
        self._repository.store(book)

    def delete_book(self, book_id):
        '''
        deletes the book identified by an id
        :param book_id: uique integer
        :return: the popped element
        '''
        book = self._repository.delete(book_id)
        return book

    def list(self):
        '''
        prints the books
        '''
        print(self._repository)

    def add(self, id, title, author):
        '''
        adds a new book to the book repository
        :param id: unique positive integer
        :param title: book title - str > 3
        :param author: book author - str > 3
        '''
        book = Book(id, title, author)
        self._repository.store(book)

    def update(self, id, title, author):
        '''
        updates the book's title and/or author
        :param id: positive integer unique
        :param title: book title - str > 3
        :param author: book author - str > 3
        '''
        book = Book(id, title, author)
        self._repository.update(book)

    def search_by_id(self, id):
        for book in self._repository.get_all():
            if book.id == id:
                return str(book)
        return None

    def search_by_title(self, title):
        result = ""
        for book in self._repository.get_all():
            if match_string(book.title, title):
                result += str(book) + '\n'
        if result != "":
            return result
        return None

    def search_by_author(self, author):
        result = ""
        for book in self._repository.get_all():
            if match_string(book.author, author):
                result += str(book) + '\n'
        if result != "":
            return result
        return None

    def get_list(self):
        return self._repository.get_all()

    def __str__(self):
        rez = ""
        for book in self._repository.get_all():
            rez += str(book) + '\n'
        return rez