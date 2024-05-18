from Functions import split_command
from Functions import execute_command
from Functions import execute_command
from Functions import make_list_copy

def print_list ( list ):
    print(build_result_table(list).draw())

def start_Ui (list :list):
    history_of_list = []
    history_of_list.append(make_list_copy(list))
    while True:
        valid = False
        while not valid:
            try:
                command = input("Give command > ")
                if command == 'quit':
                    print('Exiting program.')
                    return
                [code, command] = split_command(command)

            except ValueError as ve:
                print("There was a " + str(type(ve)) + " " + str(ve))
            except TypeError as te:
                print("There was a " + str(type(te)) + " " + str(te))
            except IndexError as ie:
                print("There was a " + str(type(ie)) + " " + str(ie))
            else:
                print("command is valid")
                print("Executing command : " + code)
                list = execute_command(list, code, command, history_of_list)
                valid = True
            finally:
                print("loading...")
