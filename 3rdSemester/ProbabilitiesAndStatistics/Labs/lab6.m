X = [7 7 4 5 9 9 ...
     4 12 8 1 8 7 ...
     3 13 2 1 17 7 ...
     12 5 6 2 1 13 ...
     14 10 2 4 9 11 ...
     3 5 12 6 10 7];

n=length(X);
alpha=input("Provide the significance level: ");
% The null hyp. is HO: m=8.5(it is also >= 8.5,
% the standard is met)
% the alt. hyp. is H1: m < 8.5(the standard is not met)
% left-tail test

disp("We use the left tail test for the mean when sigma is known. ");
sigma=5;
m0=8.5; % test value

% help ztest
[h,pval, ci, zvalue] = ztest(X, m0, sigma, "alpha", alpha, "tail", "left");
zalpha=norminv(alpha, 0, 1);
RR=[-inf zalpha];
if(h==1)
  disp("The null hyp. H0 is rejected.\n");
  disp("The data sugests that the standard is not met.\n");
 else
  disp("The null hyp. is not rejected.\n");
  disp("The data sugests that the standard is met.\n");
end

X = [7 7 4 5 9 9 ...
     4 12 8 1 8 7 ...
     3 13 2 1 17 7 ...
     12 5 6 2 1 13 ...
     14 10 2 4 9 11 ...
     3 5 12 6 10 7];

n = length(X);
alpha = input("Provide the significance level: ");
mu0 = 5.5; % test value

[h, pval, ci, stats] = ttest(X, mu0, "alpha", alpha, "tail", "right");

if h == 1
    disp("The null hyp. H0 is rejected.");
    disp("The data suggests that, on average, the number of files stored exceeds 5.5.");
else
    disp("The null hyp. is not rejected.");
    disp("The data does not suggest that, on average, the number of files stored exceeds 5.5.");
end

# ttest for sigma not known
# ztest for sigma knowns

# daca sigma known - norminv rr - apartine N
# not known - tinv

#tt is zvalue

# s - std(x)
# s^2 - var(x)
#sp - formula
