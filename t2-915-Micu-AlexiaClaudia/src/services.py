from repository import Repository
from random import randint
class Services:
    def __init__(self):
        self._repository = Repository()

    def generate_taxis(self, nr):
        self._repository.generate_taxis(nr)

    def dist(self, x1, y1, x2, y2):
        xs = abs(x1 - x2)
        ys = abs(y1 - y2)
        return xs + ys

    def ride(self, x_start, y_start, x_stop, y_stop):
        taxi = self._repository.get_closest_ride(x_start, y_start)
        fare = self.dist(x_start, y_start, x_stop, y_stop)
        self._repository.change_fare(taxi.id, fare)
        self._repository.change_location(taxi, x_stop, y_stop)
        self._repository.sort()

    def simulate_ride(self, nr_rides):
        rez = ''
        for i in range(nr_rides):
            sem = 0
            while sem == 0:
                x_start = randint(0, 100)
                y_start = randint(0, 100)
                x_stop = randint(0, 100)
                y_stop = randint(0, 100)
                if self.dist(x_start, y_start, x_stop, y_stop) >= 10:
                    sem = 1
            self.ride(x_start, y_start, x_stop, y_stop)
            rez += f"({str(x_start)},{str(y_start)}) to ({str(x_stop)},{str(y_stop)})" + '\n'
        return rez


    def __str__(self):
        return str(self._repository)