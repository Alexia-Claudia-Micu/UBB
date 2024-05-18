# Solve the problem from the second set here
'''
7. Determine the twin prime numbers `p1` and `p2` immediately larger than the given non-null natural
 number `n`. Two prime numbers `p` and `q` are called twin if `q - p = 2`.
'''

def create_vect ( n, v ):
    for i in range  (1, 30002 ):
        v.append(0)
    v[1] = 1
    v[0] = 1
    for i in range ( 2, 15001 ):
        x = i * 2
        if v[i] == 0 and v[i-2] == 0 and i-2 > n:
            print ( "The two twin prime numbers larger than " + str(n) + " are " + str(i-2) + " and " + str(i) )
            return
        while x <= 30000:# Sirul lui Ieratostene
            v[x] = 1
            x += i

n=int( input("Value for n: ") )
v=[]
create_vect(n,v)