pkg load statistics
n = input('Give the number of trials n=');
p = input('Give the probability of success p=');
# n = nr of trials, a natural number
# p = probability of success, p is a number between 0 and 1

x = 0:1:n;
#x is the number of successes in n trials

px = binopdf(x,n,p);
plot(x,px,'r+');
hold on

xx = 0:0.01:n;
cx = binocdf(xx,n,p);
plot(xx,cx,'b');
