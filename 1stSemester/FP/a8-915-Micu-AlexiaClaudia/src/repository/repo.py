from src.repository.repository_exception import RepositoryException

class Repository:
    def __init__(self):
        self._objects = []

    def store(self, obj):
        '''
        Adds the obj to the repository if it does not already exist, otherwise it raises an error
        :param obj: book, client or rental
        '''
        if self.find(obj.id) is not None:
            raise RepositoryException("Element having id=" + str(obj.id) + " already stored!")
        self._objects.append(obj)

    def find(self, id):
        for obj in self._objects:
            if id == obj.id:
                return obj
        return None

    def find_unused_id(self):
        id = 0
        obj = self.find(id)
        while obj != None:
            id += 1
            obj = self.find(id)
        return id

    def update(self, obj):
        '''
        Updates the object from the repository
        :param obj: book, client or rental
        '''
        elem = self.find(obj.id)
        if elem is None:
            raise RepositoryException("Element not found")
        idx = self._objects.index(elem)
        self._objects.remove(elem)
        self._objects.insert(idx, obj)

    def delete(self, id):
        '''
        Deletes the object from the repository
        :param obj: book, client or rental
        '''
        obj = self.find(id)
        if obj is None:
            raise RepositoryException("Element is not in repository")
        self._objects.remove(obj)
        return object

    def get_all(self):
        return self._objects

    def get_list(self):
        return list(self._objects)

    def __len__(self):
        return len(self._objects)

    def __str__(self):
        string = ""
        for obj in self._objects:
            string += str(obj)
            string += "\n"
        return string
