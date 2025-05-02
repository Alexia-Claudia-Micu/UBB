% Given data
x = [0.5 1.5 2 3 3.5 4.5 5 6 7 8];
f = [5 5.8 5.8 6.8 6.9 7.6 7.8 8.2 9.2 9.9];

% Degree of polynomial (you can choose based on the data shape; let's pick degree 2 for now)
degree = 2;

% Least squares polynomial approximation
p = polyfit(x, f, degree);

% Define interval for plotting
interval = linspace(min(x), max(x), 100);

% Evaluate the polynomial at the points in interval
approx_values = polyval(p, interval);

% Plot the data and the approximation
figure;
plot(x, f, 'o', 'MarkerFaceColor', 'r'); % Original data points
hold on;
plot(interval, approx_values, 'b-', 'LineWidth', 2); % Approximated curve
title('Least Squares Polynomial Approximation');
xlabel('x');
ylabel('f(x)');
legend('Data Points', 'Polynomial Fit');
grid on;
hold off;
