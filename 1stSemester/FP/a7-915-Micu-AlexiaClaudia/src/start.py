from src.repository.memory_repo import MemoryRepo
from src.repository.bin_repo import BinaryFileRepo
from src.repository.text_repo import TextFileRepo
from src.repository.database_repo import DatabaseRepo
from src.services.student_services import StudentService
from src.ui.ui import UserInterface


if __name__ == "__main__":
    print("915 - Micu Alexia-Claudia")
    print("-------------------------")
    print("1. Text file repository")
    print("2. Binary file repository")
    print("3. Memory repository")
    print("4. Database repository")
    command = input("Repositoy implementation > ")

    if command not in ["text", "memory", "binary", "database"]:
        raise ValueError("Invalid implementation method")

    elif command == "text":
        repository = TextFileRepo("students.txt")
    elif command == "binary":
        repository = BinaryFileRepo("students.bin")
    elif command == "memory":
        repository = MemoryRepo()
        repository.add_rand_students(10)
    elif command == "database":
        repository = DatabaseRepo(r"Driver={Microsoft Access Driver (*.mdb, *.accdb)};"
                         r"DBQ=C:\Users\alexi\Documents\GitHub\a7-915-Micu-AlexiaClaudia\src\students.accdb;")
    services = StudentService(repository)
    UI = UserInterface(services)

    UI.menu()
