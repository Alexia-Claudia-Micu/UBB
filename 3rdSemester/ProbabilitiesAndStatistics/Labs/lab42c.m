# lab 4 2 c
pkg load statistics
N=input("Give nr of simulations: ");
p=input("Give nr of victories: ");

X=zeros(1,N);
for i=1:N
X(i)=0;
while rand>=p
  X(i)=X(i)+1;
endwhile
endfor

U_X=unique(X);
n_X= hist(X, length(U_X));
rel_freq=n_X/N

K=0:20;
P_K=geopdf(K,p);
plot(U_X,rel_freq,'*',K,P_K,'ro');
