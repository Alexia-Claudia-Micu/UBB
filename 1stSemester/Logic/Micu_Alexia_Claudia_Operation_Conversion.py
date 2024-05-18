# 915 Micu Alexia-Claudia

def convert_digit_to_base_10(digit: str):
    '''
    Converts a digit in bases [2,16] into base 10
    :param digit: a character in range [0,9] u [A,F]
    :return: integer correspondent of the digit: [0, 15]
    '''
    digits = {"0": 0, "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9, "A": 10, "B": 11, "C": 12, "D": 13, "E": 14, "F": 15}
    return digits[digit]

def convert_digit_from_base_10(digit: int):
    '''
    Converts a digit in bases 10 into base [2,16]
    :param digit: integer in range [0,15]
    :return: string correspondent of the digit: [0,9] u [A,F]
    '''
    digit = str(digit)
    digits = {"0": "0", "1": "1", "2": "2", "3": "3", "4": "4", "5": "5", "6": "6", "7": "7", "8": "8", "9": "9", "10": "A", "11": "B", "12": "C", "13": "D", "14": "E", "15": "F"}
    return digits[digit]

def addition(nr_1: str, nr_2: str, base: int):
    '''
    Adds two numbers having the same base.
    :param nr_1: a string containing characters in [0,9] u [A,F] representing the first term of the addition
    :param nr_2: a string containing characters in [0,9] u [A,F] representing the second term of the addition
    :param base: integer in range [2, 16] representing the base in which the addition will be performed
    :return: A string representing the result
    '''
    carry = 0 # initialises the carry variable with 0 since there is no carry for the rightmost digits
    result = "" # the result is currently null

    len_1 = len(nr_1) - 1 # retains the lenght of the two numbers (we use the lenght to iterate from right to left since)
    len_2 = len(nr_2) - 1

    while len_1 >= 0 or len_2 >= 0 or carry != 0:
        # isolate one digit at a time from each number starting from the right
        if len_1 >= 0: # this condition is used in care one nr is longer than the other and we need to add 0 + digit
            digit_1 = convert_digit_to_base_10(nr_1[len_1])
            len_1 -= 1 # decrease the lenght for next iteration (we use the lenght to iterate from right to left since)
        else:
            digit_1 = 0
        if len_2 >= 0:
            digit_2 = convert_digit_to_base_10(nr_2[len_2])
            len_2 -= 1
        else:
            digit_2 = 0

        # first calculate the sum of the digits in base 10
        digit = digit_1 + digit_2 + carry
        # calculate carry for the next iteration
        carry = digit // base
        # convert the digit into required base
        digit = convert_digit_from_base_10(digit % base)

        # add the digit to the start position of the result
        aux = digit + result
        result = aux

    return result

def subtraction(nr_1, nr_2, base):
    '''
    Subtracts two numbers having the same base.
    :param nr_1: a string containing characters in [0,9] u [A,F] representing the first term of the subtraction
    :param nr_2: a string containing characters in [0,9] u [A,F] representing the second term of the subtraction
    :param base: integer in range [2, 16] representing the base in which the subtraction will be performed
    :return: A string representing the result
    '''
    carry = 0  # initialises the carry variable with 0 since there is no carry for the rightmost digits
    result = "" # the result is currently null

    len_1 = len(nr_1) - 1 # retains the lenght of the two numbers (we use the lenght to iterate from right to left since)
    len_2 = len(nr_2) - 1

    while len_1 >= 0 or len_2 >= 0 or carry != 0:
        # isolate one digit at a time from each number starting from the right
        if len_1 >= 0: # this condition is used in care one nr is longer than the other and we need to subtract 0 - digit or digit - 0
            digit_1 = convert_digit_to_base_10(nr_1[len_1])
            len_1 -= 1 # decrease the lenght for next iteration (we use the lenght to iterate from right to left since)
        else:
            digit_1 = 0
        if len_2 >= 0:
            digit_2 = convert_digit_to_base_10(nr_2[len_2])
            len_2 -= 1
        else:
            digit_2 = 0

        # first calculate the difference of the digits in base 10
        digit = digit_1 - digit_2 + carry
        # calculate carry for the next iteration
        if digit < 0: # handles the case of d1 - d2 when d1 > d2
            digit = base + digit
            carry = -1
        else:
            carry = 0 # resets the carry
        # convert the digit into required base
        digit = convert_digit_from_base_10(digit)

        # add the digit to the start position of the result
        aux = digit + result
        result = aux

    return result

def multiplication(nr_1: str, nr_2: str, base: int):
    '''
    Multiplies a number by one digit in a given base.
    :param nr_1: a string containing characters in [0,9] u [A,F] representing the first factor of the multiplication
    :param nr_2:  a string containing characters in [0,9] u [A,F] representing the second factor of the multiplication
    :param base:  integer in range [2, 16] representing the base in which the multiplication will be performed
    :return: A string representing the result
    '''
    carry = 0 # initialises the carry variable with 0 since there is no carry for the rightmost digits
    result = "" # the result is currently null

    len_1 = len(nr_1) - 1 # retains the lenght of the number (we use the lenght to iterate from right to left since)
    # we know that nr_2 is a digit, so we can convert it into decimal
    nr_2 = convert_digit_to_base_10(nr_2)

    while len_1 >= 0 or carry != 0:
        # isolate one digit at a time from the first factor
        if len_1 >= 0:
            digit_1 = convert_digit_to_base_10(nr_1[len_1])
            len_1 -= 1 # decrease the lenght for next iteration
        else:
            digit_1 = 0

        # first calculate the product of the digits in base 10
        digit = digit_1 * nr_2 + carry
        # calculate carry for the next iteration
        carry = digit // base
        # convert the digit into required base
        digit = convert_digit_from_base_10(digit % base)

        # add the digit to the start position of the result
        aux = digit + result
        result = aux

    return result

def division(divident: str, divisor: str, base: int):
    '''
    Divides a number by one digit in a given base.
    :param nr_1: a string containing characters in [0,9] u [A,F] representing the divident
    :param nr_2:  a string containing characters in [0,9] u [A,F] representing the divisor
    :param base:  integer in range [2, 16] representing the base in which the division will be performed
    :return: A pair of strings representing the quotient and remainder
    '''
    divisor = convert_digit_to_base_10(divisor) # we know that nr_2 is a digit, so we can convert it into decimal
    remainder = '0' # the remainder is currently 0
    quotient = "" # the quotient is currently null

    for current_digit in divident: # since there is no carry, we can iterate through the digits from left to right
        remainder_b10 = convert_digit_to_base_10(remainder) * base # calculates the remainder obtained in the previous iteration and converts it into decimal
        current_digit_b10 = convert_digit_to_base_10(current_digit) # converts the current digit into decimal

        quotient_int = (remainder_b10 + current_digit_b10) // divisor # calculates the quotient and remained in base 10
        remainder_b10 = (remainder_b10 + current_digit_b10) % divisor
        remainder = convert_digit_from_base_10(remainder_b10) # converts the remainder into the given base

        if quotient_int != 0: # converts the quotient into the given base
            quotient += convert_digit_from_base_10(quotient_int)

    if quotient == "":
        quotient = "0"
    return [quotient, remainder]

def substitution_conversion(nr: str, source_base: int, destination_base: int):
    '''
    Converts a number from source base b into destination base h with b < h
    :param nr:  the number that needs to be converted
    :param source_base:  integer in [2, 16]
    :param destination_base: integer in [2, 16]
    :return: A string representing the result
    '''
    nr_b10 = "0"
    base_power = 1
    digit = len(nr) - 1
    while digit > -1:
        digit_b10 = nr[digit] # takes the digit in base 10
        element = multiplication(str(base_power), digit_b10, destination_base) # multiplies the digit by the base(raised to the power of its rank in the number)
        nr_b10 = addition(nr_b10, element, destination_base)
        base_power = multiplication(str(base_power), str(source_base), destination_base) # increased the rank to which the base is raised to a power
        digit -= 1
    return nr_b10

def successive_division_conversion(nr: str, source_base: int, destination_base: int):
    '''
    Converts a number from source base b into destination base h with b > h
    :param nr: the number that needs to be converted
    :param source_base: integer in [2, 16]
    :param destination_base: integer in [2, 16]
    :return:  A string representing the result
    '''
    result = ""  # the result is currently null

    while nr != '0':
        [quotient, remainder] = division(nr, str(destination_base), int(source_base)) # divide the number by the destination base (the division is done in the source base)
        nr = quotient # the number becomes the quotient

        aux = remainder + result # the remainder is added to the result
        result = aux

    return result

def rapid_conversion(nr: str, source_base: int, destination_base: int):
    '''
    Converts a number from source base b into destination base h with b and h multiples of 2
    :param nr: the number that needs to be converted
    :param source_base: integer from {2,4,8,16}
    :param destination_base: integer from {2,4,8,16}
    :return:  A string representing the result
    '''
    if source_base < destination_base: # decides how many digits it needs to take from the number and into how many digits it needs to transform them
        nr_taken_digits = 1
        nr_transform_digits = 1
        x = source_base
        while x < destination_base:
            x *= source_base
            nr_taken_digits += 1
    else:
        nr_taken_digits = 1
        nr_transform_digits = 1
        x = destination_base
        while x < source_base:
            x *= destination_base
            nr_transform_digits += 1

    result = ""  # the result is currently null
    nr_len = len(nr) # retains the lenght of the number
    while nr_len > 0:
        digits_to_convert = nr[max(0, nr_len - nr_taken_digits): nr_len] # the max is added to simulate the added 0-s to the left
        nr_len -= nr_taken_digits
        digits_to_add = intermediate_base_conversion(digits_to_convert, source_base, destination_base)
        x = "0000"
        needed_addtionary_0s = x[len(x) - nr_transform_digits:len(x)-len(digits_to_add)] # takes the difference between the max(4) and how many digits there should be; how many digits there are
        z = needed_addtionary_0s + digits_to_add
        result = z + result
    return result

def intermediate_base_conversion(nr: str, source_base: int, destination_base: int):
    '''
    Converts a number from source base b into destination base h using the intermediate base 10
    :param nr: the number that needs to be converted
    :param source_base: integer in [2, 16]
    :param destination_base: integer in [2, 16]
    :return:  A string representing the result
    '''
    # source_base -> base 10
    nr_b10 = 0
    base_power = 1
    digit = len(nr) - 1
    while digit > -1:
        digit_b10 = convert_digit_to_base_10(nr[digit])
        nr_b10 += digit_b10 * base_power
        base_power *= source_base
        digit -= 1

    # base 10 -> destination_base
    result = ""
    while nr_b10 != 0:
        digit = nr_b10 % destination_base
        digit_destination_base = convert_digit_from_base_10(digit)
        aux = digit_destination_base + result
        result = aux
        nr_b10 //= destination_base

    return result

def conversion_menu():

    command = ""
    while command != '0':
        print("You need to pick a conversion method: ")
        print("1. Substitution conversion b < h ")
        print("2. Successive division conversion b > h  ")
        print("3. Rapid conversions ")
        print("4. Intermediate base conversion ")
        print("0. Quit ")
        print("---------------------------------")
        command = input("Give command > ")
        print("---------------------------------")

        if command == '1':
            print("You need to input a number, the source base and the destination base: ")
            nr_1 = input("Number > ")
            source_base = int(input("Source base > "))
            destination_base = int(input("Destination base > "))
            result = substitution_conversion(nr_1, source_base, destination_base)
            print(f"{str(nr_1)}({str(source_base)}) = {str(result)}({str(destination_base)})")
        elif command == '2':
            print("You need to input a number, the source base and the destination base: ")
            nr_1 = input("Number > ")
            source_base = int(input("Source base > "))
            destination_base = int(input("Destination base > "))
            result = successive_division_conversion(nr_1, source_base, destination_base)
            print(f"{str(nr_1)}({str(source_base)}) = {str(result)}({str(destination_base)})")
        elif command == '3':
            print("You need to input a number, the source base and the destination base: ")
            nr_1 = input("Number > ")
            source_base = int(input("Source base > "))
            destination_base = int(input("Destination base > "))
            result = rapid_conversion(nr_1, source_base, destination_base)
            print(f"{str(nr_1)}({str(source_base)}) = {str(result)}({str(destination_base)})")
        elif command == '4':
            print("You need to input a number, the source base and the destination base: ")
            nr_1 = input("Number > ")
            source_base = int(input("Source base > "))
            destination_base = int(input("Destination base > "))
            result = intermediate_base_conversion(nr_1, source_base, destination_base)
            print(f"{str(nr_1)}({str(source_base)}) = {str(result)}({str(destination_base)})")

def menu():
    command = ""
    while command != '0':
        print("1. Addition.")
        print("2. Subtraction.")
        print("3. Multiplication by one digit.")
        print("4. Division by one digit.")
        print("5. Conversion.")
        print("0. Quit.")
        print("---------------------------------")

        command = input("Give command > ")

        print("---------------------------------")

        if command == "1":
            print("You need to input two numbers and their base: ")
            nr_1 = input("Number 1 > ")
            nr_2 = input("Number 2 > ")
            base = int(input("Base > "))
            result = addition(nr_1, nr_2, base)
            print(f"{str(nr_1)}({str(base)}) + {str(nr_1)}({str(base)}) = {str(result)}({str(base)})")
        elif command == "2":
            print("You need to input two numbers and their base: ")
            nr_1 = input("Number 1 > ")
            nr_2 = input("Number 2 > ")
            base = int(input("Base > "))
            result = subtraction(nr_1, nr_2, base)
            print(f"{str(nr_1)}({str(base)}) - {str(nr_1)}({str(base)}) = {str(result)}({str(base)})")
        elif command == "3":
            print("You need to input a number, a digit and their base: ")
            nr_1 = input("Number > ")
            nr_2 = input("Digit > ")
            base = int(input("Base > "))
            result = multiplication(nr_1, nr_2, base)
            print(f"{str(nr_1)}({str(base)}) * {str(nr_2)}({str(base)}) = {str(result)}({str(base)})")
        elif command == "4":
            print("You need to input a number, a digit and their base: ")
            nr_1 = input("Number > ")
            nr_2 = input("Digit > ")
            base = int(input("Base > "))
            result = division(nr_1, nr_2, base)
            print(f"{str(nr_1)}({str(base)}) / {str(nr_2)}({str(base)}) = {str(result[0])}({str(base)}), r: {str(result[1])}")
        elif command == "5":
            conversion_menu()

def assert_program ():
    try:
        assert(addition('43012', '3243', 5) == '101310'), "Addition example 1: 43012(5) + 3243(5) != 101312(5)"
        assert(addition('A5F', '96BD', 16) == 'A11C'), "Addition example 2: A5F(16) + 96BD(16) != A11C(16)"
        assert(addition('1110101101', '110110011', 2) == '10101100000'), "Addition example 3: 1110101101(2) + 110110011(2) != 10101100000(2)"
        assert (subtraction('A11C', 'A5F', 16) == '96BD'), "Subtraction example 1: A11C(16) - A5F(16) != 96BD(16)"
        assert (subtraction('20053', '4444', 6) == '11205'), "Subtraction example 2: 20053(6) - 4444(6) != 11205(6)"
        assert (subtraction('110001011000', '1110110011', 2) == '100010100101'), "Subtraction example 3: 110001011000(2) - 1110110011(2) != 100010100101(2)"
        assert (multiplication('2031', '3', 4) == '12213'), "Multiplication example 1: 2031(4) * 3(4) != 12213(4)"
        assert (multiplication('2B5F', 'A', 16) == '1B1B6'), "Multiplication example 2: 2B5F(16) * A(16) != 1B1B6(16)"
        assert (division('A5B', '8', 16) == ['14B', '3']), "Division example 1: A5B(16) * 8(16) != 14B(16) r 3"
        assert (division('2043', '5', 8) == ['323', '4']), "Division example 2: 2043(8) * 5(8) != 323(8) r 4"
        assert (successive_division_conversion('A5B', 16, 8) == '5133'), "Conversion by successive divisions example 1: A5B(16) -> 5133(8)"
        assert (intermediate_base_conversion('5133', 8, 16) == 'A5B'), "Conversion using an intermediate base example 1: 5133(8) -> A5B(16)"
        assert (substitution_conversion('354', 6, 8) == '216'), "Conversion using substitutions example 1: 354(6) -> 216(8)"
        assert (substitution_conversion('11011', 2, 4) == '123'), "Conversion using substitutions example 2: 11011(2) -> 123(4)"
        assert (rapid_conversion('3201', 4, 2) == '11100001'), "Conversion using rapid conversions example 1: 3201(4) -> 11100001(2)"
        assert (rapid_conversion('7205346', 8, 2) == '111010000101011100110'), "Conversion using rapid conversions example 2: 7205346(8) -> 111010000101011100110(2)"
        assert (rapid_conversion('60FAB28', 16, 2) == '0110000011111010101100101000'), "Conversion using rapid conversions example 3: 60FAB28(16) -> 0110000011111010101100101000(2)"
        assert (rapid_conversion('1001100011010111', 2, 8) == '114327'), "Conversion using rapid conversions example 4: 1001100011010111(2) -> 1143270(8)"
        assert (rapid_conversion('111000011001010011010', 2, 4) == '13003022122'), "Conversion using rapid conversions example 5: 111000011001010011010(2) -> 13003022122(4)"
        assert (rapid_conversion('110001010110011100101010101000', 2, 16) == '3159CAA8'), "Conversion using rapid conversions example 6: 110001010110011100101010101000(2) -> 3159CAA8(16)"
    except AssertionError as ae:
        print("There was a " + str(type(ae)) + " " + str(ae))
    else:
        print("Assert tests returned addition to be correctly calculated.")
        print("Assert tests returned subtraction to be correctly calculated.")
        print("Assert tests returned multiplication to be correctly calculated.")
        print("Assert tests returned division to be correctly calculated.")
        print("Assert tests returned conversion by successive divisions to be correctly calculated.")
        print("Assert tests returned conversion using an intermediate base to be correctly calculated.")
        print("Assert tests returned conversion by substitution to be correctly calculated.")
        print("Assert tests returned rapid conversion to be correctly calculated.")

def ui():
    #assert_program()
    print("---------------------------------")
    print("Student: Micu Alexia-Claudia")
    print("---------------------------------")
    menu()

ui()