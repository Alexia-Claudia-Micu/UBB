import unittest
from cell import Cell


class Testing(unittest.TestCase):
    def test_str(self):
        cell = Cell(1, 1, "value")
        self.assertEqual(str(cell), "value")
        #print("Addition functional")

if __name__ == '__main__':
    unittest.main()
