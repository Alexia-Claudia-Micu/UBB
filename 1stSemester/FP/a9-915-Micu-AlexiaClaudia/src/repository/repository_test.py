import unittest
from src.repository.repo import Repository
from src.domain.board import Board
from src.domain.ship import Ship


class Testing(unittest.TestCase):
    def test_generate(self):
        repo = Repository()
        board_p = Board("player")
        board_c = Board("computer")
        repo.generate_board()
        self.assertIn(str(board_p), str(repo))
        self.assertIn(str(board_c), str(repo))

    def test_add(self):
        board = Board("player")
        ship = Ship("    carrier    ", 1, 1, 'v')
        board.add_ship(ship)
        repo = Repository()
        repo.generate_board()
        repo.add_ship("player", ship)
        self.assertIn(str(board), str(repo))

    def test_attack(self):
        ship = Ship("    carrier    ", 1, 1, 'v')
        repo = Repository()
        repo.generate_board()
        repo.add_ship("player", ship)
        self.assertEqual(repo.attack('player', 1, 5), 'hit     carrier    ')
        self.assertEqual(repo.attack('player', 2, 1), 'miss')


if __name__ == '__main__':
    unittest.main()
