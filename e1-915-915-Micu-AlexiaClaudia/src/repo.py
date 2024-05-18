
class Repository:
    def __init__(self, people, land, grain):
        self._year = 1
        self._population = people
        self._acres = land
        self._grain = grain

    @property
    def year(self):
        return self._year

    @property
    def population(self):
        return self._population

    @property
    def acres(self):
        return self._acres

    @property
    def grain(self):
        return self._grain

    @year.setter
    def year(self, value):
        self._year += 1

    @acres.setter
    def acres(self, value):
        self._acres = value

    @population.setter
    def population(self, value):
        self._population = value

    @grain.setter
    def grain(self, value):
        self._grain = value

