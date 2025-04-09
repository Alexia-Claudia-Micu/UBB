% Function to build Newton Divided Differences Table
function c = divided_differences(x, y)
    n = length(x);
    c = y;
    for j = 2:n
        c(j:n) = (c(j:n) - c(j-1:n-1)) ./ (x(j:n) - x(1:n-j+1));
    end
end

% Function to evaluate Newton polynomial
function p = newton_poly(c, x_nodes, x_eval)
    n = length(c);
    p = c(n);
    for k = n-1:-1:1
        p = p .* (x_eval - x_nodes(k)) + c(k);
    end
end

% === Main script ===

% Given nodes
x_nodes = [0, 1/3, 1/2, 1];
y_nodes = cos(pi * x_nodes);

% 1. Compute coefficients using Newton's divided differences
c = divided_differences(x_nodes, y_nodes);

% 2. Define fine grid for plotting
x_fine = linspace(0, 1, 200);
y_true = cos(pi * x_fine);
y_interp = newton_poly(c, x_nodes, x_fine);

% 3. Plot
figure;
plot(x_fine, y_true, 'b-', 'LineWidth', 2); hold on;
plot(x_fine, y_interp, 'r--', 'LineWidth', 2);
plot(x_nodes, y_nodes, 'ko', 'MarkerFaceColor', 'k'); % nodes
legend('f(x) = cos(\pi x)', 'Interpolating Polynomial L_3(x)', 'Nodes');
xlabel('x');
ylabel('y');
title('Interpolation using Newton''s Divided Differences');
grid on;

% 4. Approximate cos(pi/5) using L3
x_approx = pi/5 / pi;  % x corresponding to pi/5
approx_value = newton_poly(c, x_nodes, x_approx);
fprintf('Approximation of cos(pi/5) = %.6f\n', approx_value);
fprintf('Actual value of cos(pi/5)   = %.6f\n', cos(pi/5));
fprintf('Absolute error              = %.6e\n', abs(approx_value - cos(pi/5)));
