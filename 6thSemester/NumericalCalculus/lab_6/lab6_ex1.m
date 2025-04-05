% Define the given function
f = @(x) (x + 1) ./ (3*x.^2 + 2*x + 1);

% a) Compute the Lagrange polynomial L9f
n = 9;
x_nodes = linspace(-2, 4, n+1); % 10 equally spaced nodes in [-2, 4]
y_nodes = f(x_nodes);

% Lagrange interpolation function
L9f = @(x) lagrange_interp(x_nodes, y_nodes, x);

% b) Plot the function f, L9f, and the nodes
x_plot = linspace(-2, 4, 1000);
f_plot = f(x_plot);
L9f_plot = arrayfun(@(x) L9f(x), x_plot);

figure;
plot(x_plot, f_plot, 'b', 'LineWidth', 1.5); hold on;
plot(x_plot, L9f_plot, 'r--', 'LineWidth', 1.5);
plot(x_nodes, y_nodes, 'ko', 'MarkerFaceColor', 'k');
legend('f(x)', 'L_9f(x)', 'Nodes');
title('Function f and Lagrange Polynomial L_9f');
xlabel('x'); ylabel('y'); grid on;

% c) Plot error |f - L9f| and compute max error
errors = abs(f_plot - L9f_plot);
figure;
plot(x_plot, errors, 'm', 'LineWidth', 1.5);
title('Error |f(x) - L_9f(x)|');
xlabel('x'); ylabel('Error'); grid on;
max_error = max(errors);
fprintf('Max error: %.6f\n', max_error);

% d) Approximate f(1/2) and compute error
x_eval = 0.5;
f_true = f(x_eval);
f_approx = L9f(x_eval);
approx_error = abs(f_true - f_approx);
fprintf('f(1/2) ≈ %.6f by L9f. Error: %.6f\n', f_approx, approx_error);

function L = lagrange_interp(x_nodes, y_nodes, x_eval)
    n = length(x_nodes);
    L = 0;
    for i = 1:n
        li = 1;
        for j = 1:n
            if j ~= i
                li = li * (x_eval - x_nodes(j)) / (x_nodes(i) - x_nodes(j));
            end
        end
        L = L + y_nodes(i) * li;
    end
end

