X1 = [46 37 39 48 47 44 35 31 44 37]
X2 = [35 33 31 35 34 30 27 32 31 31]

# variances
v1 = var(X1);
v2 = var(X2);

#means
m1 = mean(X1);
m2 = mean(X2);

#length
n1 = length(X1);
n2 = length(X2);

alpha = 0.05

# to check to variance difference, we use two tailed test
#               - vartest2 - sigma unknown

# Null Hypothesis - they are equal
# Alternate Hypothesis - they are different

#find rejection region - finv because sigma not known
r1 = finv(alpha/2, n1-1, n2-1)
r2 = finv(1-alpha/2, n1-1, n2-1)
RR = [r1 r2]

[h,p,ci,stats] = vartest2(X1,X2,'alpha', alpha)

if h == 1
  disp('The null hypothesis is rejected -> they seem to be different')
else
  disp('The null hypothesis is NOT rejected -> they seem to be Equal')

c = (var1/n1)/(var1/n1+var2/n2)
n = c^2/(n1-1)+((1-c)^2)/n2-1
n = 1/n

t = tinv(1-alpha/2, n)

c1 = m1-m2-t*sqrt(var1/n1 + var2/n2)
c2 = m1-m2+t*sqrt(var1/n1 + var2/n2)


