from src.ui.ui_exceptions import UIException
from src.repository.repo_exception import RepositoryException
from src.domain.domain_exception import DomainException
from src.domain.ship import Ship
from random import choice, randint
from src.services.services import Service
class UI:

    def __init__(self):
        self._service = Service()
        self._player_hits = 0
        self._computer_hits = 0
        self._computer_next_moves = []

    def _validate_input_coord(self, coord): # techanlly make a class utils cu validators
        if len(coord) > 1 and coord != '10':
            raise UIException("Incorrect coordinate")
        if coord > "9" or coord < "1":
            raise UIException("Incorrect coordinate")

    def _validate_input_orientation(self, o):
        orient = {"v": "vertical", 'h': "horizontal"}
        if o not in ["v", "h"]:
            raise UIException("Incorrect orientation")
        return orient[o]

    def _read_player_board(self):
        ship_types = {5: 'carrier', 4: 'battleship', 3: 'destroyer', 2: 'submarine', 1: 'patrol boat'}
        ship_code = {"unmarked": "    unmarked   ", "carrier": "    carrier    ", "battleship": '   battleship  ', "destroyer": '   destroyer   ', "submarine": '   submarine   ', "patrol boat": '  patrol boat  ', "hit_carrier": "  hit_carrier  ", 'hit_battleship': ' hit_battleship', 'hit_destroyer': ' hit_destroyer ', 'hit_submarine': ' hit_submarine ', 'hit_patrol boat': 'hit_patrol boat', "       X       ": "       X       "}
        for i in range(1, 6):
            sem = 0
            while sem == 0:
                try:
                    print(f"Please input coordinates for the {ship_types[i]} ship")
                    row = input("row > ")
                    self._validate_input_coord(row)
                    column = input("column > ")
                    self._validate_input_coord(column)
                    orientation = input("orientation (v for vertical and h for horizontal) > ")
                    orientation = self._validate_input_orientation(orientation)
                    code = ship_code[ship_types[i]]
                    new_ship = Ship(code, int(row), int(column), orientation)
                    self._service.add_ship("player", new_ship)
                except UIException as ie:
                    print(f"There was a {type(ie)}: {ie}")
                except DomainException as de:
                    print(f"There was a {type(de)}: {de}")
                except RepositoryException as re:
                    print(f"There was a {type(re)}: {re}")
                else:
                    sem = 1

    def start_game(self):
        '''
        generate_boards
        1a. Player 1 places ships
            - place ship (service) : input x ship : orientation, coords
                                    - adds ship or returns an error
        1b. Computer generates the ships
            - randomly generates ships
        '''
        self._read_player_board()
        self._service.generate_board()
        print(self._service)

    def play_game(self):
        '''
        2. Take turns attacking
        - In the service there's going to be a method that receives a board and the attacks that board at given coords
            > player 1
            - attack - input : coords + returns miss or hit

            > computer
            - attacks - First of all - random moves, but no overlapping
                      - secondly - strategy


        - if the entire ship is hit -> print ship_name down
        - after the player or the board attacks, both are printed

        - game stops when either player_hits or computer_hits equals 17 (max hits)
        :return:
        '''
        print("-----------------------------")
        print("The game has started.")
        coin_toss = choice(["player", "computer"])
        print(f"Coin toss: {coin_toss} gets to move first")
        print("-----------------------------")

        while self._player_hits < 17 and self._computer_hits < 17:
            print(f"{coin_toss}'s turn.")
            if coin_toss == "player":
                self._player_attacks()
                coin_toss = "computer"
            else:
                self.computer_attacks()
                coin_toss = "player"
            if coin_toss == "player":
                print("---------------------------------------------------------------------------------------")
                print(self._service)
                print("---------------------------------------------------------------------------------------")
        if self._player_hits == 17:
            print("player wins")
        else:
            print("computer wins")

    def _player_attacks(self):
        sem = 0
        while sem == 0:
            try:
                print(f"Please input coordinates for the attack")
                row = input("row > ")
                self._validate_input_coord(row)
                column = input("column > ")
                self._validate_input_coord(column)
                outcome = self._service.attack("computer", int(row), int(column))
            except UIException as ie:
                print(f"There was a {type(ie)}: {ie}")
            except DomainException as de:
                print(f"There was a {type(de)}: {de}")
            except RepositoryException as re:
                print(f"There was a {type(re)}: {re}")
            else:
                sem = 1
                if outcome != "miss":
                    self._player_hits += 1
                print(outcome)

    def computer_attacks(self):
        sem = 0
        while sem == 0:
            try:
                pair = self._get_computer_move()
                row = pair[0]
                column = pair[1]
                print(f"Computer attacks row {str(row)}, column {str(column)}")
                outcome = self._service.attack("player", int(row), int(column))
            except RepositoryException as re:
                #pass
                print(f"There was a {type(re)}: {re}")
            else:
                sem = 1
                if outcome != "miss":
                    self._computer_hits += 1
                    self._append_next_moves(row, column)
                print(outcome)

    def _get_computer_move(self):
        '''
        if the computer has better moves that it can execute, it will
        otherwise, it will choose randomly
        :return: a pair with the chosen coords
        '''
        if len(self._computer_next_moves) != 0:
            top = len(self._computer_next_moves) - 1
            pair = self._computer_next_moves[top]
            row = pair[0]
            column = pair[1]
            self._computer_next_moves.pop(top)
            return [row, column]
        else:
            row = randint(1, 10)
            column = randint(1, 10)
        return [row, column]

    def _check_moves(self, row, column):
        '''checks whether the cell has valid coords'''
        if row > 10 or row < 1 or column > 10 or column < 1:
            return False
        return True

    def _append_next_moves(self, row, column):
        '''
        uses direction vectors to add the sorrounding elements to a stack s.t. there is a higher chance to hit
        '''
        di = [-1, 0, 1, 0]
        dj = [0, 1, 0, -1]
        for t in range(4):
            new_row = row + di[t]
            new_column = column + dj[t]
            if self._check_moves(new_row, new_column) == True and self._check_moves(-1 * new_row, -1 * new_column) == True:
                if self._service.get_pb_val(row, column) == self._service.get_pb_val(new_row, new_column):
                    self._computer_next_moves.append([-1 * new_row, -1 * new_column])
        for t in range(4):
            new_row = row + di[t]
            new_column = column + dj[t]
            if self._check_moves(new_row, new_column) == True:
                    self._computer_next_moves.append([ new_row, new_column])
