#pdf: f(x) = P(X=x)
#cdf: f(x) = P(X<=x)
#P(X<2) = P(X<=1)
#P(X>=1)=1-P(X<1) = 1-P(X<=o) = 1-P(X=0)
#P(x>1)=1-P(x<=1)
pkg load statistics
A=binopdf(0,3,0.5)
A
B=1-binopdf(0,3,0.5)
B
C=binocdf(2,3,0.2)
C
#P(x<2)=P(x<=1)
D=binocdf(1,3,0.2)
D=binocdf(2,3,0.2)-binopdf(2,3,0.2)
D
E=1-binocdf(1,3,0.5)+pdf(1,2,0.5)


