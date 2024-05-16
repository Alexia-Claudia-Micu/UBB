X1=[22.4 21.7 ...
    24.5 23.4 ...
    21.6 23.3 ...
    22.4 21.6 ...
    24.8 20.0];
X2=[17.7 14.8 ...
   19.6 19.6 ...
   12.1 14.8 ...
   15.4 12.6 ...
   14.0 12.2];

n1=10;
n2=10;
sp=sqrt((n1-1)*var(X1)+(n2-1)*var(X2)/(n1+n2-2));
one_minus_alpha=input("Give comfidence level: ");
alpha=1-one_minus_alpha;
m1=mean(X1)-mean(X2)-tinv(one_minus_alpha/2,n1+n2-2)*sp*sqrt(1/n1+1/n2);
m2=mean(X1)-mean(X2)+tinv(one_minus_alpha/2,n1+n2-2)*sp*sqrt(1/n1+1/n2);

fprintf("The confidence interval for the difference of population means when sigma1=sigma2 unknown (m1,m2)=(%4.3f,%4.3f)\n",m2,m1);

c=((var(X1)/n1)/((var(X1)/n1)+(var(X2)/n2)));
aux=c^2/(n1-1)+(1-c)^2/(n2-1);
n=ceil(1/aux);

m1_b=mean(X1)-mean(X2)-tinv(one_minus_alpha/2,n)*sqrt(var(X1)/n1+(X2)/n2);
m2_b=mean(X1)-mean(X2)+tinv(one_minus_alpha/2,n)*sqrt(var(X1)/n1+(X2)/n2);

fprintf("The confidence interval for the difference of population means when sigma1!=sigma2 unknown (m1,m2)=(%4.3f,%4.3f)",m2_b,m1_b);
