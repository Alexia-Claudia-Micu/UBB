p=input("give p in between 0.05 and 0.95 >")
n=101
k=0:n;
y=binopdf(k,n,p)
plot(k,y,'b-')
hold on
z = normpdf(k,n.*p,sqrt(n.*p.*(1-p)))
plot(k,z,'r--')

