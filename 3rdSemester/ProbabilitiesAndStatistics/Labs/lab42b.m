# lab 4 2 b
pkg load statistics

N=input("Give nr of simulations: ");
n=input("Give nr of trials: ");
p=input("Give nr of victories: ");

U = rand(n,N);
X=sum(U<p);

#verif
U_X=unique(X);
n_X= hist(X, length(U_X));
rel_freq=n_X/N
K=0:n;
P_K=binopdf(K,n,p);
plot(U_X,rel_freq,'*',K,P_K,'ro');
