function D = Get_Distances_Among_LGHS(P_LGHS)
% Get_Distances_Among_LGHS Computes pairwise distances between lighthouses.
%
% Input:
%   P_LGHS : Matrix of lighthouse positions [n_lighthouses x dimensions]
%
% Output:
%   D      : Vector containing all pairwise distances

    n_lighthouses = size(P_LGHS, 1);
    n_distances = n_lighthouses * (n_lighthouses - 1) / 2;

    D = zeros(1, n_distances);

    k = 1;
    for i = 1:n_lighthouses-1
        for j = i+1:n_lighthouses
            D(k) = norm(P_LGHS(i, :) - P_LGHS(j, :));
            k = k + 1;
        end
    end
end
