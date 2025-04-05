% Known data (Years and corresponding populations in millions)
x = [1980 1990 2000 2010 2020];
f = [4451 5287 6090 6970 7821];

% Actual known values for comparison
actual_values = [6474, 7405]; % for 2005 and 2015
x_eval = [2005, 2015];

% Compute barycentric weights using the formula:
% w_i = 1 / prod_{j ≠ i} (x_i - x_j)
n = length(x);
w = zeros(1, n);
for i = 1:n
    others = [1:i-1, i+1:n];
    w(i) = 1 / prod(x(i) - x(others));
end

% Barycentric interpolation function using weights
barycentric_interp = @(x0) arrayfun(@(xv) ...
    sum((w ./ (xv - x)) .* f) / sum(w ./ (xv - x)), x0);

% Evaluate at 2005 and 2015
approx_values = barycentric_interp(x_eval);

% Compute relative errors
rel_errors = abs(actual_values - approx_values) ./ actual_values;

% Display results
fprintf('\n--- Barycentric Interpolation (with explicit weights) ---\n');
fprintf('Year\tApprox\t\tActual\t\tRel. Error (%%)\n');
for i = 1:length(x_eval)
    fprintf('%d\t%.2f\t\t%.0f\t\t%.4f%%\n', ...
        x_eval(i), approx_values(i), actual_values(i), rel_errors(i)*100);
end
