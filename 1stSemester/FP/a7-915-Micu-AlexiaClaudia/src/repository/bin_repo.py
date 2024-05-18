from src.domain.student import Student
from src.repository.memory_repo import MemoryRepo
import pickle
from src.repository.student_repo import generate_students

class BinaryFileRepo(MemoryRepo):

    def __init__(self, file_name="students.bin"):
        super(BinaryFileRepo, self).__init__()
        self._file_name = file_name
        #self.generate_random(10)
        self._load_file()


    def _load_file(self):
        fin = open(self._file_name, "rb")
        obj = pickle.load(fin)
        for student in obj:
            super().add(student)
        fin.close()

    def add(self, student: Student):
        '''
        Adds the added student to the text binary by overriding the memory(base) repository using inheritance
        '''
        super().add(student)
        self._save_file()

    def _save_file(self):
        fout = open(self._file_name, "wb")
        pickle.dump(self.get_all(), fout)
        fout.close()

    def delete_student(self, id: int):
        super().delete_student(id)
        self._save_file()

    def change_data(self, data):
        super().change_data(data)
        self._save_file()

    def generate_random(self, n):
        for student in generate_students(n):
            self.add(student)