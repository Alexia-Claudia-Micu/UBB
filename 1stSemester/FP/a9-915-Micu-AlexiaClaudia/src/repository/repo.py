from src.domain.board import Board
from src.repository.repo_exception import RepositoryException
from src.domain.domain_exception import DomainException
from src.domain.ship import Ship
class Repository:
    '''
    each repo has just one board
    My repo and the computer's repo
    Methods :
    - add ship : receives type, coord and orientation + not possible; adds ships
     - add carrier, etc
    - attack : receives coords, marks hit or miss, returns hit or miss
    - generate board
    '''

    def get_pb_val(self, row, column):
        return self._player_board.get_cell_value(row, column)

    def __init__(self):
        '''
        - has a board for the player and one for the computer
        '''
        self._player_board = Board("player")
        self._computer_board = Board("computer")

    def add_ship(self, player: str, new_ship: Ship):
        '''
        Adds the given ship to its corresponding board
        :param player: string representing the player or computer
        :param new_ship: a Ship which is to be added
        '''
        if player == "player":
            self._player_board.add_ship(new_ship)
        else:
            self._computer_board.add_ship(new_ship)

    def attack(self, player, row, column):
        '''
        Attacks the cell identified by row and column
        :param player: the player/computer's board which is to be attacked
        :param row: cell row - int in [1,10]
        :param column: cell column - int in [1, 10]
        :return: the outcome : miss or hit[ship name]
        '''
        key = f"r:{str(row)},c:{str(column)}"
        if player == "player":
            outcome = self._player_board.attack_cell(key)
        else:
            outcome = self._computer_board.attack_cell(key)
        return outcome

    def generate_board(self):
        '''
        Generates a board:
            - for each ship type, it generates a random position and checks it
        '''
        ship_types = {5: 'carrier', 4: 'battleship', 3: 'destroyer', 2: 'submarine', 1: 'patrol boat'}
        ship_code = {"unmarked": "    unmarked   ", "carrier": "    carrier    ", "battleship": '   battleship  ', "destroyer": '   destroyer   ', "submarine": '   submarine   ', "patrol boat": '  patrol boat  ', "hit_carrier": "  hit_carrier  ", 'hit_battleship': ' hit_battleship', 'hit_destroyer': ' hit_destroyer ', 'hit_submarine': ' hit_submarine ', 'hit_patrol boat': 'hit_patrol boat', "       X       ": "       X       "}
        for i in [5, 4, 3, 2, 1]:
            sem = 0
            while sem == 0:
                try:
                    new_ship = Ship(ship_code[ship_types[i]], None, None, None)
                    new_ship.generate_ship()
                    self.add_ship("computer", new_ship)
                except DomainException:
                    sem = 0
                except RepositoryException:
                    sem = 0
                else:
                    sem = 1

    def __str__(self):
        '''
        string of the repository
        :return: the concatenated player(revealed) and computer board(concealed)
        '''
        rez = ""
        rez += "Player's Board:\n"
        rez += str(self._player_board)
        rez += "\n\nComputer's Board:\n"
        rez += str(self._computer_board)
        return rez
