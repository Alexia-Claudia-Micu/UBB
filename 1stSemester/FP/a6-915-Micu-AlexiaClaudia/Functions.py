from texttable.texttable import Texttable
import datetime
#------------------------------

def check_element( x, condition, condition_value):
    '''
    Verifies whether x [ < | = | > ] condition_value
    :param x: positive int
    :param condition: char in {<,=,>}
    :param condition_value: positive int
    :return: a boolean to indicate whether the condition has been fulfilled
    '''
    if condition == '<' and x < condition_value:
        return True
    if condition == '>' and x > condition_value:
        return True
    if condition == '=' and x == condition_value:
        return True
    return False

#-----------------------------------------

def try_int(x):
    # tries to convert the parameter to an integer
    # if it fails, it returns the string as is
    for i in x:
        if i < '0' or i > '9':
            return  x
    return int(x)

#---------------------------------------- checks
# check whether a parameter can be evaluated as a day, sum or category

def is_day(day):
    day = try_int(day)
    if day not in range(1, 31):
        return False
    return True

def is_sum(sum):
    sum = try_int(sum)
    if sum not in range(0, 1001):
        return False
    return True

def is_expense(category):
    expenses = ['housekeeping', 'food', 'transport', 'clothing', 'internet', 'others']
    if category not in expenses:
        return False
    return True

#------------------------------------ validators
# throw errors if the individual parts of the command are not correct

def validate_day(day):
    if not is_day(day):
        raise ValueError("Incorrect parameter for <day>")

def validate_sum( sum ):
    if not is_sum(sum):
        raise ValueError("Incorrect parameter for <sum>")

def validate_expense(category):
    if not is_expense(category):
        raise ValueError("Incorrect parameter for <expenses>")

def validate_command_lenght(lenght, correct):
    if lenght != correct:
        raise IndexError("Not enough or too many parameters")

def validate_day_or_category(par):
    if is_day(par):
        return "day"
    elif is_expense(par):
        return "expense"
    else:
        raise ValueError("Incorrect parameter for <expenses> or <day>")

def validate_connector(con):
    if con != "to":
        raise ValueError("Incorrect parameter for <connector>")

def validate_comparison_symbol (symbol):
    symbols = ['<', '>', '=']
    if not symbol in symbols:
        raise ValueError("Incorrect parameter for <comparison symbol>")

#------------------------------ tests
# use validators to check the validity of the command as a whole

def test_add_command (x):
    '''
    add <sum> <category>
    '''
    validate_command_lenght(len(x), 3)
    validate_sum(x[1])
    validate_expense(x[2])
    return 'add'

def test_insert_command (x):
    '''
    insert <day> <sum> <category>
    '''
    validate_command_lenght(len(x), 4)
    validate_day(x[1])
    validate_sum(x[2])
    validate_expense(x[3])
    return 'insert'

def test_remove_command (x):
    '''
    remove <day>
    remove <start day> to <end day>
    remove <category>
    '''
    if validate_day_or_category(x[1]) == "day":
        if len(x) == 2:
            return 'remove.1'
        else:
            validate_command_lenght(len(x), 4)
            validate_connector(x[2])
            validate_day(x[3])
            if int(x[1]) >= int(x[3]):
                raise ValueError("Incorrect interval for days")
            return 'remove.2'
    else:
        validate_command_lenght(len(x), 2)
        return 'remove.3'

def test_list_command (x):
    '''
    list
    list <category>
    list <category> [ < | = | > ] <value>
    '''
    if len(x) == 1:
        return 'list.1'
    else:
        validate_expense(x[1])
        if len(x) == 2:
            return 'list.2'
        else:
            validate_comparison_symbol(x[2])
            validate_sum(x[3])
            return 'list.3'

def test_filter_command (x):
    '''
    filter <category>
    filter <category> [ < | = | > ] <value>
    '''
    validate_expense(x[1])
    if len(x) == 2:
        return 'filter.1'
    else:
        validate_comparison_symbol(x[2])
        validate_sum(x[3])
        return 'filter.2'

