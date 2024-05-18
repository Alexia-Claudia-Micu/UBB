# Solve the problem from the first set here
'''
2. Given natural number `n`, determine the prime numbers `p1` and `p2` such that `n = p1 + p2` (check the Goldbach hypothesis).
'''

def create_vect ( n, v ): # Sirul lui Ieratostene
    for i in range  (1, n + 2 ):
        v.append(0)
    for i in range ( 2, n//2 + 1 ):
        x = i * 2
        while x <= n:
            v[x] = 1
            x += i
    v[1] = 1

def goldbach ( n, v ):
    sem=0
    for i in range ( 2, n ):
        if v[i] == 0 and v[ n-i ] == 0:
            print(str(i) + " + " + str(n-i) + " = " + str(n) )
            sem=1
    if sem == 0:
        print ( "There are no pairs." )


n=int( input("Value for n: ") )
v=[]
create_vect(n,v)
#print ( v )
goldbach(n,v)