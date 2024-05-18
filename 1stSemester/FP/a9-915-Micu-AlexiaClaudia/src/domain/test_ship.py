import unittest
from ship import Ship


class Testing(unittest.TestCase):
    def test_len(self):
        ship = Ship("    carrier    ", 1, 1, 'v')
        self.assertEqual(ship.lenght(), 5)
        #print("Addition functional")

if __name__ == '__main__':
    unittest.main()
