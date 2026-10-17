function P_LGHS = Generate_Lighthouses_Positions(n_lighthouses, dimensions, max_distance, minimal_axis_offset)
% Generate_Lighthouses_Positions Generates random lighthouse positions.
%
% Inputs:
%   n_lighthouses       : Number of lighthouses
%   dimensions          : Number of dimensions (2 or 3)
%   max_distance        : Maximum absolute coordinate value
%   minimal_axis_offset : Minimum coordinate offset
%
% Output:
%   P_LGHS              : Matrix of positions [n_lighthouses x dimensions]

    % Validate inputs
    if n_lighthouses < 1 || n_lighthouses ~= floor(n_lighthouses)
        error('n_lighthouses must be a positive integer.');
    end

    if ~ismember(dimensions, [2, 3])
        error('dimensions must be either 2 or 3.');
    end

    if minimal_axis_offset < 0 || max_distance < minimal_axis_offset
        error('Require 0 <= minimal_axis_offset <= max_distance.');
    end


    P_LGHS = zeros(n_lighthouses, dimensions);

    for i = 1:min(n_lighthouses-1, dimensions)
        P_LGHS(i+1, 1:i) = ...
            minimal_axis_offset + ...
            rand(1, i) * (max_distance - minimal_axis_offset);

        % Randomly choose positive or negative coordinates
        signs = 2 * (rand(1, i) >= 0.5) - 1;
        P_LGHS(i+1, 1:i) = P_LGHS(i+1, 1:i) .* signs;
    end

    first_remaining = dimensions + 2;

    if n_lighthouses >= first_remaining
        P_LGHS(first_remaining:end, :) = ...
            (2 * rand(n_lighthouses-first_remaining+1, dimensions) - 1) ...
            * max_distance;
    end


    for i=1:min(dimensions, 3)
        P_LGHS(:, i) = P_LGHS(:, i)*sign(P_LGHS(i+1, i));
    end
end
