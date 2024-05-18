from Ui import start_Ui
from random import randint
from Functions import insert_expense

def append_30_days ( list ):
    # appends the base of the dictionary: 30 days with no expenses
    for i in range(1,31):
        list[str(i)] = {}

def generate_random_list ( list, expenses ):
    '''
    - > for each day it randomly generates a nr in (0, 5) meaning the nr of initial expenses for that day
    - > randomly picks an expense (can pick duplicates)
    - > generates a sum in interval [1, 1000] and either adds it to the existing expense or creates a new key for its expense in the dictionary
    :param list: a dictionary with 30 days
    :param expenses: elem from list {'housekeeping', 'food', 'transport', 'clothing', 'internet', 'others'}
    :return: the dictionary with randomly generated expenses
    '''
    for day in range(1, 31):
        nr_expenses = randint(0, 5)
        for i in range(0, nr_expenses):
            expense = randint(0, 5)
            sum = randint(1, 1000)
            list[str(day)] = insert_expense(list[str(day)], sum, expenses[expense])

def create_list ():
    '''
    - > initializes an empty dictionary
    - > creates the base of the dictionary (days)
    - > randomly generates some values and expenses
    :return: a dictionary fit for evaluating the program
    '''
    expenses = ['housekeeping', 'food', 'transport', 'clothing', 'internet', 'others']
    list = {}
    append_30_days(list)
    generate_random_list(list, expenses)
    return list

start_Ui(create_list())