def test_undo_command (x):
    if len(x) != 1:
        raise IndexError('Too many parameters for command')
    return 'undo'

def split_command(command_string):
    '''
    - > Receives the entire command as a string
    - > Splits it
    - > checks based on the initial keyword (if it is valid) {'add', 'insert', 'remove', 'list', 'filter', 'undo'}
    - > decides a command code: {add, insert, remove.1-3, list.1-3, filter.1-2, undo}
    :param command_string: full command (string)
    :return: returns a pair :[command code, list of the components of the command]
    '''
    possible_commands = ['add', 'insert', 'remove', 'list', 'filter', 'undo']
    x = command_string.split(" ")
    command = possible_commands.index(x[0]) # raises an error if the command keyword is not valid
    command = x[0]

    if command == 'add':
        return [test_add_command(x), x]
    elif command == 'insert':
        return [test_insert_command(x), x]
    elif command == 'remove':
        return [test_remove_command(x), x]
    elif command == 'list':
        return [test_list_command(x), x]
    elif command == 'filter':
        return [test_filter_command(x), x]
    elif command == 'undo':
        return [test_undo_command(x), x]

#----------------------------------- getters
def get_current_day(): # returns current day
    day = datetime.datetime.now().day
    return int(day)

def get_element(day, category):
    '''
    Returns the value for expense for the given day
    :param day: int [1, 30]
    :param category: an expense
    :return: the sum of the expense for the day if there exists an expense, otherwise none
    '''
    for i in day:
        if i == category:
            return day[category]
    return None

#----------------------------------- setter

def insert_expense(day:list, sum: int, expense: str):
    '''
    If the given day does not have any expense for the given expense
    then it creates a new type of expense.
    otherwise, it adds a new type of expense into the dictionary
    :param day: a dictionary from the list of dictionaries representing the expenses for a day
    :param sum: integer in range [1-1000] :the sum to be added
    :param expense: string from {'housekeeping','food','transport','clothing','internet','others'} :the type of expense
    :return: a dictionary like: {'expense': sum}
    '''
    x = day.setdefault(expense, 0)
    day[expense] = x + sum
    return day

#----------------------------------- executing the command

def add (list, sum, category): # add <sum> <category>
    day = str(get_current_day())
    insert_expense(list[day], sum, category)

def insert (list, day, sum, category): # insert <day> <sum> <category>
    insert_expense(list[day], sum, category)

def remove_1 ( list, day ): # remove <day>
    list[day].clear()

def remove_2 ( list, start_day, end_day ): # remove <day> to <day>
    for day in range(start_day, end_day+1):
        remove_1(list, str(day))

def remove_3 ( list, category ): # remove <category>
    for i in range(1, 31):
        if get_element(list[str(i)],category) != None:
            list[str(i)].pop(category)

def filter_1 ( list, category ): # filter <category>
    expenses = ['housekeeping', 'food', 'transport', 'clothing', 'internet', 'others']
    for expense in expenses:
        if expense != category:
            remove_3(list, expense)

def filter_2 ( list, category, condition, condition_value ): # filter <category> [ < | = | > ] <value>
    for day in range(1, 31):
        if get_element(list[str(day)], category) != None:
            if check_element(list[str(day)][category], condition, condition_value) == False:
                list[str(day)].pop(category)

