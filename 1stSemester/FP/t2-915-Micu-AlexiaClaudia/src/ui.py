from services import Services
from random import randint
class Ui:
    def __init__(self):
        self._services = Services()

    def list(self):
        print(str(self._services))

    def start(self):
        nr_taxis = int(input("Give number of taxis > "))
        self._services.generate_taxis(nr_taxis)
        self.list()

    def add_rides(self):
        nr_rides = int(input("How many rides > "))
        for i in range(nr_rides):
            x_start = int(input("give x start > "))
            y_start = int(input("give y start > "))
            x_stop = int(input("give x stop > "))
            y_stop = int(input("give x stop > "))
            self._services.ride(x_start,y_start,x_stop,y_stop)
            self.list()

    def simulate_rides(self):
        nr_rides = int(input("How many rides > "))
        rides = self._services.simulate_ride(nr_rides)
        print(rides)
        self.list()

    def menu(self):
        command = 0
        while command != "0":
            print("1. Add rides")
            print("2. Simulate rides")
            print("0.Quit")
            print("--------")
            command = input("Give command > ")
            if command == "1":
                self.add_rides()
            elif command == "2":
                self.simulate_rides()

if __name__ == "__main__":
    interface = Ui()
    interface.start()
    interface.menu()
