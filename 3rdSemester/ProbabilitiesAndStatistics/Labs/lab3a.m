n=input("n>")
m=input("m>")
alpha=input("alpha>")
beta=input("beta>")

normal_smaller=normcdf(0,n,m)
normal_greater=1-normcdf(0,n,m)

student_smaller=tcdf(0,n)
student_greater=1-tcdf(0,n)

chi_smaller=chi2cdf(0,n)
chi_greater=1-chi2cdf(0,n)

fisher_smaller=fcdf(0,n,m)
fisher_greater=1-fcdf(0,n,m)

#P(x>=0)=1-P(x<0) (probability law is continuous) = 1-P(x<=0)
#P(-1<=X<=1) = continuous -> cdf(1)-cdf(-1)
#P(a<X<=b) = cdf(b) - cdf(a)

B = fcdf(1,n,m)-fcdf(-1,n,m)

#P((X<=-1)U(X>=1))=1-P(-1<X<1)

C= 1-B

x_alpha = finv(alpha,n,m)
x_beta = finv(1-beta,n,m)


