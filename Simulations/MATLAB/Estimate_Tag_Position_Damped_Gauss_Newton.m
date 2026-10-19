function [P, dFit, residuals, rmse] = ...
    Estimate_Tag_Position_Damped_Gauss_Newton(P_vec, R_vec)
% Estimate tag position using damped Gauss-Newton
% (Levenberg-Marquardt algorithm).
%
% Inputs:
%   P_vec      N-by-D matrix of lighthouse positions
%   R_vec      N-element vector of measured distances
%
% Outputs:
%   P          1-by-D estimated tag position
%   dFit       N-by-1 vector of fitted distances
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

    % Initial estimate from linear least squares
    P = Estimate_Tag_Position_Least_Squares(P_vec, R_vec);
    P = P(:).';

    % Algorithm parameters
    maxIterations = 100;
    tolerance = 1e-8;

    lambda = 1e-3;
    lambdaFactor = 10;
    maxLambda = 1e12;

    % Initial residuals and cost
    delta = P - P_vec;
    dFit = sqrt(sum(delta.^2, 2));

    if any(dFit < eps)
        error('Initial estimate coincides with a lighthouse.');
    end

    residuals = dFit - R_vec;
    cost = 0.5 * sum(residuals.^2);

    for iter = 1:maxIterations

        % Compute Jacobian
        delta = P - P_vec;
        dFit = sqrt(sum(delta.^2, 2));

        if any(dFit < eps)
            error('Tag estimate coincides with a lighthouse.');
        end

        residuals = dFit - R_vec;
        J = delta ./ dFit;

        % Levenberg-Marquardt system
        H = J.' * J;
        g = J.' * residuals;

        % Scale damping according to the diagonal of H
        damping = max(diag(H), 1e-12);
        H_damped = H + lambda * diag(damping);

        % Solve for the proposed update
        dp = -H_damped \ g;

        if any(~isfinite(dp))
            lambda = lambda * lambdaFactor;

            if lambda > maxLambda
                break;
            end

            continue;
        end

        % Evaluate the candidate position
        P_candidate = P + dp.';

        delta_candidate = P_candidate - P_vec;
        dFit_candidate = sqrt(sum(delta_candidate.^2, 2));

        if any(~isfinite(dFit_candidate)) || ...
                any(dFit_candidate < eps)
            candidateCost = Inf;
        else
            residuals_candidate = dFit_candidate - R_vec;
            candidateCost = 0.5 * sum(residuals_candidate.^2);
        end

        % Accept only steps that reduce the cost
        if candidateCost < cost
            improvement = cost - candidateCost;

            P = P_candidate;
            cost = candidateCost;

            % Reduce damping after a successful step
            lambda = max(lambda / lambdaFactor, 1e-12);

            % Convergence checks
            if norm(dp) < tolerance * (1 + norm(P)) || ...
                    improvement < tolerance * (1 + cost)
                break;
            end
        else
            % Reject the step and increase damping
            lambda = lambda * lambdaFactor;

            if lambda > maxLambda
                break;
            end
        end
    end

    % Final fitted distances and residuals
    delta = P - P_vec;
    dFit = sqrt(sum(delta.^2, 2));

    residuals = dFit - R_vec;
    rmse = sqrt(mean(residuals.^2));

end