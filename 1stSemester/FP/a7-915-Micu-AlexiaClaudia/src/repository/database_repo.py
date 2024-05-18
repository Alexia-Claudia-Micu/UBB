from src.repository.memory_repo import *
from src.domain.student import Student
import pyodbc


class DatabaseRepo(MemoryRepo):
    # this class inherits from student_repo
    # => has all the methods and attributes in student_repo

    def __init__(self, file_name):
        # call superclass constructor
        super(DatabaseRepo, self).__init__()
        # remember the name of the file we're working with
        self._con = file_name
        # load the students from the file
        self._load_file()
        #self.generate_random(10)

    def _load_file(self):
        """
        Load the students from database
        """
        try:
            con_string = (r"Driver={Microsoft Access Driver (*.mdb, *.accdb)};"
                         r"DBQ=C:\Users\alexi\Documents\GitHub\a7-915-Micu-AlexiaClaudia\src\students.accdb;")
            conn = pyodbc.connect(con_string)
            self.conn = conn
        except pyodbc.Error as e:
            print("Error in connection", e)

        cur = self.conn.cursor()
        sql = "select * from students"
        cur.execute(sql)
        for row in cur.fetchall():
            new_student = Student(row[0], row[1], row[2])
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

    def add_sql(self, new_student: Student):
        cur = self.conn.cursor()
        #sql = "Insert into students values (19, 'Helmy', 916)"
        sql = f"Insert into students values ({new_student.student_id}, '{new_student.name}', {new_student.group})"
        cur.execute(sql)
        self.conn.commit()

    def add(self, new_student: Student):
        '''
        Adds the added student to the text file by overriding the memory(base) repository using inheritance
        '''
        super().add(new_student)
        self.add_sql(new_student)
    def delete_student(self, student_id):
        super().delete_student(student_id)
        cur = self.conn.cursor()
        cur.execute('DELETE FROM students WHERE ID = ?', (student_id))
        self.conn.commit()

    def change_data(self, data):
        super().change_data(data)
        cur = self.conn.cursor()
        cur.execute('DELETE * FROM students')
        self.conn.commit()
        for student in self.get_all():
            self.add_sql(student)

