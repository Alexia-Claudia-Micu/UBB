from src.domain.exceptions import StudentValidationException

class Student:
    """
    Each student must have:
        -> a valid id (unique integer),
        -> a name (string).
        -> a group (positive integer).
    """

    def __init__(self, student_id: int, student_name: str, student_group: int):
        self.__student_id = student_id
        self.__name = student_name
        self.__group = student_group
        self.validate()

    def validate(self):
        errors = []
        # V1 - All properties are non-empty
        if self.student_id < 0:
            errors.append('Invalid student id')
        if self.group < 0:
            errors.append('Invalid value for student group')
        if len(self.name) < 3:
            errors.append('Student name should have at least 3 letters')

        if len(errors) > 0:
            raise StudentValidationException(errors)



    @property
    def student_id(self):
        return self.__student_id

    # @student_id.setter
    # def student_id(self, new_value):
    #     self.__student_id = new_value

    @property
    def name(self):
        return  self.__name

    @name.setter
    def name(self, new_value):
        self.__name = new_value

    @property
    def group(self):
        return  self.__group

    @group.setter
    def group(self, new_value):
        self.__group = new_value

    def __str__(self):
        return f"Student {str(self.__student_id)}: Name: {self.__name}, Group: {str(self.__group)}"


def test_student():
    new_student = Student(1, "Vasile", 917)
    assert new_student.student_id == 1
    assert new_student.name == "Vasile"
    assert new_student.group == 917
    assert str(new_student) == "Student 1: Name: Vasile, Group: 917"

    # change group
    new_student.group = 215
    assert new_student.group == 215
    assert str(new_student) == "Student 1: Name: Vasile, Group: 215"

if __name__ == "__main__":
    test_student()