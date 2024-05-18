from functions import generate_secret_nr
from functions import check_guess
def main():
    secret_nr = generate_secret_nr()

    possible_ends = ["player wins", "computer wins"]
    my_end = ""

    while my_end not in possible_ends:
        guess = int(input("Guess a number > "))

        my_end = check_guess(guess, secret_nr)
        print(my_end)

main()
