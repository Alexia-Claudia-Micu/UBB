# bernouli
N = input("Give nr of simulations: ");
p = input("Give probability of success (p): ");

U = rand(1, N);
X = U < p;

% Verification and plotting
U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq = n_X / N;
K = [0, 1];
P_K = [1 - p, p];
plot(U_X, rel_freq, '*', K, P_K, 'ro');
title(['Bernoulli Distribution with p = ', num2str(p)]);
xlabel('Random Variable (X)');
ylabel('Relative Frequency');
legend('Simulated Distribution', 'Theoretical Distribution');

#binomial
N = input("Give nr of simulations: ");
n = input("Give nr of trials: ");
p = input("Give probability of success (p): ");

U = rand(n, N);
X = sum(U < p);

% Verification and plotting
U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq = n_X / N;
K = 0:n;
P_K = binopdf(K, n, p);
plot(U_X, rel_freq, '*', K, P_K, 'ro');
title(['Binomial Distribution with n = ', num2str(n), ' and p = ', num2str(p)]);
xlabel('Random Variable (X)');
ylabel('Relative Frequency');
legend('Simulated Distribution', 'Theoretical Distribution');

#Geometric
N = input("Give nr of simulations: ");
p = input("Give probability of success (p): ");

U = rand(1, N);
X = ceil(log(1 - U) / log(1 - p));

% Verification and plotting
U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq = n_X / N;
K = 0:max(U_X);
P_K = p * (1 - p).^(K-1);
plot(U_X, rel_freq, '*', K, P_K, 'ro');
title(['Geometric Distribution with p = ', num2str(p)]);
xlabel('Random Variable (X)');
ylabel('Relative Frequency');
legend('Simulated Distribution', 'Theoretical Distribution');

#pascal
N = input("Give nr of simulations: ");
n = input("Give nr of failures required (n): ");
p = input("Give probability of success (p): ");

U = rand(n, N);
X = sum(ceil(log(1 - U) / log(1 - p)), 1);

% Verification and plotting
U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq = n_X / N;
K = 0:max(U_X);
P_K = nbinpdf(K, n, p);
plot(U_X, rel_freq, '*', K, P_K, 'ro');
title(['Pascal Distribution with n = ', num2str(n), ' and p = ', num2str(p)]);
xlabel('Random Variable (X)');
ylabel('Relative Frequency');
legend('Simulated Distribution', 'Theoretical Distribution');
