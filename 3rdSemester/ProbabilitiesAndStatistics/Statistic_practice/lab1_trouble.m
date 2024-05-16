% Generate some sample data
x = linspace(0, 10, 100);  % Create a vector of 100 points from 0 to 10

y1 = sin(x);              % Sine wave
y2 = cos(x);              % Cosine wave
y3 = 0.5 * x;             % Linear function

% Plot the first graph (sin(x)) with a blue solid line
plot(x, y1, 'b-');  % 'b-' represents blue solid line

hold on;  % Keep the current plot and add the next one

% Plot the second graph (cos(x)) with a red dashed line
plot(x, y2, 'r--');  % 'r--' represents red dashed line

% Plot the third graph (0.5*x) with a green dotted line
plot(x, y3, 'g:');   % 'g:' represents green dotted line

hold off;  % Release the hold on the current plot

% Add labels and a legend
xlabel('X-axis');
ylabel('Y-axis');
title('Three Simple Graphs');
legend('sin(x)', 'cos(x)', '0.5*x');

% Display the grid
grid on;

