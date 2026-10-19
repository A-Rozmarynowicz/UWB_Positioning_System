function [P, dFit, residuals, rmse] = ...
    Estimate_Tag_Position_Gauss_Newton(P_vec, R_vec)
% Estimate tag position using the Gauss-Newton algorithm.
% Initial position is obtained from the linear least-squares method.
%
% Inputs:
%   P_vec      N-by-D matrix of lighthouse positions
%   R_vec      N-element vector of measured distances
%
% Outputs:
%   P          1-by-D estimated tag position
%   dFit       N-by-1 fitted distances
%   residuals  N-by-1 residuals (fitted - measured)
%   rmse       Root mean square distance residual

    % Validate inputs
    validateattributes(P_vec, {'numeric'}, ...
        {'real','finite','2d','nonempty'});
    validateattributes(R_vec, {'numeric'}, ...
        {'real','finite','vector','nonempty','positive'});

    P_vec = double(P_vec);
    R_vec = double(R_vec(:));

    [N, D] = size(P_vec);

    if numel(R_vec) ~= N
        error('R_vec must contain one distance per lighthouse.');
    end

    if N < D + 1
        error('At least D+1 lighthouses are required.');
    end

    % Initial estimate from the linear least-squares method
    P = Estimate_Tag_Position_Least_Squares(P_vec, R_vec);
    P = P(:).';

    % Gauss-Newton parameters
    maxIterations = 100;
    tolerance = 1e-8;

    for iter = 1:maxIterations

        % Predicted distances
        delta = P - P_vec;
        dFit = sqrt(sum(delta.^2, 2));

        % Avoid division by zero
        if any(dFit < eps)
            error('Tag estimate coincides with a lighthouse.');
        end

        % Residual vector
        residuals = dFit - R_vec;

        % Jacobian of distance residuals
        J = delta ./ dFit;

        % Gauss-Newton update:
        % Solve J * dp = -residuals in least-squares sense
        dp = -J \ residuals;

        % Update position
        P_new = P + dp.';

        % Convergence check
        if norm(dp) < tolerance * (1 + norm(P))
            P = P_new;
            break;
        end

        P = P_new;
    end

    % Recalculate final fitted distances and residuals
    delta = P - P_vec;
    dFit = sqrt(sum(delta.^2, 2));

    residuals = dFit - R_vec;
    rmse = sqrt(mean(residuals.^2));

end