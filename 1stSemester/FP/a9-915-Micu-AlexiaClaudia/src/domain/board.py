from src.domain.cell import Cell
from src.domain.ship import Ship
from src.domain.domain_exception import DomainException
from src.repository.repo_exception import RepositoryException

class Board:
    ''''
    Each board will have
     - list of cells
     - each cell is a class that has coords, value
     - dimensions: height and width: constants = 10

     - 2 print methods
    '''

    def __init__(self, name):
        '''
        Board has a name: Player/Computer
        A dictionary "data" which holds the cells - dictionary keys are string composed of the row and column
            - initializes all cells as empty
        :param name: player/computer
        '''
        self._name = name
        self._data = {}

        for i in range(1, 11):
            for j in range(1, 11):
                key = f"r:{str(i)},c:{str(j)}"
                self._data[ key ] = Cell(i, j, "    unmarked   ")

    def _get_cell_value(self, key):
        # returns the value of the cell identified by its row and column (key)
        return self._data[key].value

    def get_value(self, row, column):
        key = f"r:{str(row)},c:{str(column)}"
        return self._get_cell_value(key)

    def get_cell_value(self, row, column):
        key = f"r:{str(row)},c:{str(column)}"
        ship_types = ["hit_carrier", "hit_battleship", 'hit_patrol boat', 'hit_submarine', 'hit_destroyer']
        for ship in ship_types:
            if ship in self._get_cell_value(key):
                return ship
        return "none"

    def _set_cell_value(self, key, new_value):
        # sets the value of the cell identified by its row and column (key) to the new value
        self._data[key].value = new_value

    def _validate_space(self, new_ship: Ship):
        '''
        Checks if the space where the new ship is to be added is clear
        :param new_ship: ship to be added
        '''
        new_row = new_ship.row
        new_column = new_ship.column
        if new_ship.orientation == "vertical":
            di = 1
            dj = 0
        else:
            dj = 1
            di = 0
        lenght = new_ship.lenght()
        for i in range(lenght):
            key = f"r:{str(new_row)},c:{str(new_column)}"
            if new_row > 10 or new_row < 1 or new_column > 10 or new_column < 1:
                raise RepositoryException("Index out of range")
            if self._get_cell_value(key) != "    unmarked   ":
                raise DomainException("Ship Already Exists")
            else:
                new_row = new_row + di
                new_column = new_column + dj

    def add_ship(self, new_ship: Ship):
        '''
        Adds the new ship if it can
        :param new_ship: ship to be added
        '''
        self._validate_space(new_ship)
        new_row = new_ship.row
        new_column = new_ship.column
        if new_ship.orientation == "vertical":
            di = 1
            dj = 0
        else:
            dj = 1
            di = 0
        lenght = new_ship.lenght()
        for i in range(lenght):
            key = f"r:{str(new_row)},c:{str(new_column)}"
            new_row = new_row + di
            new_column = new_column + dj
            self._set_cell_value(key, new_ship.name)

    def _str_open(self):
        '''
            - creates the first line composed of the column names
            - appends it to the result
            - for each line, it appends the line number and the cell value
        :return: a string representing the matrix
        '''
        empty = ""
        rez = " 0|        "
        for i in range(1, 10):
            rez += str(i) + "        |        "
            empty += "----"
        empty += "---"
        new_line = f"\n"
        #new_line = f"\n{empty}\n"
        rez += f'10       |{new_line} 1| '
        prev_r = 1
        for key in self._data:
            elem = self._data[key]
            if elem.row != prev_r:
                prev_r += 1
                if elem.row != 10:
                    rez += f'{new_line} {str(elem.row)}| '
                else:
                    rez += f'{new_line}{str(elem.row)}| '
            rez += str(elem) + " | "
        return rez

    def _str_closed(self):
        '''
            - creates the first line composed of the column names
            - appends it to the result
            - for each line - it appends the line number
                            - if appends '?' if line has not been attacked
                            - if line has been attacked and is a miss
                            - if line has been attacked and is a miss
        :return: a string representing the matrix
        '''
        empty = ""
        rez = " 0|        "
        for i in range(1, 10):
            rez += str(i) + "        |        "
            empty += "----"
        empty += "---"
        new_line = f"\n"
        #new_line = f"\n{empty}\n"
        rez += f'10       |{new_line} 1| '
        prev_r = 1
        for key in self._data:
            elem = self._data[key]
            if elem.row != prev_r:
                prev_r += 1
                if elem.row != 10:
                    rez += f'{new_line} {str(elem.row)}| '
                else:
                    rez += f'{new_line}{str(elem.row)}| '
            if elem.value not in ["  hit_carrier  ", ' hit_battleship', ' hit_destroyer ', ' hit_submarine ', 'hit_patrol boat', "       X       "]:
                x = "       ?       "
            else:
                x = str(elem.value)

            rez += x + " | "
        return rez

    def attack_cell(self, key):
        '''

        :param key: key by which the attacked cell is identified
        :return: a message as to wether the attack is a miss or a hit and which ship it hit
        '''
        values = {"    carrier    ": "carrier", '   battleship  ': "battleship", '   destroyer   ': "destroyer", '   submarine   ': "submarine", '  patrol boat  ': "patrol boat"}
        hit_ships = {"carrier": "  hit_carrier  ", 'battleship': ' hit_battleship', 'destroyer': ' hit_destroyer ', 'submarine': ' hit_submarine ', 'patrol boat': 'hit_patrol boat'}
        value = self._get_cell_value(key)
        if value in values:
            self._set_cell_value(key, hit_ships[values[value]])
            return f"hit {value}"
        elif value not in ["unmarked", "    unmarked   "]:
            raise RepositoryException("Cannot hit a spot twice")
        else:
            self._set_cell_value(key, "       X       ")
            return "miss"

    def __str__(self):
        '''decides whether to print the board concealed or not'''
        if self._name == "player":
            return self._str_open()
        else:
            return self._str_closed()

if __name__ == "__main__":
    b = Board("player")
    print(b)