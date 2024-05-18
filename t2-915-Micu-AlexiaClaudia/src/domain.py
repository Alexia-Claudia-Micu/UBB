class Taxi:
    def __init__(self, id, x_location, y_location):
        self._id = id
        self._fare = 0
        self._x = x_location
        self._y = y_location

    @property
    def id(self):
        return self._id

    @property
    def fare(self):
        return self._fare

    @property
    def x_location(self):
        return self._x

    @property
    def y_location(self):
        return self._y

    @fare.setter
    def fare(self, new_value):
        self._fare = new_value

    @x_location.setter
    def x_location(self, new_value):
        self._x = new_value

    @y_location.setter
    def y_location(self, new_value):
        self._y = new_value

    def __str__(self):
        return f"Taxi {str(self._id)}, Location: ({str(self._x), str(self._y)}), fare: {str(self._fare)})"
