import unittest
from board import Board
from cell import Cell
from ship import Ship


class Testing(unittest.TestCase):
    def test_add_ship(self):
        ship = Ship("    carrier    ", 1, 1, 'v')
        board = Board('player')
        board.add_ship(ship)
        self.assertEqual(board.get_value(1, 1), "    carrier    ")
        self.assertEqual(board.get_value(1, 2), "    carrier    ")
        self.assertEqual(board.get_value(1, 3), "    carrier    ")
        self.assertEqual(board.get_value(1, 4), "    carrier    ")
        self.assertEqual(board.get_value(1, 5), "    carrier    ")

if __name__ == '__main__':
    unittest.main()
