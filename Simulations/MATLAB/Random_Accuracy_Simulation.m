function [accuracy, lghs_positions_ground_truth, estimated_lghs_positions, tag_position_ground_truth, estimated_tag_position] = ...
Random_Accuracy_Simulation(n_lighthouses, dimensions, distance_accuracy, max_distance, minimal_axis_offset, noise_func, lghs_estimator, tag_estimator, lghs_position_generator, tag_position_generator)
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

    tag_position_ground_truth = tag_position_generator(dimensions, max_distance, true);
    lghs_positions_ground_truth = lghs_position_generator(n_lighthouses, dimensions, max_distance, minimal_axis_offset);
    
    distances_among_LGHS = Get_Distances_Among_LGHS(lghs_positions_ground_truth);
    distances_among_LGHS = noise_func(distances_among_LGHS, distance_accuracy);

    [estimated_lghs_positions, LGHS_estimated_dFit, LGHS_residuals, LGHS_estimation_rmse] = lghs_estimator(distances_among_LGHS);

    tag_distances = Get_Distances_Tag_To_LGHS(tag_position_ground_truth, estimated_lghs_positions);
    tag_distances = noise_func(tag_distances, distance_accuracy);

    [estimated_tag_position, tag_dFit, tag_residuals, tag_rmse] = tag_estimator(estimated_lghs_positions, tag_distances); 
    
    accuracy = norm(estimated_tag_position - tag_position_ground_truth);
end