pkg load statistics

X = [ 7 7 4 5 9 9 ...
      4 12 8 1 8 7 ...
      3 13 2 1 17 7 ...
      12 5 6 2 1 13 ...
      14 10 2 4 9 11 ...
      3 5 12 6 10 7];

n = length(X);
sigma = 5;
one_minus_alpha = input("Confidence level>");
alpha = 1 - one_minus_alpha;

m1 = mean(X) - sigma/sqrt(n)*norminv(1-alpha/2, 0,1);
m2 = mean(X) + sigma/sqrt(n)*norminv(1-alpha/2, 0,1);

printf("The confidence interval for the theoretical mean when sigma is known is (m1, m2) = (%4.3f, %4.3f)\n", m1, m2);

m1_b = mean(X) - std(X)/sqrt(n)*tinv(1-alpha/2, n-1);
m2_b = mean(X) + std(X)/sqrt(n)*tinv(1-alpha/2, n-1);

printf("The confidence interval for the theoretical mean when sigma is unknown is (m1, m2) = (%4.3f, %4.3f)\n", m1_b, m2_b);

v1 = (n-1)*var(X)/chi2inv(1-alpha/2, n-1);
v2 = (n-1)*var(X)/chi2inv(alpha/2, n-1);

printf("The confidence interval for the theoretical mean when sigma is unknown is (m1, m2) = (%4.3f, %4.3f)\n", v1,v2);

s1 = sqrt(v1);
s2 = sqrt(v2);

printf("The confidence interval for the population standard deviation (m1, m2) = (%4.3f, %4.3f)\n", s1,s2);

