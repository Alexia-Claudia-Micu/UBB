import unittest
from src.repository.repo import Repository
from src.domain.book import Book


class Testing(unittest.TestCase):
    def test_store(self):
        repo = Repository()
        book = Book(1, "Deadcrush", "Alt-J")
        repo.store(book)
        self.assertIn(book, repo.get_all())
        #print("Addition functional")

    def test_update(self):
        repo = Repository()
        book = Book(1, "Deadcrush", "Alt-J")
        repo.store(book)
        self.assertIn(book, repo.get_all())
        book = Book(1, "Nara", "Glass")
        repo.update(book)
        self.assertIn(book, repo.get_all())
        #print("Update functional")

    def test_delete(self):
        repo = Repository()
        book1 = Book(1, "Deadcrush", "Alt-J")
        repo.store(book1)
        book2 = Book(2, "Nara", "Glass")
        repo.store(book2)
        repo.delete(1)
        self.assertNotIn(book1, repo.get_all())
        #print("Delete functional")


if __name__ == '__main__':
    unittest.main()
