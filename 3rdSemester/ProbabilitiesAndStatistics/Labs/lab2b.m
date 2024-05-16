N=input("Nr simulations>")
U=rand(3,N)
Y=(U<0.5)
X=sum(Y)
#clf clears
#clf
hist(X)
