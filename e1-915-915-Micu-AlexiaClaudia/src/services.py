from repo import Repository
from exceptions import ServiceException
from exceptions import GameOverExeption
from random import randint

class Service:
    def __init__(self):
        self._repo = Repository(100, 1000, 2800)
        self._came = 0
        self._starved = 0
        self._harvest = 3
        self._rats = 200
        self._land_price = 20

    def __str__(self):
        return f"In year {str(self._repo.year)}, {str(self._starved)} people starved.\n{str(self._came)} people came to the city.\nCity population is {str(self._repo.population)}\nCity owns {str(self._repo.acres)} acres of land.\nHarvest was {str(self._harvest)} units per acre.\nRats ate {str(self._rats)} units.\nLand price is {str(self._land_price)} units per acre.\n\nGrain stacks are {str(self._repo.grain)} units"

    def check_acres(self, value):
        '''
        - checks if the value parameter is suitable to represent acres
            - if you have the land from which you're trying to sell
            - if you have the grain with which you're trying to buy
        :param value: integer
        :return: raises and error if "value" cannot be interpreted as a parameter fot acres, nothing otherwise
        '''
        if value >= 0:
            if value * self._land_price > self._repo.grain:
                raise ServiceException("Cannot buy more land than you have grain for.")
        elif value < 0:
            if (-1) * value > self._repo.acres:
                raise ServiceException("Cannot sell more land than you have money to buy.")

    def check_feed(self, acres, feed):
        '''
        - checks if the feed parameter is suitable to represent amount of food given to people
            - if you have the grain you want to give to people (taking into consideration the previous land buy/sell)
        :
        :param acres: integer
        :param feed: integer
        :return: raises and error if "feed" cannot be interpreted as a parameter for food, nothing otherwise
        '''
        if acres < 0:
            extra = self._land_price * (-1) * acres
        else:
            extra = (-1) * self._land_price * acres
        if feed > self._repo.grain + extra:
            raise ServiceException("Cannot feed people more grain than you have.")

    def check_plant(self, acres, feed, plant):
        '''
        - checks if the plant parameter is suitable to represent amount of land you can plant
            - if you have the grain you want to plant (taking into consideration the previous land buy/sell)
            - if you have the land on which you want to plant (taking into consideration the previous land buy/sell)
        :
        :param acres: integer
        :param feed: integer
        :param plant: integer
        :return: raises and error if "feed" cannot be interpreted as a parameter for food, nothing otherwise
        '''
        if acres < 0:
            extra = self._land_price * (-1) * acres
        else:
            extra = (-1) * self._land_price * acres
        if self._repo.grain - feed + extra < plant:
            raise ServiceException("Cannot plant more grain than you have.")
        if plant > self._repo.acres + acres:
            raise ServiceException("Cannot plant on land you do not own.")

    def pass_year(self, acres, feed, plant):
        '''
        1. Modifies the land you owe based on the acres parameter
            - affects the grain also
            - updates the land price for the next year
        2. Uses feed parameter to feed people and decide how many survive
            - the game ends if it is less than half
            - randomizes the people that come into city as a result of everyone getting fed
        3. Plants the grain and decides how much is harvested
            - it has to decide if the manpower is able to harvest the required, otherwise, it harvests what is can
        4. Decides if there was a rat infestation
        5. Increases the year
        :param acres: integer
        :param feed:  integer
        :param plant:  integer
        '''
        #   1
        # land is bought/sold
        if acres < 0:
            self._repo.grain += self._land_price * (-1) * acres
            self._repo.acres += acres
        else:
            self._repo.grain -= self._land_price * acres
            self._repo.acres += acres
        # land price varies between 15-20
        self._land_price = randint(15, 25)

        #   2
        #grain used to feed people is subtracted
        self._repo.grain -= feed
        #each person needs 20 grain
        people_survive = feed // 20
        #game is over if more than half the population died
        if self._repo.population > 2 * people_survive:
            raise GameOverExeption("More than half the population has died")
        if people_survive <= self._repo.population:
            self._starved = self._repo.population - people_survive
        else:
            self._starved = 0
        #people come to the city
        if self._repo.population <= people_survive:
            self._came = randint(0, 10)
        else:
            self._came = 0
        self._repo.population = min(people_survive, self._repo.population)

        self._repo.population += self._came

        #   3
        #grain is planted
        self._repo.grain -= plant
        #grain is harvested - 10 acres/person
        #harvest - random in 1,6
        self._harvest = randint(1, 6)
        harvested_grain = min(self._repo.population*10, plant)
        self._repo.grain += harvested_grain * self._harvest

        #   4
        #rat infestation is 20% ;chance is 1 of 5
        rat_infestation = randint(1, 5)
        if rat_infestation == 1:
            self._rats = self._repo.grain - ((self._repo.grain*9) // 10)
            self._repo.grain -= self._rats
        else:
            self._rats = 0

        #   5
        #year increases
        self._repo.year += 1

    def ending_message(self):
        '''
        - check how the player did based on the population and land
        :return: return the end-of-game message
        '''
        if self._repo.population > 100 and self._repo.acres > 1000:
            return "GAME OVER. You prospered !"
        return "GAME OVER. You did not do so well"

if __name__ == "__main__":
    serv = Service()
    print(serv)