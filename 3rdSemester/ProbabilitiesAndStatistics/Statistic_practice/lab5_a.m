% A
% Given data
X = [20 21 22 23 24 25 26 27];
Y = [75 76 77 78 79 80 81 82];
fX = [2 1 3 6 5 9 2 2]; % frequencies of X
fY = [3 2 2 5 8 8 1 1]; % frequencies of Y

% a) Calculate means
mean_X = mean(X);
mean_Y = mean(Y);

% b) Calculate variances
var_X = var(X, fX);
var_Y = var(Y, fY);

% c) Calculate covariance
cov_XY = cov(X, Y);

% d) Calculate correlation coefficient
corrcoef_XY = corrcoef(X, Y);

% Display the results
fprintf('a) Mean of X: %.2f\n', mean_X);
fprintf('   Mean of Y: %.2f\n', mean_Y);
fprintf('b) Variance of X: %.2f\n', var_X);
fprintf('   Variance of Y: %.2f\n', var_Y);
fprintf('c) Covariance of X and Y: %.2f\n', cov_XY);
fprintf('d) Correlation coefficient: %.4f\n', corrcoef_XY(1,2));
