X=[ 7 7 4 5 9 9 ...
    4 12 8 1 8 7 ...
    3 13 2 1 17 7 ...
    12 5 6 2 1 13 ...
    14 10 2 4 9 11 ...
    3 5 12 6 10 7];
n=36;
sigma=5;
one_minus_alpha=input("Give comfidence level: ");
alpha=1-one_minus_alpha;
m1=mean(X)-sigma/sqrt(n)*norminv(1-alpha/2,0,1);
m2=mean(X)+sigma/sqrt(n)*norminv(1-alpha/2,0,1);
fprintf("The confidence interval for the theoretical mean when sigma is known is (m1,m2)=(%4.3f,%4.3f)\n",m1,m2)

m1_b=mean(X)-std(X)/sqrt(n)*tinv(1-alpha/2,n-1);
m2_b=mean(X)+std(X)/sqrt(n)*tinv(1-alpha/2,n-1);
fprintf("The confidence interval for the theoretical mean when sigma is unknown is (m1b,m2b)=(%4.3f,%4.3f)\n",m1_b,m2_b)

v1=(n-1)*var(X)/chi2inv((1-alpha)/2,n-1);
v2=(n-1)*var(X)/chi2inv(alpha/2,n-1);
fprintf("The confidence interval for the theoretical population variance is (v1,v2)=(%4.3f,%4.3f)\n",v1,v2)

s1=sqrt(v1);
s2=sqrt(v2);
fprintf("The confidence interval for the standard population variance is (s1,s2)=(%4.3f,%4.3f)\n",s1,s2)
