pkg load statistics
X1 = [ 22.4 21.7 ...
       24.5 23.4 ...
       21.6 23.3 ...
       22.4 21.6 ...
       24.8 20.0
      ]
X2 = [ 17.7 14.8 ...
       19.6 19.6 ...
       12.1 14.8 ...
       15.4 12.6 ...
       14.0 12.2
      ]

n1 = length(X1)
n2 = length(X2)

Sp = sqrt(((n1-1)*(var(X1)) + (n2-1)*(var(X2)))/(n1+n2-2))

one_minus_alpha = input("Confidence level>");
alpha = 1 - one_minus_alpha;

m1=mean(X1)-mean(X2)-tinv(1-alpha/2,n1+n2-2)*Sp*sqrt(1/n1+1/n2)
m2=mean(X1)-mean(X2)+tinv(1-alpha/2,n1+n2-2)*Sp*sqrt(1/n1+1/n2)

printf("The confidence interval for the difference of population means when sigma1 = sigma2 unknown is (m1, m2) = (%4.3f, %4.3f)\n", m1, m2);

c=var(X1)/n1/(var(X1)-n1 + var(X2)-n2)
aux = c^2/(n1-1)+(1-c)^2/(n2-1)
n=ceil(1/aux)

m1_b=mean(X1)-mean(X2)-tinv(1-alpha/2,n)*sqrt(var(X1)/n1+var(X2)/n2)
m2_b=mean(X1)-mean(X2)+tinv(1-alpha/2,n)*sqrt(var(X1)/n1+var(X2)/n2)

printf("The confidence interval for the difference of population means when sigma1 = sigma2 unknown is (m1, m2) = (%4.3f, %4.3f)\n", m1_b, m2_b);

m1_c=mean(X1)-mean(X2)-finv(1-alpha/2,n1-1)*sqrt(var(X1)/n1+var(X2)/n2)
m2_c=mean(X1)-mean(X2)+finv(1-alpha/2,n2-1)*sqrt(var(X1)/n1+var(X2)/n2)

printf("The confidence interval for the difference of population means when sigma1 = sigma2 unknown is (m1, m2) = (%4.3f, %4.3f)\n", m1_c, m2_c);

# (10 11 12... -values
#   7  1  2... - freq
# X = [10,10,10,10,10,10,10,11,12,12] - repmat
# x = [10*ones(1,7) 11*ones(1,1), 12*ones(1,2)...]
# cov =? corrcoef=?
