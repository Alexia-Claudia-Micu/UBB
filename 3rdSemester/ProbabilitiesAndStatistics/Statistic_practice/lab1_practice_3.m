x  = linspace(0,3,12);

y1 = (x.^5)/10
y2 = x .* sin(x)
y3 = cos(x)

plot(x,y1,'b-');
hold on
plot(x,y2,'r--');
plot(x,y3,'g:');

xlabel('X-axis');
ylabel('Y-axis');
title('Three Simple Graphs');
legend('sin(x)', 'cos(x)', '0.5*x');

% Display the grid
grid on;
