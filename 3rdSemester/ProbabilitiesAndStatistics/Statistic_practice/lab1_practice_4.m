x = linspace(0,3,12);

y1=(x.^5)/10;
y2=x.*sin(x);
y3=cos(x)

subplot(3,1,1);
plot(x,y1,'b-');
xlabel('X-axis');
ylabel('Y-axis');
title('Graph of x^5/10');
grid on;

subplot(3,1,2);
plot(x,y2,'r--');
xlabel('X-axis');
ylabel('Y-axis');
title('Graph of x*sin(x)');
grid on;

subplot(3,1,3);
plot(x,y3,'g:');
xlabel('X-axis');
ylabel('Y-axis');
title('Graph of cos(x)');
grid on;
