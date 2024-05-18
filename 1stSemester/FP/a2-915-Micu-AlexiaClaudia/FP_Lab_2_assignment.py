from random import randint
from random import shuffle

# option 1

def generate_list ( n ):
    # generates a list with random numbers
    list = []
    for i in range(n):
        x = randint( 0,500 )
        list.append( x )
    return list

def command_1 ():
    '''
    Reads list lenght
    Generates list
    '''
    list = []
    n = read_integer("array lenght")
    list = generate_list( n)
    return list

# option 2

def is_sorted ( list ):
    # checks if the list is sorted
    for i in range( len(list)-1 ):
        if list[i] > list[i+1]:
            return 0
    return 1

def shuffle ( list ):
    # shuffles list
    for i in range ( len(list) ):
        aux = list[i]
        nrRand = randint( 0, len(list)-1 )
        list[i]=list[nrRand]
        list[nrRand]=aux

def permutation_sort ( list, step ):
    '''
    Sorts the list using permutation sort
    :param list: given array
    :param step: print list every n*step
    '''
    nr_step = 0

    while is_sorted( list ) == 0:

        if nr_step % step == 0: # printing every (step) steps
            print_list( list )

        shuffle( list )
        nr_step += 1

    print( "The list has been sorted." )

# option 3

def stooge_sort ( list, step, step_counter, left, right ):
    '''
    Sorts the list using stooge sort
    The algorithm sorts values at opposite positions of the list and
    reduces its size by 1/3 each time (until the size reaches 2)
    :param list:
    :param step: print list every n*step
    :param step_counter: current step
    :param left: left list boundry
    :param right: right list boundry
    '''

    #if left >= right :
    #    return

    if step_counter % step == 0:
        print_list(list)

    if list[left] > list[right] :
        aux = list[left]
        list[left] = list[right]
        list[right] = aux

    if right - left + 1 > 2:
        part = ( right - left + 1 )// 3

        stooge_sort( list, step, step_counter+1, left, right - part )
        stooge_sort( list, step, step_counter+1, left + part, right )
        stooge_sort( list, step, step_counter+1, left, right - part )


# option 4

def print_list ( list ):
    print( "Your list is: " )
    print(list)

def read_integer ( str ):
    '''
    Provides integer values
    :param str: text message of required value to be printed
    :return: integer value
    '''
    step = "0"
    ok = 0
    while ok == 0:
        ok = 1
        step = input("Give integer value for " + str + ": ")
        for i in range ( len(step)-1 ):
            if step[i] < "1" or step[i] > "9":
                ok = 0
    return int(step)

def solve ():
    '''
    Generates the menu
    Executes the inputed commands
    '''
    input_command = "-1"
    list = []

    while input_command != "0":
        print( "1 - Generate list of n natural numbers." )
        print( "2 - Sorting option 1 - Permutation sort." )
        print( "3 - Sorting option 2 - Stooge sort." )
        print( "4 - Show list." )
        print( "0 - Exit program." )
        print( "----------------------------------------" )

        input_command = input( "Input command: " )

        if input_command == "1":
            list = command_1()
        elif input_command == "2":
            if len(list) == 0:
                print("Must generate a list.")
            else:
                step = read_integer("steps")
                permutation_sort( list, step )
        elif input_command == "3":
            if len(list) == 0:
                print("Must generate a list.")
            else:
                step = read_integer("steps")
                stooge_sort(list,step,0,0,len(list)-1)
                print("The list has been sorted.")
        elif input_command == "4":
            if len(list) == 0:
                print("Must generate a list.")
            else:
                print_list( list )
        elif input_command == "0":
            print( "Exiting program." )
        else:
            print ( "The command that you inputed does not exist." )

solve()


