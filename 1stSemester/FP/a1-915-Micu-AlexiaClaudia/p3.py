# Solve the problem from the third set here

'''
13. Determine the `n-th`  element of the sequence `1,2,3,2,5,2,3,7,2,3,2,5,...` obtained from the sequence of natural
numbers by replacing composed numbers with their prime divisors, without memorizing the elements of the sequence.
'''


def solve ( n ):
    k=1
    x=1
    while k < n:
        d=2
        aux=x
        x += 1
        while aux != 1 and k < n:
            if aux % d == 0:
                k += 1
                while aux % d == 0:
                    aux //= d
            d += 1
    return d-1

n= int ( input ("Value for n: ") )
sol= solve(n)
print("The " + str(n) + "-th element of the sequence is " + str (sol))
