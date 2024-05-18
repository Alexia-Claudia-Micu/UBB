import unittest
from src.repository.repo import Repository
from src.services.BookServices import BookService
from src.domain.book import Book
from src.services.ClientServices import ClientService
from src.domain.client import Client


class Testing(unittest.TestCase):
    def test_Book_add(self):
        b_repo = Repository()
        c_repo = Repository()
        r_repo = Repository()
        book_s = BookService(b_repo, c_repo, r_repo)
        book = Book(1, "Deadcrush", "Alt-J")
        book_s.add(1, "Deadcrush", "Alt-J")
        self.assertEqual(str(book)+'\n', str(book_s))
        print("Book Addition functional")

    def test_Client_add(self):
        b_repo = Repository()
        c_repo = Repository()
        r_repo = Repository()
        client_s = ClientService(b_repo, c_repo, r_repo)
        client = Client(1, "Deadcrush")
        client_s.add(1, "Deadcrush")
        self.assertEqual(str(client)+'\n', str(client_s))
        print("Client Addition functional")

    def test_book_update(self):
        b_repo = Repository()
        c_repo = Repository()
        book_1 = BookService(b_repo, b_repo, b_repo)
        book_2 = BookService(c_repo, c_repo, c_repo)
        book_1.add(1, "Deadcrush", "Alt-J")
        book_1.update(1, "Cold Blood", "Alt")
        book_2.add(1, "Cold Blood", "Alt")
        self.assertEqual(book_1.search_by_id(1), book_2.search_by_id(1))
        print("Update functional")

    def test_client_update(self):
        b_repo = Repository()
        c_repo = Repository()
        client_1 = ClientService(b_repo, b_repo, b_repo)
        client_2 = ClientService(c_repo, c_repo, c_repo)
        client_1.add(1, "Deadcrush")
        client_1.update(1, "Cold Blood")
        client_2.add(1, "Cold Blood")
        self.assertEqual(client_1.search_by_id(1), client_2.search_by_id(1))
        print("Update functional")

    def test_book_remove(self):
        b_repo = Repository()
        c_repo = Repository()
        r_repo = Repository()
        book_s = BookService(b_repo, c_repo, r_repo)
        empty_s = BookService(b_repo, c_repo, r_repo)
        book_s.add(1, "Deadcrush", "Alt-J")
        book_s.delete_book(1)
        self.assertEqual(book_s.get_list(), empty_s.get_list())
        print("Delete functional")

    def test_client_remove(self):
        b_repo = Repository()
        c_repo = Repository()
        r_repo = Repository()
        client_s = ClientService(b_repo, c_repo, r_repo)
        empty_s = ClientService(b_repo, c_repo, r_repo)
        client_s.add(1, "Deadcrush")
        client_s.delete_client(1)
        self.assertEqual(client_s.get_list(), empty_s.get_list())
        print("Delete functional")


if __name__ == '__main__':
    unittest.main()
