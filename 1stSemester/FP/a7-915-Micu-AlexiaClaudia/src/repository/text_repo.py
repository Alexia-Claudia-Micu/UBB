from src.repository.memory_repo import *
from src.repository.student_repo import generate_students
from src.domain.student import Student


class TextFileRepo(MemoryRepo):
    # this class inherits from student_repo
    # => has all the methods and attributes in student_repo

    def __init__(self, file_name="students.txt"):
        # call superclass constructor
        super(TextFileRepo, self).__init__()
        # remember the name of the file we're working with
        self._file_name = file_name
        # load the students from the file
        self._load_file()
        #self.generate_random(10)

    def _load_file(self):
        """
        Load the students from a text file
        """
        # open a text file for reading
        # t - text file mode, r - reading
        lines = []

        try:
            fin = open(self._file_name, "rt")
            # each student should be on their own line
            lines = fin.readlines()
            # close the file when done reading
            fin.close()
        except IOError:
            # It's ok if we don't find the input file
            print("file not found")

        for line in lines:
            current_line = line.split(",")
            new_student = Student(int(current_line[0].strip()), current_line[1].strip(), int(current_line[2].strip()))
            # NOTE call super() so that we don't write the file we're reading from
            super().add(new_student)

    def _save_file(self):
        """
        Save all students to a text file
        """
        # open a text file for writing
        # t - text file mode, w - writing (rewrite the file every time)
        fout = open(self._file_name, "wt")

        # writes student_string into the text file
        # fout.write(student_string)
        for student in self.get_all():
            student_string = str(student.student_id) + "," + student.name + "," + str(student.group) + "\n"
            fout.write(student_string)

        # call close when done writing
        fout.close()

    def add(self, new_student: Student):
        '''
        Adds the added student to the text file by overriding the memory(base) repository using inheritance
        '''
        # call the add() method on the super class
        # we want to do everything the superclass add() already does
        super().add(new_student)
        # we also want to save all students to a text file
        self._save_file()

    def delete_student(self, id: int):
        super().delete_student(id)
        self._save_file()

    def change_data(self, data):
        super().change_data(data)
        self._save_file()

    def generate_random(self, n):
        for student in generate_students(n):
            self.add(student)
