from src.domain.student import Student
from random import choice, randint
import pickle


# RepoException inherits from Python's builtin Exception class
# RepoException "IS AN" exception
class RepoException(Exception):
    pass


class student_repo(object):
    def __init__(self):
        # keys are student id's, values are student objects
        self._data = {}

    def add(self, new_student: Student):
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

    def __len__(self):
        return len(self._data)


class student_repo_bin_file(student_repo):
    def __init__(self, file_name="students.bin"):
        # call superclass constructor
        super(student_repo_bin_file, self).__init__()
        # remember the name of the file we're working with
        self._file_name = file_name
        # load the students from the file
        #self._load_file()

    def add(self, new_student: Student):
        # call the add() method on the super class
        # we want to do everything the superclass add() already does
        super().add(new_student)
        # we also want to save all students to a text file
        self._save_file()

    def _load_file(self):
        # r - read, b - binary
        fin = open(self._file_name, "rb")
        obj = pickle.load(fin)

        for c in obj:
            super().add(c)
        fin.close()

    def _save_file(self):
        # w - write mode (overwrite), b - binary mode
        fout = open(self._file_name, "wb")
        pickle.dump(self.get_all(), fout)
        # NOTE Don't forget to close the file!
        fout.close()


# just a plain old regular class :)
class student_repo_text_file(student_repo):
    # this class inherits from student_repo
    # => has all the methods and attributes in student_repo

    def __init__(self, file_name="students.txt"):
        # call superclass constructor
        super(student_repo_text_file, self).__init__()
        # remember the name of the file we're working with
        self._file_name = file_name
        # load the cars from the file
        self._load_file()

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
        # call the add() method on the super class
        # we want to do everything the superclass add() already does
        super().add(new_student)
        # we also want to save all students to a text file
        self._save_file()


#
# def test_car_repo():
#     repo = car_repo()
#     # car repository is empty
#     assert len(repo) == 0
#
#     # add cars to the repo
#     c1 = car("CJ 01 ABC", "Dacia", "Sandero", "red")
#     repo.add(c1)
#     c2 = car("CJ 01 XYZ", "Dacia", "Logdy", "white")
#     repo.add(c2)
#     assert len(repo) == 2
#
#     # try to add the same car again
#     try:
#         repo.add(c1)
#         assert False
#     except RepoException:
#         assert True
#
#     # retrieve cars from repo
#     assert repo.get("CJ 01 ABC") == c1
#
#     # TODO Try to implement repo["CJ 01 XYZ"] == c2
#     assert repo.get("CJ 01 XYZ") == c2
#
#     # try to retrieve a non-existing car
#     try:
#         repo.get("SJ 04 RTY")
#         assert False
#     except RepoException:
#         assert True


def generate_students(n: int):
    """
    Generates n student instances
    :return: A list of n students
    """
    id = 0
    names = {"First Name": ["Olivia", "Emma", "Charlotte", "Amelia", "Ava", "Sophia", "Jude", "Milo", "Malachi", "Charlie", "Ira", "Molly", "Paul", "Bailey", "Rebecca", "Sage", "Ezekiel", "Brianna", "Elora", "Simon", "Leon"], 'Last Name': ["Smith", "Johnson", "Williams", "Miller", "Davis", "Garcia", "Brown", "Evans", "Moore", "Taylor", "Walker", "Baker"]}
    groups = [215, 216, 811, 812, 911, 912, 915, 916, 917]

    result = []
    while n > 0:
        id += 1
        name = choice(names['First Name']) + " " + choice(names["Last Name"])
        group = choice(groups)
        result.append(Student(id, name, group))
        n -= 1
    return result

def generate_and_print_students_text_file(n):
    # saves the generated students to the file
    repo_text = student_repo_text_file()
    for student in generate_students(50):
        print(str(student))
        repo_text.add(student)
    for student in repo_text.get_all():
        print(str(student))
def generate_and_print_students_bin_file(n):
    # saves the generated students to the file
    repo = student_repo()
    repo_bin = student_repo_bin_file()
    for student in generate_students(50):
        #print(str(student))
        repo_bin.add(student)
    for student in repo_bin:
        #print(str(student))
        repo_bin.add(student)

if __name__ == "__main__":
    generate_and_print_students_text_file(10)
