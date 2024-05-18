from src.domain.domain_exception import DomainException

class Book:
    '''
    Each book must have:
     -> book_id - integer, unique
     -> title - > 3
     - > author - > 3
    '''

    def __init__(self, id: int, title: str, author: str):
        self.__id = id
        self.__title = title
        self.__author = author

    @property
    def id(self):
        return self.__id

    @property
    def title(self):
        return self.__title

    @property
    def author(self):
        return self.__author

    @id.setter
    def id(self, new_id):
        self.__id = new_id

    @title.setter
    def title(self, new_title):
        self.__title = new_title

    @author.setter
    def author(self, new_author):
        self.__author = new_author

    def __str__(self):
        return f"Book {str(self.__id)}: Title: {self.__title}, Author: {self.__author} "