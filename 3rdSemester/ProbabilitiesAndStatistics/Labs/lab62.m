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

n1 = length(X1);
n2 = length(X2);
alpha = 0.05

f_value = finv(1-alpha/2,n1-1,n2-1)
RR = [-inf, finv(alpha/2, n1-1, n2-1)]
RR = [finv(1-alpha/2, n1-1, n2-1), inf]

[h_var, p_var, ci_var, stats_var] = vartest2(X1, X2, "alpha", alpha)
# h = 0 sau 1
# p - printat
# ci confidence interval
# stats - printed

if h_var == 0
  disp("good")
else
  disp("bad")
end

n = n1 + n2 - 2
t2 = tinv(1 - alpha, n) % quantile for right-tailed test (for rejection region)
[H2, P2, CI2, ZVAL2] = ttest2(X1, X2, "alpha", alpha, "tail", "right")

H2
v1=var(X1)
v2=var(X2)

c = (v1/n1)/(v1/n1 + v2/n2)
n = c^2/(n1 - 1) + (1 - c)^2/(n2 - 1)
n = 1/n
t2 = tinv(1 - alpha, n) % quantile for right-tailed test (for rejection region)
[H2, P2, CI2, ZVAL2] = ttest2(X1, X2, 'alpha', alpha, 'tail', 'right') % option "unequal" if variances are not equal

H2
