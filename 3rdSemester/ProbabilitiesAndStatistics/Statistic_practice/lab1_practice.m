# 1
A = [1 0 -2; 2 1 3; 0 1 0];
B = [2 1 1; 1 0 -1; 1 1 0];

C = A - B;
D = A * B;
E = A .* B;

function y = funct1 (x)
  y=2*x-2;
endfunction

disp("Matrix B:")
disp(B)

V=1:2:10;
disp(V)
V+2
V.^2

# 2

pkg load statistics

n = input('Trials: '); # natural nr
p = input('Probability: '); # 0<p<1

x = 0:1:n;
# successec in n trials

px = binopdf(x,n,p);
plot(x,px,'r+');
hold on

xx = 0:0.01:n;
cx = binocdf(xx,n,p);
plot(xx,cx,'b');



