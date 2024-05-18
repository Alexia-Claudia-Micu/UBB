from src.domain.client import Client
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

class ClientService:
    def __init__(self, book_repo, client_repo, rental_repo):
        self._bookRepo = book_repo
        self._repository = client_repo
        self._rental_repo = rental_repo

    def create_client(self, client_id, name):
        client = Client(client_id, name)
        self._repository.store(client)

    def delete_client(self, client_id):
        '''
        deletes the client identified by an id
        :param client_id: uique integer
        :return: the popped element
        '''
        client = self._repository.delete(client_id)
        return client

    def list(self):
        '''
        prints the clients
        '''
        print(self._repository)

    def add(self, id, name):
        '''
        adds a new client to the client repository
        :param id: unique positive integer
        :param name: client name - str > 3
        '''
        client = Client(id, name)
        self._repository.store(client)

    def update(self, id, name):
        '''
        updates the client to have a new name
        :param id: positive integer unique
        :param name: client name str > 3
        '''
        client = Client(id, name)
        self._repository.update(client)

    def search_by_id(self, id):
        for client in self._repository.get_all():
            if client.id == id:
                return str(client)
        return None

    def search_by_name(self, name):
        result = ""
        for client in self._repository.get_all():
            if match_string(client.name, name):
                result += str(client) + '\n'
        if result != "":
            return result
        return None

    def get_list(self):
        return self._repository.get_all()

    def __str__(self):
        rez = ""
        for client in self._repository.get_all():
            rez += str(client) + '\n'
        return rez