def execute_command(list, code, command, history_of_list):
    '''
    Executes the command by:
    - > choosing a procedure determined by the code
    - > send the corresponding parameters from the command list
    - > updates the history of the list by either adding a new change or reverting a step
    :param list:  dictionary of dictionaries like [ day 1 -> 30: { expense: value }]
    :param code:  {add, insert, remove.1-3, list.1-3, filter.1-2, undo}
    :param command: a list containing the separated elements of the command
    :param history_of_list: a stack that retain all the stages that resulted in modifying the list and updates it regularly
    :return: the list as a result of the operation
    '''
    # functionality a: add + insert
    if code == 'add':
        add(list, int(command[1]), command[2])
        history_of_list.append(make_list_copy(list))
    elif code == 'insert':
        insert(list, command[1], int(command[2]), command[3])
        history_of_list.append(make_list_copy(list))
    # functionality b: 3 types of removing
    elif code == 'remove.1':
        remove_1(list, command[1])
        history_of_list.append(make_list_copy(list))
    elif code == 'remove.2':
        remove_2(list, int(command[1]), int(command[3]))
        history_of_list.append(make_list_copy(list))
    elif code == 'remove.3':
        remove_3(list, command[1])
        history_of_list.append(make_list_copy(list))
    # functionality c: 3 types of listing
    elif code == 'list.1':
        print(list_1(list).draw())
    elif code == 'list.2':
        print(list_2(list, command[1]).draw())
    elif code == 'list.3':
        print(list_3(list, command[1], command[2], int(command[3])).draw())
    # functionality d: 2 types of filtering
    elif code == 'filter.1':
        filter_1(list, command[1])
        history_of_list.append(make_list_copy(list))
    elif code == 'filter.2':
        filter_2(list, command[1], command[2], int(command[3]))
        history_of_list.append(make_list_copy(list))
    else:
        # functionality e: undo
        if(len(history_of_list) == 1):
            print("Cannot undo anymore.")
        else:
            history_of_list.pop()
            list = history_of_list[len(history_of_list)-1]
    return list

#----------------------------- table creating functions

def make_list_copy (list): # returns a copy of the list
    x = {}
    for i in range(1, 31):
        x[str(i)] = list[str(i)].copy()
    return x

def list_1(list): # list
    '''
    Creates a table organised by expenses with the 30 days as rows.
    If there are no expenses for a day, it will print '-'
    :param list: dictionary of dictionaries like [ day 1 -> 30: { expense: value }]
    :return: a table
    '''
    table = Texttable()
    expenses = ['housekeeping', 'food', 'transport', 'clothing', 'internet', 'others']
    table.add_row(['Day', 'Housekeeping', 'Food', 'Transport', 'Internet', 'Clothing', 'Others'])
    for day in range(1, 31):
        row = []
        row.append(day)
        for category in expenses:
            elem = get_element(list[str(day)], category)
            if elem != None:
                row.append(elem)
            else:
                row.append("-")
        table.add_row(row)
    return table

def list_2(list, category): # list <category>
    '''
    Creates a table only with the expenses for the given category.
    If there are no expenses for a day, it will print '-'
    :param list: dictionary of dictionaries like [ day 1 -> 30: { expense: value }]
    :param category: an expense
    :return: a table enumerating the days and their expenses split into intervals of 10 days
    '''
    table = Texttable()
    for k in range(1, 4):
        days = ['Days']
        row = [category]
        for day in range((k-1)*10+1, k * 10 + 1):
            x = 'Day ' + str(day)
            days.append(x)
            if get_element(list[str(day)], category) != None:
                row.append(get_element(list[str(day)], category))
            else:
                row.append("-")
        table.add_row(days)
        table.add_row(row)
    return table

def list_3(list, category, condition, condition_value): # list <category> [ < | = | > ] <value>
    '''
    Creates a table by adding day -> value with respect to the condition
    :param list: dictionary of dictionaries like [ day 1 -> 30: { expense: value }]
    :param category: an expense
    :param condition: [ < | = | > ]
    :param condition_value: positive integer
    :return: a table with the days that contain expenses that verify the condition
    '''
    table = Texttable()
    days = ['Days']
    row = [category]
    for day in range(1, 31):
        x = 'Day ' + str(day)
        elem = get_element(list[str(day)], category)
        if elem != None:
            if check_element(elem, condition, condition_value):
                row.append(elem)
                days.append(x)
    table.add_row(days)
    table.add_row(row)
    return table

