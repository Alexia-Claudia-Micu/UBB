% Define the range of x values
x_values = linspace(0, 3, 100);

% Define the functions
y1 = (x_values.^5)/10;
y2 = x_values .* sin(x_values);
y3 = cos(x_values);

% Plot all functions on the same set of axes
figure;
plot(x_values, y1, 'r-', 'LineWidth', 2, 'DisplayName', '(x^5)/10');
hold on;
plot(x_values, y2, 'g--', 'LineWidth', 2, 'DisplayName', 'x*sin(x)');
plot(x_values, y3, 'b-.', 'LineWidth', 2, 'DisplayName', 'cos(x)');
hold off;

% Add title and legend
title('Graphs of Functions');
legend('Location', 'Northwest');

% Create separate plots in the same window
figure;

subplot(3, 1, 1);
plot(x_values, y1, 'r-', 'LineWidth', 2);
title('(x^5)/10');

subplot(3, 1, 2);
plot(x_values, y2, 'g--', 'LineWidth', 2);
title('x*sin(x)');

subplot(3, 1, 3);
plot(x_values, y3, 'b-.', 'LineWidth', 2);
title('cos(x)');
