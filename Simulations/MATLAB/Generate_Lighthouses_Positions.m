function P_LGHS = Generate_Lighthouses_Positions(n_lighthouses, dimensions, max_distance, minimal_axis_offset)
% Generate_Lighthouses_Positions  Generates random positions for lighthouses.
%   Inputs:
%       n_lighthouses : number of lighthouses to generate
%       dimensions : number of dimensions: 3 for 3D, 2 for 2D
%       max_distance : max distance of a lighthouse from the origin
%       minimal_axis_offset : minimal distance between lighthouses in the
%           direction orthogonal to the line, plane or space created by
%           previous lighthouses
%       
%    Outputs:
%       P_LGHS: matrix of lighthouses positions" [n_lighthoues, dimensions]
%

    P_LGHS = zeros(n_lighthouses, dimensions);
    
    for i=1:dimensions
        P_LGHS(i+1, 1:i) = rand(1, i)*(2*max_distance) - max_distance;
        if (P_LGHS(i+1, i))^2 < minimal_axis_offset
            P_LGHS(i+1, i) = sign(P_LGHS(i+1, i)) * minimal_axis_offset;
        end
    end
    
    if n_lighthouses > 4
        P_LGHS(5:n_lighthouses, :) = rand(n_lighthouses-4, 3)*(2*max_distance) - max_distance;
    end
      
end