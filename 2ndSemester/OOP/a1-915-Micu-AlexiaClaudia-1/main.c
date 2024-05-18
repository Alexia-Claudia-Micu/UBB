#include <stdio.h>
#include <string.h>

int ReadVector(int* vector)
{
    /*
     *  Reads a vector from the keyboard
     *  vector : vector of integers
     *  returns: the length of the vector that has been read
     */
    printf("Give values for vector >");
    int number, vector_length = 0;
    scanf("%d", &number);
    while (number != 0)
    {
        vector[vector_length] = number;
        vector_length ++;
        scanf("%d", &number);
    }
    return vector_length;
}

void PrintVector(int* vector, int vector_length, int start_index, int end_index)
{
    /*
     * Prints the vector
     */
    for (int i = start_index; i < end_index; i++)
        printf("%d ", vector[i]);
    printf("\n\n");
}

int Exponent_of_the_primeNumber_in_naturalNumber(int prime_number, int natural_number)
{
    /*
     * Checks the exponent to which p appears in n
     * prime_number: the prime integer number whose exponent we check for
     * natural_number: the natural number in which we check
     * return: the exponent - integer number
     */
    int exponent = 0;

    while(natural_number % prime_number == 0)
    {
        natural_number /= prime_number;
        exponent ++;
    }

    return exponent;
}

int greatest_common_divisor(int number1, int number2)
{
    /*
     * Determine the greatest common divisor using Euclid's algorithm
     * a & b: the numbers fot which we compute gcd
     * returns: the gcd of a&b
     */
    if( number1 < number2 )
    {
        int swap_holder;
        swap_holder = number2;
        number2 = number1;
        number1 = swap_holder;
    }
    if ( number1 == 1 || number2 == 1)
        return 1;
    int remainder;
    while(number2 != 0)
    {
        remainder = number1 % number2;
        number1 = number2;
        number2 = remainder;
    }
    return number1;
}

void longest_contiguous_sequence_of_partial_primes(int vector[], int vector_length, int* start_position, int* length_of_sequence)
{
    /*
     * Checks for the longest contiguous sequence of partial primes from the given vector;
     * vector: vector of integers
     * vector_length: the length of vector
     * return: prints the l.c.s...
     */
    int maximum_length = 0, current_length = 1, start_index_of_max_length;
    for (int i = 1; i < vector_length; i++)
        if (greatest_common_divisor(vector[i-1], vector[i]) == 1)
        {
            current_length ++;
            if(current_length > maximum_length)
            {
                maximum_length = current_length;
                start_index_of_max_length = i - current_length + 1;
            }
        } else
            current_length = 1;
    *start_position = start_index_of_max_length;
    *length_of_sequence = maximum_length;
}

int main()
{
    char command[20];
    int vector[20], vector_length;
    strcpy(command, "1");

    while(strcmp(command, "0") != 0)
    {
        printf("1. Read vector from console.\n");
        printf("2. 5.Calculate the exponent to which a given prime number appears in a given natural number.\n");
        printf("3. 5.Display the longest contiguous sequence of partial prime numbers in a given vector.\n" );
        printf("0. Quit\n");
        printf("Give command >  ");
        scanf("%s", command);
        printf("\n");
        if(strcmp(command, "1") == 0)
        {
            vector_length = ReadVector(vector);
            PrintVector(vector, vector_length, 0, vector_length);
        }
        else
            if(strcmp(command, "2") == 0)
            {
                int prime_number, natural_number, exponent_of_the_primeNumber_in_naturalNumber ;
                printf("Give a prime number (p) >");
                scanf("%d", &prime_number);
                printf("Give a non-null natural number (n) >");
                scanf("%d", &natural_number);
                exponent_of_the_primeNumber_in_naturalNumber = Exponent_of_the_primeNumber_in_naturalNumber(prime_number, natural_number);
                printf("The exponent of p in n is: %d", exponent_of_the_primeNumber_in_naturalNumber);
            }
            else
                if(strcmp(command, "3") == 0)
                {
                    int* start_position;
                    int* longest_sequence_length;
                    vector_length = ReadVector(vector);
                    longest_contiguous_sequence_of_partial_primes(vector, vector_length, start_position, longest_sequence_length);
                    PrintVector(vector, vector_length, *start_position, *start_position + *longest_sequence_length);
                }
        printf("\n");
    }

    return 0;
}
