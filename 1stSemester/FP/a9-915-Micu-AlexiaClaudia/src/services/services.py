from src.repository.repo import Repository
class Service:
    def __init__(self):
        self._repository = Repository()

    def __str__(self):
        return str(self._repository)

    def add_ship(self, player, ship):
        self._repository.add_ship(player, ship)

    def generate_board(self):
        self._repository.generate_board()

    def attack(self, player, row, column):
        return self._repository.attack(player, row, column)

    def get_pb_val(self, row, column):
        return self._repository.get_pb_val( row, column)


x = 1
c = {1:1, 1: [1,1]}
print(str(x) in c)






