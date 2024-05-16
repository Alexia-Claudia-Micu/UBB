#aprox in a limit case the poisson distribution with the help of binary
# how to compute for pdf the value for the ? of poisson
# draw in the same thing bino and poisson pdf
# n>=30
# p <0.05
n=50;
p = 0.03;
k = 0:n;

y = binopdf(k,n,p)
plot(k,y,'b-')
hold on
z = poisspdf(k,n.*p)
plot(k,z,'r--')

