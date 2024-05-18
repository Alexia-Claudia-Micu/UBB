import copy
from random import choice

from src.domain.student import Student


class RepoException(Exception):
    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message


class MemoryRepo:
    def __init__(self):
        # keys are student id's, values are student objects
        self._data = {}

    def add(self, new_student: Student):
        '''
        Adds a student to the repository
        -> receives the student and checks for duplicate unique key
        -> adds a new student to the data in the repository stored like dictionaries
        '''
        if new_student.student_id in self._data:
            raise RepoException("Duplicate id")
        self._data[new_student.student_id] = new_student

    def get(self, student_id: int):
        # If student cannot be found in repo, catch the dict's KeyError and
        # re-raise it as RepoException
        try:
            return self._data[student_id]
        except KeyError:
            raise RepoException("Student is not in repo")

    def get_all(self):
        return list(self._data.values())

    def get_students(self):
        return self._data

    def delete_student(self, id: int):
        del self._data[id]

    def __len__(self):
        return len(self._data)

    def add_rand(self):
        names = {"First Name": ["Olivia", "Emma", "Charlotte", "Amelia", "Ava", "Sophia", "Jude", "Milo", "Malachi",
                                "Charlie", "Ira", "Molly", "Paul", "Bailey", "Rebecca", "Sage", "Ezekiel", "Brianna",
                                "Elora", "Simon", "Leon"],
                 'Last Name': ["Smith", "Johnson", "Williams", "Miller", "Davis", "Garcia", "Brown", "Evans", "Moore",
                               "Taylor", "Walker", "Baker"]}
        groups = [215, 216, 811, 812, 911, 912, 915, 916, 917]
        name = choice(names['First Name']) + " " + choice(names["Last Name"])
        group = choice(groups)
        id = self.find_unused_id()
        student = Student(id, name, group)
        self.add(student)

    def find_unused_id(self):
        id = 0
        try:
            while True:
                id += 1
                self.get(id)
        except KeyError:
            return id
        except RepoException:
            return id

    def add_rand_students(self, nr):
        for i in range(nr):
            self.add_rand()

    def change_data(self, new_lst):
        self._data = copy.deepcopy(new_lst)


def test_add():
    repo = MemoryRepo()
    assert repo.get_students() == {}
    student = Student(1, "Vasile", 917)
    repo.add(student)
    y = {1: student}
    assert repo.get_students() == y


if __name__ == "__main__":
    test_add()