# ------------------------------------- tests
# add + insert
'''
related to add
-> test_add_command(x)
-> add(list,sum,expense)
related to insert
-> test_insert_command(x)
-> insert(list,day,sum,expense)
'''
def assert_add_formula_check (): # add <sum> <expense>
    assert(test_add_command(['add', '10', 'food']) == 'add'), "add-correct command evaluated as false - common command"
    assert(test_add_command(['add', '1', 'food']) == 'add'), "add-correct command evaluated as false - low range for sum"
    assert(test_add_command(['add', '30', 'food']) == 'add'), "add-correct command evaluated as false - hight range for sum"
    assert(test_add_command(['add', '30', 'housekeeping']) == 'add'), "add-correct command evaluated as false - category"
    assert(test_add_command(['add', '30', 'internet']) == 'add'), "add-correct command evaluated as false - category"
    assert(test_add_command(['add', '30', 'clothing']) == 'add'), "add-correct command evaluated as false - category"
    assert(test_add_command(['add', '30', 'others']) == 'add'), "add-correct command evaluated as false - category"
    assert(test_add_command(['add', '30', 'transport']) == 'add'), "add-correct command evaluated as false - category"

def assert_insert_formula_check (): # add <sum> <expense>
    assert(test_insert_command(['insert', '10', '700', 'food']) == 'insert'), "insert-correct command evaluated as false - common command"
    assert(test_insert_command(['insert', '1', '1', 'food']) == 'insert'), "insert-correct command evaluated as false - low range"
    assert(test_insert_command(['insert', '30', '1000', 'food']) == 'insert'), "insert-correct command evaluated as false - hight range"
    assert(test_insert_command(['insert', '30', '1000', 'housekeeping']) == 'insert'), "insert-correct command evaluated as false - category"
    assert(test_insert_command(['insert', '30', '1000', 'internet']) == 'insert'), "insert-correct command evaluated as false - category"
    assert(test_insert_command(['insert', '30', '1000', 'clothing']) == 'insert'), "insert-correct command evaluated as false - category"
    assert(test_insert_command(['insert', '30', '1000', 'others']) == 'insert'), "insert-correct command evaluated as false - category"
    assert(test_insert_command(['insert', '30', '1000', 'transport']) == 'insert'), "insert-correct command evaluated as false - category"

def assert_add ():
    list = {str(get_current_day()): {'transport': 20}}
    it1 = {str(get_current_day()): {'transport': 40}}
    it2 = {str(get_current_day()): {'transport': 40, 'others': 200}}
    add(list, 20, 'transport')
    assert(list == it1), 'add to an existing expense'
    add(list, 200, 'others')
    assert(list == it2), 'add a new expense'

def assert_insert ():
    list = {'10': {'clothing': 20}, '2': {'food': 20}}
    it1 = {'10': {'clothing': 20}, '2': {'food': 20, 'internet': 450}}
    it2 = {'10': {'clothing': 220}, '2': {'food': 20, 'internet': 450}}
    insert(list, '2', 450, 'internet')
    assert(list == it1), 'insert to an existing expense'
    insert(list, '10', 200, 'clothing')
    assert(list == it2), 'insert a new expense'

def test_add_insert ():
    try:
        assert_add_formula_check()
        assert_add()
        assert_insert_formula_check()
        assert_insert()
    except AssertionError as ae:
        print("There was a " + str(type(ae)) + " " + str(ae))
    else:
        print("add and insert commands are valid")
    finally:
        print("loading...")

# remove
'''
-> test_remove_command(x)
related to remove.1
-> remove_1(list,day)
related to remove.2
-> remove_2(list,start_day,end_day)
related to remove.3
-> remove_3(list,category)
'''

def assert_remove_formula_check():
    assert(test_remove_command(['remove', '1']) == 'remove.1'), 'remove.1 - low day'
    assert(test_remove_command(['remove', '30']) == 'remove.1'), 'remove.1 - high day'
    assert(test_remove_command(['remove', '1', 'to', '30']) == 'remove.2'), 'remove.2'
    assert(test_remove_command(['remove', 'food']) == 'remove.3'), 'remove.3 - category'
    assert(test_remove_command(['remove', 'others']) == 'remove.3'), 'remove.3 - category'

