from services import Service
from exceptions import *

class UI:
    def __init__(self):
        self._service = Service()

    def start_game(self):
        print("---------------------------------------------------------")
        for year in range(1, 6):
            print(self._service)
            print("---------------------------------------------------------")
            sem = 0
            while sem == 0:
                try:
                    acres = int(input("Acres to buy/sell (+/-) -> "))
                    self._service.check_acres(acres)
                    feed = int(input("Units to feed the population -> "))
                    self._service.check_feed(acres, feed)
                    plant = int(input("Acres to plant -> "))
                    self._service.check_plant(acres, feed, plant)
                    self._service.pass_year(acres, feed, plant)
                except ValueError as ve:
                    print(f"There was a {str(type(ve))}, with message {str(ve)}")
                except ServiceException as ve:
                    print(f"There was a {str(type(ve))}, with message {str(ve)}")
                except GameOverExeption as ge:
                    print(f"You have lost because: {str(ge)}")
                    return
                else:
                    sem = 1
                finally:
                    print("---------------------------------------------------------")
        print(self._service)
        print(self._service.ending_message())
