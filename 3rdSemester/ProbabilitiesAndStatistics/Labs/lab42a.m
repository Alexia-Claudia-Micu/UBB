# lab 4 2 a
N=input("Give nr of simulations: ");
P=input("Give nr of permutations: ");
U=rand(1,N);
X=(U<P);

#verif
U_X = [0 1];
n_X= hist(X, length(U_X));
rel_freq=n_X/N

