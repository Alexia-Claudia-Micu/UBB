pkg load statistics

#n - nr of trials
# p - probability of success
n = 3;
p = 0.5;

A = binopdf(0, 3, 0.5);
B = 1 - binopdf(0, 3, 0.5);
C = binocdf(2,3,0.5);
D=binocdf(2,3,0.5); # P(x<=2)
D=binocdf(2,3,0.5)-binopdf(2,3,0.5); #P(x<2)
E=1 - binopdf(0,3,0.5); # p(x>=1);
E
F = E - binopdf(1,3,0.5);
F

% Number of coin tosses
num_tosses = 3;

% Probability of getting heads on a single toss
p_heads = 0.5;

% Simulate coin tosses
toss_results = rand(1, num_tosses) < p_heads;

% Compute the number of heads (variable X)
num_heads = sum(toss_results);

% Display the results
disp('Coin Toss Results:');
disp(toss_results);
disp(['Number of Heads (X): ', num2str(num_heads)]);

