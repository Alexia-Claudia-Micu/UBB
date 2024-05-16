% Generate some sample data
x = linspace(0, 10, 100);  % Create a vector of 100 points from 0 to 10

y1 = sin(x);              % Sine wave
y2 = cos(x);              % Cosine wave
y3 = 0.5 * x;             % Linear function

% Create a 2x2 subplot and plot the first graph (sin(x))
subplot(3, 1, 1);
plot(x, y1, 'b-');  % 'b-' represents blue solid line
xlabel('X-axis');
ylabel('Y-axis');
title('Graph of sin(x)');
grid on;

% Create a 2x2 subplot and plot the second graph (cos(x))
subplot(3, 1, 2);
plot(x, y2, 'r--');  % 'r--' represents red dashed line
xlabel('X-axis');
ylabel('Y-axis');
title('Graph of cos(x)');
grid on;

% Create a 2x2 subplot and plot the third graph (0.5*x))
subplot(3, 1, 3);
plot(x, y3, 'g:');   % 'g:' represents green dotted line
xlabel('X-axis');
ylabel('Y-axis');
title('Graph of 0.5*x');
grid on;
