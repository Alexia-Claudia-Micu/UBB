X1 = [4.6 0.7 4.2 1.9 4.8 6.1 4.7 5.5 5.4]
X2 = [2.5 1.3 2.0 1.8 2.7 3.2 3.0 3.5 3.4]

vx1 = var(X1)
vx2 = var(X2)

n1 = length(X1)
n2 = length(X2)

m1 = mean(X1)
m2 = mean(X2)

alpha = 0.05

# differ => two tailed test and no sigma is known
# H0 - they are equal
# H1 - they differ

[ha,pa,cia,valstata] = vartest2(X1, X2, 'alpha', alpha)
r1 = finv(alpha/2, n1-1,n2-1)
r2 = finv(1-alpha/2, n1-1, n2-2)
RR = [r1 r2]

if ha == 1
  disp('the null hypothesis is rejected -> variances seem to differ')
else
  disp('the null hypothesis is not rejected _> variances seem to be equal')
end

# null hypothesis - larger
# h1 - not larger
[H2, P2, CI2, ZVAL2] = ttest2(X1, X2, "alpha", alpha, "tail", "right")

if H2 == 1
  disp('the null hypothesis is rejected')
else
  disp('the null hypothesis is not rejected')
end
