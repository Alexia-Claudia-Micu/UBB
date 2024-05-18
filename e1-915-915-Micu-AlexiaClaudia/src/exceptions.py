class UIException(Exception):
    def __init__(self, message):
        self._message = message
    def __str__(self):
        return str(self._message)

class ServiceException(Exception):
    def __init__(self, message):
        self._message = message
    def __str__(self):
        return str(self._message)

class GameOverExeption(Exception):
    def __init__(self, message):
        self._message = message
    def __str__(self):
        return str(self._message)