def assert_remove():
    list = {'1': {'clothing': 20, 'food': 90, 'transport': 260, 'internet': 30}, '5': {'food': 20}, '15': {'food': 20}, '20': {'food': 20, 'others': 220}, '25': {'food': 20}, '26': {'food': 20}, '27': {'food': 20}, '30': {'food': 20}, '2':{}, '3':{}, '4':{}, '8':{}, '6':{}, '7':{}, '9':{}, '10':{}, '11':{}, '12':{}, '13':{}, '14':{}, '16':{}, '17':{}, '18':{}, '19':{}, '21':{}, '22':{}, '23':{}, '24':{}, '28':{}, '29':{}}
    it1 = {'1': {}, '5': {'food': 20}, '15': {'food': 20}, '20': {'food': 20, 'others': 220}, '25': {'food': 20}, '26': {'food': 20}, '27': {'food': 20}, '30': {'food': 20}, '2':{}, '3':{}, '4':{}, '8':{}, '6':{}, '7':{}, '9':{}, '10':{}, '11':{}, '12':{}, '13':{}, '14':{}, '16':{}, '17':{}, '18':{}, '19':{}, '21':{}, '22':{}, '23':{}, '24':{}, '28':{}, '29':{}}
    it2 = {'1': {}, '5': {'food': 20}, '15': {'food': 20}, '20': {'food': 20, 'others': 220}, '25': {}, '26': {}, '27': {}, '30': {'food': 20}, '2':{}, '3':{}, '4':{}, '8':{}, '6':{}, '7':{}, '9':{}, '10':{}, '11':{}, '12':{}, '13':{}, '14':{}, '16':{}, '17':{}, '18':{}, '19':{}, '21':{}, '22':{}, '23':{}, '24':{}, '28':{}, '29':{}}
    it3 = {'1': {}, '5': {}, '15': {}, '20': {'others': 220}, '25': {}, '26': {}, '27': {}, '30': {}, '2':{}, '3':{}, '4':{}, '8':{}, '6':{}, '7':{}, '9':{}, '10':{}, '11':{}, '12':{}, '13':{}, '14':{}, '16':{}, '17':{}, '18':{}, '19':{}, '21':{}, '22':{}, '23':{}, '24':{}, '28':{}, '29':{}}
    remove_1(list, '1')
    assert(list == it1), 'remove.1 - remove day'
    remove_2(list, 25, 27)
    assert(list == it2), 'remove.2 - remove day interval'
    remove_3(list, 'food')
    assert(list == it3), 'remove.3 - remove category'

def test_remove():
    try:
        assert_remove_formula_check()
        assert_remove()
    except AssertionError as ae:
        print("There was a " + str(type(ae)) + " " + str(ae))
    else:
        print("remove command is valid")
    finally:
        print("loading...")

# test auxiliary
def assert_auxiliary_split_command():
    assert(split_command('add 10 food') == ['add', ['add', '10', 'food']]), "split command - add"
    assert(split_command('insert 14 10 transport') == ['insert', ['insert', '14', '10', 'transport']]), "split command - insert"
    assert(split_command('remove 30') == ['remove.1', ['remove', '30']]), "split command - remove.1"
    assert(split_command('remove 14 to 18') == ['remove.2', ['remove', '14', 'to', '18']]), "split command - remove.2"
    assert(split_command('remove clothing') == ['remove.3', ['remove', 'clothing']]), "split command - remove.3"

def assert_auxiliary_insert_expense():
    day = {'others': 10}
    it1 = {'others': 10, 'food': 999}
    it2 = {'others': 10, 'food': 1000}
    insert_expense(day, 999, 'food')
    assert(day == it1), 'insert new expense'
    insert_expense(day, 1, 'food'), 'insert to existing expense'

# auxiliary
'''
-> split_command(command)
-> insert_expense(day,sum,expense)
'''

def test_auxiliary():
    try:
        assert_auxiliary_split_command()
        assert_auxiliary_insert_expense()
    except AssertionError as ae:
        print("There was a " + str(type(ae)) + " " + str(ae))
    else:
        print("auxiliary procedures are valid")
    finally:
        print("loading...")

#test_add_insert()
#test_remove()
#test_auxiliary()