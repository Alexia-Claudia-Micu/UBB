from unittest import TestCase
from services import Service
from exceptions import GameOverExeption

class TestProcessingYear(TestCase):
    def test_land_buy(self):
        city = Service()
        city.pass_year(100, 2000, 0)
        self.assertIn("City owns 1100 acres of land", str(city))

    def test_land_sell(self):
        city = Service()
        city.pass_year(-100, 2000, 0)
        self.assertIn("City owns 900 acres of land", str(city))

    def test_half_dies(self):
        city = Service()
        city.pass_year(0, 1000, 0)
        self.assertIn("50 people starved", str(city))

    def test_everyone_lives(self):
        city = Service()
        city.pass_year(0, 2000, 0)
        self.assertIn("0 people starved", str(city))

    def test_grain_planting(self):
        city = Service()
        city.pass_year(0, 2000, 800)
        result = str(city).split(" ")
        self.assertGreater(int(result[len(result)-2]), 799)

    def test_result(self):
        city = Service()
        city.pass_year(0, 1000, 1800)
        city.pass_year(0, 1000, 1800)
        city.pass_year(0, 1000, 1800)
        city.pass_year(0, 1000, 1800)
        city.pass_year(0, 1000, 1800)
        self.assertEqual(city.ending_message(), "GAME OVER. You did not do so well")