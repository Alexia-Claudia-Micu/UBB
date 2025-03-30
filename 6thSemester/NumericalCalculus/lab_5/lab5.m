function [x, history] = jacobi_method_verbose(A, b, x0, tol, max_iter)
    D = diag(diag(A));
    R = A - D;
    x = x0;
    history = zeros(max_iter+1, length(x)+2); 
    prev_error = NaN;

    for k = 1:max_iter
        x_new = D \ (b - R * x);
        err = norm(x_new - x, inf);
        ratio = NaN;
        if k > 1 && ~isnan(prev_error)
            ratio = err / prev_error;
        end
        prev_error = err;

        history(k+1, :) = [x_new', err, ratio];
        if err < tol
            history = history(1:k+1, :);
            break;
        end
        x = x_new;
    end
end


function [x, history] = gauss_seidel_verbose(A, b, x0, tol, max_iter)
    n = length(b);
    x = x0;
    history = zeros(max_iter+1, n+2); % store x1, x2, x3, error, ratio
    prev_error = NaN;

    for k = 1:max_iter
        x_old = x;
        for i = 1:n
            sum1 = A(i,1:i-1) * x(1:i-1);
            sum2 = A(i,i+1:n) * x_old(i+1:n);
            x(i) = (b(i) - sum1 - sum2) / A(i,i);
        end
        err = norm(x - x_old, inf);
        ratio = NaN;
        if k > 1 && ~isnan(prev_error)
            ratio = err / prev_error;
        end
        prev_error = err;

        history(k+1, :) = [x', err, ratio];
        if err < tol
            history = history(1:k+1, :);
            break;
        end
    end
end


function [A, B] = excercise1Lab5(n)
    A = 5*eye(n) - diag(ones(n-1,1),1) - diag(ones(n-1,1),-1);
    b = 3*ones(n,1) + triu(ones(n,1)) + tril(ones(n,1), 1-n);
end

A = [9 1 1; 2 10 3; 3 4 11];
b = [10; 19; 0];          
x0 = zeros(3,1);        
tol = 1e-6;
max_iter = 100;

% Run both verbose versions
[x_jacobi, hist_jacobi] = jacobi_method_verbose(A, b, x0, tol, max_iter);
[x_gs, hist_gs] = gauss_seidel_verbose(A, b, x0, tol, max_iter);

% Extract error from history
err_jacobi = hist_jacobi(:, end-1);
err_gs = hist_gs(:, end-1);

fprintf('Jacobi converged in %d iterations.\n', size(hist_jacobi, 1)-1);
fprintf('Gauss-Seidel converged in %d iterations.\n', size(hist_gs, 1)-1);

fprintf('Jacobi solution:       [%f, %f, %f]\n', x_jacobi);
fprintf('Gauss-Seidel solution: [%f, %f, %f]\n', x_gs);

figure;
semilogy(0:length(err_jacobi)-1, err_jacobi, '-o', 'DisplayName', 'Jacobi');
hold on;
semilogy(0:length(err_gs)-1, err_gs, '-x', 'DisplayName', 'Gauss-Seidel');
xlabel('Iteration');
ylabel('Error (log scale)');
title('Convergence of Jacobi vs Gauss-Seidel');
legend show;
grid on;

function [A,b] = tridiagmatrix2(n)
    A = 5*eye(n) - diag(ones(n-1,1),1) - diag(ones(n-1,1),-1) - diag(ones(n-3,1),3) - diag(ones(n-3,1),-3);
    b=ones(n,1) +triu(ones(n,1)) + tril(ones(n,1),1-n)+triu(ones(n,1),-2)+tril(ones(n,1),3-n);
end

function [x, nit] = sor_method(A, b, omega, x0, tol, max_iter)
    n = length(b);
    x = x0;
    nit = 0;
    for k = 1:max_iter
        x_old = x;
        for i = 1:n
            sum1 = A(i,1:i-1) * x(1:i-1);
            sum2 = A(i,i+1:n) * x_old(i+1:n);
            x(i) = (1 - omega) * x_old(i) + omega * (b(i) - sum1 - sum2) / A(i,i);
        end
        nit = nit + 1;
        if norm(x - x_old, inf) < tol
            break;
        end
    end
end

n = 1000;
tol = 1e-5;
max_iter = 1000;
[x0, omega] = deal(zeros(n,1), 1.2);  % Choose a good ω (e.g., 1.2 ~ 1.5)

[A, b] = tridiagmatrix2(n);

% Run all methods
[~, hist_jacobi] = jacobi_method_verbose(A, b, x0, tol, max_iter);
[~, hist_gs] = gauss_seidel_verbose(A, b, x0, tol, max_iter);
[x_sor, nit_sor] = sor_method(A, b, omega, x0, tol, max_iter);

% Report iterations
fprintf('Jacobi:       %d iterations\n', size(hist_jacobi,1)-1);
fprintf('Gauss-Seidel: %d iterations\n', size(hist_gs,1)-1);
fprintf('SOR:          %d iterations (ω = %.2f)\n', nit_sor, omega);
