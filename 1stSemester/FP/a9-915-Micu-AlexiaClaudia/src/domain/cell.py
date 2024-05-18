class Cell:
    def __init__(self, row: int, column: int, value: int):
        self._row = row
        self._column = column
        self._value = value

    @property
    def row(self):
        return self._row

    @property
    def column(self):
        return self._column

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, new_value):
        self._value = new_value

    def __str__(self):
        return self._value

if __name__ == "__main__":
    cell = Cell(1, 1, "unmarked")
    print(cell)