from domain import Taxi
from  random import randint
class Repository:
    def __init__(self):
        self._data = []
    def distance(self, taxi1: Taxi, x, y):
        xs = abs(x - taxi1.x_location)
        ys = abs(y - taxi1.y_location)
        return xs + ys
    def taxi_distance(self, taxi1: Taxi, taxi2: Taxi):
        x = abs(taxi2.x_location - taxi1.x_location)
        y = abs(taxi2.y_location - taxi1.y_location)
        return x + y

    def add(self, taxi: Taxi):
        for id in self._data:
            t = self._data[self._data.index(id)]
            if t.id == taxi.id:
                raise KeyError
            if self.taxi_distance(taxi, t) <= 5:
                raise KeyError
        self._data.append(taxi)

    def get_taxi(self, id):
        for taxi in self._data:
            if taxi.id == id:
                return taxi

    def generate_taxis(self, nr):
        for i in range(nr):
            sem = 0
            while sem == 0:
                try:
                    id = i + 1
                    x = randint(0, 100)
                    y = randint(0, 100)
                    taxi = Taxi(id, x, y)
                    self.add(taxi)
                except KeyError:
                    sem = 0
                else: sem = 1

    def __str__(self):
        rez = ""
        for taxi in self._data:
            rez += str(taxi) + '\n'
        return rez

    def get_closest_ride(self, x, y):
        mini = 1000
        id = 0
        for taxi in self._data:
            if self.distance(taxi, x, y) < mini:
                mini = self.distance(taxi, x, y)
                id = taxi.id
        return self.get_taxi(id)

    def change_fare(self, id, fare):
        taxi = self.get_taxi(id)
        taxi.fare = fare
    def sort(self):
        for i in range(len(self._data) - 1):
            for j in range(i+1, len(self._data)):
                taxi1 = self._data[i]
                taxi2 = self._data[j]
                if taxi1.fare < taxi2.fare:
                    self._data[i], self._data[j] = self._data[j], self._data[i]

    def change_location(self, taxi: Taxi, x, y):
        taxi.x_location = x
        taxi.y_location = y


if __name__ == "__main__":
    repo = Repository()
    repo.generate_taxis(10)
    print(repo)
