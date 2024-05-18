from src.domain.student import Student
import copy
class ServiceException(Exception):
    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message

class StudentService:
    def __init__(self, repo):
        # self._repo = StudentRepo()
        # NOTE Taking parameters in ctor allows you to change them
        self._repo = repo
        self.operations = 0
        self._archive = []
        self._archive.append(copy.deepcopy(self._repo.get_students()))


    def add(self, student: Student):
        """
        Add a new student
        + Saves it as a new iteration in the archive
        """
        # 2. Validate Student instance
        # 3. Add student to repo
        self._repo.add(student)
        self._archive.append(copy.deepcopy(self._repo.get_students()))
        self.operations += 1

    def return_all(self):
        return self._repo.get_all()

    def filter(self, group: int):
        '''
        Filter the students from a group - delete all students from that group
        '''
        for student in self._repo.get_all():
            if student.group == group:
                self._repo.delete_student(student.student_id)
        self.operations += 1
        self._archive.append(copy.deepcopy(self._repo.get_students()))

    def undo(self):
        if self.operations == 0:
            raise ServiceException("Nothing to undo!")

        self.operations -= 1
        self._repo.change_data(copy.deepcopy(self._archive[len(self._archive)-2]))
        _ = self._archive.pop()

from src.repository.memory_repo import MemoryRepo
def test_add():
    repo = MemoryRepo()
    service = StudentService(repo)
    student = Student(1, "Vasile", 917)
    service.add(student)
    y = {1: student}
    x = repo.get_students()
    assert repo.get_students() == y

if __name__ == "__main__":
    test_add()