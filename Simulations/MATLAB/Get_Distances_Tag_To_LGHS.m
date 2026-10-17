function D = Get_Distances_Tag_To_LGHS(P_TAG, P_LGHS)
% Get_Distances_Tag_To_LGHS Computes distances from a tag to all lighthouses.
%
% Inputs:
%   P_TAG  : Tag position [1 x dimensions]
%   P_LGHS : Lighthouse positions [n_lighthouses x dimensions]
%
% Output:
%   D      : Distances from the tag to each lighthouse [1 x n_lighthouses]

    D = vecnorm(P_LGHS - P_TAG, 2, 2).';
end
