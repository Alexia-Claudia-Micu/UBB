% Two-sample t-test assuming equal variances
alpha = 0.05;
[h_mean, p_mean, ci_mean, stats_mean] = ttest2(premium, regular, 'alpha', alpha);

% Display results
disp('Part b: Two-Sample t-test for Means');
disp(['p-value: ', num2str(p_mean)]);
if h_mean == 1
    disp('Reject the null hypothesis. There is evidence that gas mileage is higher with premium gasoline.');
else
    disp('Do not reject the null hypothesis. There is no strong evidence that gas mileage differs between premium and regular gasoline.');
end


#---------------------------------

% Data
premium = [22.4 21.7 17.7 14.8 24.5 23.4 19.6 19.6 21.6 23.3];
regular = [12.1 14.8 22.4 21.6 15.4 12.6 24.8 20.0 14.0 12.2];

% Test for equality of variances
alpha = 0.05;
[h_var, p_var, ci_var, stats_var] = vartest2(premium, regular, 'alpha', alpha);

% Display results
disp('Part a: Test for Equality of Variances');
disp(['p-value: ', num2str(p_var)]);
if h_var == 1
    disp('Reject the null hypothesis. There is evidence that the variances are not equal.');
else
    disp('Do not reject the null hypothesis. There is no strong evidence that the variances differ.');
end

