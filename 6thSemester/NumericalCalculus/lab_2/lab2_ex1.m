syms x
f=exp(x);
Texp1=taylor(f,x,0,'Order',2)
Texp2=taylor(f,x,0,'Order',3)
Texp3=taylor(f,x,0,'Order',4)
Texp4=taylor(f,x,0,'Order',5)

fplot([f Texp1 Texp2 Texp3 Texp4])
xlim([-3 3])
legend('exp(x', 'T1', 'T2', 'T3', 'T4', 'Location', 'Best')
title('Problem 1. a), Taylor polynomials for exp(x)');