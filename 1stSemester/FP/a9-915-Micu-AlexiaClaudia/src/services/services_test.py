import unittest
from src.services.services import Service
from src.repository.repo import Repository
from src.domain.board import Board
from src.domain.ship import Ship


class Testing(unittest.TestCase):

    def test_add_attack(self):
        service = Service()
        service.generate_board()
        ship = Ship("    carrier    ", 1, 1, 'v')
        service.add_ship("player", ship)
        self.assertEqual(service.attack("player", 1, 1), 'hit     carrier    ')
        self.assertEqual(service.attack("player", 2, 1), 'miss')

    def test_add_get_val(self):
        service = Service()
        service.generate_board()
        ship = Ship("    carrier    ", 1, 1, 'v')
        service.add_ship("player", ship)
        self.assertEqual(service.get_pb_val(1, 1), 'none')
        service.attack("player", 1, 1)
        self.assertEqual(service.get_pb_val(1, 1), 'hit_carrier')

if __name__ == '__main__':
    unittest.main()
