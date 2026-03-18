function accuracy = Random_Accuracy_Simulation(n_lighthouses, dimensions, distance_accuracy, max_distance, minimal_axis_offset)
% Random_Accuracy_Simulation  Simulates the positioning process with the lighthouses placed in random positions.
%   Inputs:
%       n_lighthouses : number of lighthouses to simulate
%       dimensions : number of dimensions: 3 for 3D, 2 for 2D
%       distance_accuracy : expected accuracy of a single distance
%           lighthouse-tag measurement
%       max_distance : max distance of a lighthouse from the origin
%       minimal_axis_offset : minimal distance between lighthouses in the
%           direction orthogonal to the line, plane or space created by
%           previous lighthouses
%       
%    Outputs:
%       accuracy: accuracy achieved in this simulation
%

    tag_position = rand(1, dimensions)*max_distance - max_distance/2;
    lighthouses_positions = zeros(n_lighthouses, dimensions);
    
    for i=1:dimensions
        lighthouses_positions(i+1, 1:i) = rand(1, i)*max_distance - max_distance/2;
        if (lighthouses_positions(i+1, i))^2 < minimal_axis_offset
            lighthouses_positions(i+1, i) = sign(lighthouses_positions(i+1, i)) * minimal_axis_offset;
        end
    end
    
    if n_lighthouses > 4
        lighthouses_positions(5:n_lighthouses, :) = rand(n_lighthouses-4, 3)*max_distance - max_distance/2;
    end
    
    noise_vec = -distance_accuracy/2 + rand(n_lighthouses, 1)*distance_accuracy;
    distances = sqrt(sum( (ones(n_lighthouses,1) * tag_position - lighthouses_positions).^2, 2)) + noise_vec;
    
    P = Solver(lighthouses_positions, distances);
    
    accuracy = norm(P - tag_position);
end