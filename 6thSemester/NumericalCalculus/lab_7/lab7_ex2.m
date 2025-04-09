function aitken_interpolation_corrected()
    % Define nodes
    x_nodes = linspace(-4, 4, 9);
    y_nodes = 2.^x_nodes;
    
    % Value to approximate
    x_target = 0.5; % <-- NOT sqrt(2), but 0.5
    
    % Perform Aitken interpolation
    approx_value = aitken_algorithm(x_nodes, y_nodes, x_target);
    
    % Output result
    fprintf('Approximation of 2^{0.5} ≈ %.6f\n', approx_value);
    fprintf('Actual value 2^{0.5} ≈ %.6f\n', 2^0.5);
    fprintf('Absolute error ≈ %.6e\n', abs(approx_value - 2^0.5));
end

function P = aitken_algorithm(x, y, x_target)
    % Aitken’s recursive interpolation
    n = length(x);
    P = y;
    
    for j = 1:n-1
        for i = 1:n-j
            P(i) = ((x_target - x(i+j)) * P(i) + (x(i) - x_target) * P(i+1)) / (x(i) - x(i+j));
        end
    end
    
    P = P(1);
end
