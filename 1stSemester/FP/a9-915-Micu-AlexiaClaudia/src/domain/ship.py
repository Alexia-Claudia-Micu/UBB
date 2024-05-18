from random import randint, choice

class Ship:
    '''
    Each ship must have;
        - name - string
        - top left coordinate - integer in [1, 10]
        - orientation - h(horizontal) or (vertical)
    Domain "ship" has no setters because you cannot change the position of a ship
    '''
    def __init__(self, name, row, column, orientation):
        self._name = name
        self._row = row
        self._column = column
        self._orientation = orientation

    def lenght(self):
        '''
        :return: the lenght of the ship type
        '''
        values = {"    unmarked   ": "unmarked", "    carrier    ": "carrier", '   battleship  ': "battleship", '   destroyer   ': "destroyer", '   submarine   ': "submarine", '  patrol boat  ': "patrol boat", "  hit_carrier  ": "hit_carrier", ' hit_battleship': 'hit_battleship', ' hit_destroyer ': 'hit_destroyer', ' hit_submarine ': 'hit_submarine', 'hit_patrol boat': 'hit_patrol boat', "       X       ": "       X       "}
        ship_types = {'carrier': 5, 'battleship': 4, 'destroyer': 3, 'submarine': 3, 'patrol boat': 2}
        return ship_types[values[self._name]]

    @property
    def name(self):
        return self._name

    @property
    def row(self):
        return self._row

    @property
    def column(self):
        return self._column

    @property
    def orientation(self):
        return self._orientation

    def generate_ship(self):
        '''
        Generates random values for a ship
        :return:
        '''
        self._row = randint(1, 10)
        self._column = randint(1, 10)
        self._orientation = choice(["vertical", "horizontal"])