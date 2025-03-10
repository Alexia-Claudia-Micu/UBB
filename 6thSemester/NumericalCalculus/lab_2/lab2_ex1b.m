Texp10 = taylor(exp(x), x, 0, 'Order', 11)
e = subs(Texp10, x, 1)
vpa(e, 7)
format long; exp(1) % compare
format short

%ex 2

syms x
f=sin(x);
Tsin3=taylor(f,x,0,'Order',4)
Tsin5=taylor(f,x,0,'Order',6)

fplot([f Tsin3 Tsin5])
xlim([-pi pi])
legend('sin x', 'T3', 'T5', 'Location', 'Best')
title('Problem 2.a), Taylor polynomials for sin x');
%notice that the errors get bigger towards the endpoints of the interval

%ex 2 b

Tsin9 = taylor(f,x,0,'Order', 10)
var1=subs(Tsin9,x,pi/5)
vpa(var1,5)
format long; sin(pi/5) % compare
format short

