% Define function and derivative
f = @(x) (x + 1) ./ (3*x.^2 + 2*x + 1);
syms xs
fs = (xs + 1) / (3*xs^2 + 2*xs + 1);
df = matlabFunction(diff(fs)); % derivative function

% Nodes
nodes = linspace(-2, 4, 7);
fnodes = f(nodes);
dfnodes = df(nodes);

% Fine grid
xx = linspace(-2, 4, 1000);
fxx = f(xx);

% Lagrange interpolant
p = polyfit(nodes, fnodes, length(nodes)-1);
lagrange_interp = polyval(p, xx);

% de Boor spline
deBoor_interp = spline(nodes, fnodes, xx);

% --- Hermite Interpolation (properly) ---
n = length(nodes);
z = repelem(nodes,2);
Q = zeros(2*n,2*n);
Q(:,1) = repelem(fnodes,2);
Q(1:2:end,2) = dfnodes; % derivatives on odd rows
for i = 2:2*n
    if mod(i,2) == 0
        Q(i,2) = (Q(i,1)-Q(i-1,1)) / (z(i)-z(i-1));
    end
end
for j = 3:2*n
    for i = j:2*n
        Q(i,j) = (Q(i,j-1) - Q(i-1,j-1)) / (z(i) - z(i-j+1));
    end
end

% Evaluate Hermite interpolation
hermite_interp = zeros(size(xx));
for k = 1:length(xx)
    prod = 1;
    hermite_interp(k) = Q(1,1);
    for j = 1:2*n-1
        prod = prod * (xx(k) - z(j));
        hermite_interp(k) = hermite_interp(k) + Q(j+1,j+1)*prod;
    end
end

% Plotting
figure;
hold on;
plot(nodes, fnodes, 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 8); % Nodes
plot(xx, fxx, 'k-', 'LineWidth', 2); % f(x)
plot(xx, lagrange_interp, 'r--', 'LineWidth', 1.5); % Lagrange
plot(xx, deBoor_interp, 'g:', 'LineWidth', 1.5); % deBoor spline
plot(xx, hermite_interp, 'b-.', 'LineWidth', 3); % Hermite (thicker now!)
legend('Nodes', 'Original f(x)', 'Lagrange', 'deBoor spline', 'Hermite', 'Location', 'Best');
title('Interpolation Comparison (corrected)');
xlabel('x');
ylabel('y');
grid on;
hold off;
