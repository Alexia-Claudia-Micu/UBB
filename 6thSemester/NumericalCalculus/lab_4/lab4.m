function rez = lab4_ex1_backsubst(U,b)
    n=length(b);
    x=zeros(size(b));
    for(k=n:-1:1)
        x(k)=(b(k) - U(k,k+1:n) * x(k+1:n))/U(k,k);
    end
    rez = x;
end

function rez = lab4_ex1_forwardsubst(L, b)
    n = length(b);
    x = zeros(size(b));
    for k = 1:n
        x(k) = (b(k) - L(k, 1:k-1) * x(1:k-1)) / L(k, k);
    end
    rez = x;
end


function rez = gauss_partial_elimination(A, b)
    n = length(b);
    U = A;
    b_new = b;
    
    % Gaussian elimination with partial pivoting
    for k = 1:n-1
        % Partial pivoting: Find the row with the maximum absolute value in column k
        [~, max_index] = max(abs(U(k:n, k)));
        max_index = max_index + k - 1;
        
        if max_index ~= k
            % Swap rows in U
            U([k, max_index], :) = U([max_index, k], :);
            % Swap rows in b
            b_new([k, max_index]) = b_new([max_index, k]);
        end
        
        % Elimination process
        for i = k+1:n
            m = U(i, k) / U(k, k);
            U(i, k:n) = U(i, k:n) - m * U(k, k:n);
            b_new(i) = b_new(i) - m * b_new(k);
        end
    end
    
    % Back-substitution
    x = zeros(n, 1);
    for k = n:-1:1
        x(k) = (b_new(k) - U(k, k+1:n) * x(k+1:n)) / U(k, k);
    end
    
    rez = x;
end


A1=[1,1,1/2;0,1,1/2;0,0,1];
b1=[3,4,8]';

A2=[1,1,-1;3,-2,2;2,3,-2];
b2=[0,5,2]';

A3=[2,1,-1,-2;4,4,1,3;-6,-1,10,10;-2,1,8,4];
b3=[2,4,-5,1]';

rez = gauss_partial_elimination(A3,b3)

[L,U,P] = lu(A3)
y = lab4_ex1_forwardsubst(L,P*b3)
x = lab4_ex1_backsubst(U,y)

[Q,R] = qr(A3);
x = lab4_ex1_backsubst(R,Q'*b3)