function [P, dFit, residuals, rmse] = Estimate_LGHS_Positions_Simple(d)
% INPUT:
%   d       6-element vector of measured distances, ordered as:
%           [d01; d02; d03; d12; d13; d23]
%
% OUTPUT:
%   P         4x3 matrix of estimated coordinates
%   dFit      6x1 vector of fitted distances
%   residuals 6x1 vector (fitted - measured)
%   rmse      Root mean square distance residual

    validateattributes(d, {'numeric'}, ...
        {'real','finite','vector','numel',6,'nonnegative'});

    d = double(d(:));

    if any(d <= 0)
        error('All six measured distances must be positive.');
    end

    P = zeros([4, 3]);

    P(2, 1) = d(1);
    
    P(3, 1) = (d(4)^2 - d(2)^2)/(-2.0*P(2, 1)) + P(2, 1)/2.0;
    y20_sugg = d(2)^2 + d(4)^2 - 2*P(3, 1)^2 + 2*P(3, 1)*P(2, 1) - P(2, 1)^2;
    y20_sugg = abs(y20_sugg);
    P(3, 2) = sqrt(y20_sugg/2.0);

    R0 = d(3);
    R1 = d(5);
    R2 = d(6);

    x1 = P(2, 1);
    x2 = P(3, 1);
    y2 = P(3, 2);

    x3 = (R1^2 - R0^2 - x1^2)/(-2.0*x1);
    y3 = (R2^2 - R0^2 - y2^2 - x2^2 + 2*x2*x3)/(-2.0*y2);
    z_sugg = R0^2 + R1^2 + R2^2 + 2*x1*x3 - x1^2 + 2*x2*x3 - x2^2 + 2*y2*y3 - y2^2 - 3*x3^2 - 3*y3^2;
    z_sugg = abs(z_sugg);
    z3 = sqrt(z_sugg/3.0);

    P(4, 1) = x3;
    P(4, 2) = y3;
    P(4, 3) = z3;

    %-----------------------------------------
    
    pairs = [1 2;
         1 3;
         1 4;
         2 3;
         2 4;
         3 4];

    dFit = zeros(6);

    for k = 1:6
        i = pairs(k,1);
        j = pairs(k,2);
        dFit(k) = norm(P(i,:) - P(j,:));
    end

    residuals = dFit - d;
    rmse = sqrt(mean(residuals.^2));
    
 end