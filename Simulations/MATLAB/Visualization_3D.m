n_lighthouses = 5;
dimensions = 3;

distance_accuracy = 0.05; % Accuracy of a single distance measurement
minimal_axis_offset = 0.5; % Minimal distance of a lighthouse from other lighthouses
max_distance = 3.0; % Max distance of a lighthouse from the origin


[accuracy, lghs_positions_ground_truth, estimated_lghs_positions, tag_position_ground_truth, estimated_tag_position] = ...
Random_Accuracy_Simulation(n_lighthouses, dimensions, distance_accuracy, max_distance, minimal_axis_offset, @Apply_Uniform_Measurement_Noise, @Estimate_LGHS_Positions_lsqnonlin, @Estimate_Tag_Position_Least_Squares, @Generate_Fixed_Lighthouses_Positions, @Generate_Random_Tag_Position);

fprintf("Accuracy = %0.3f\n", accuracy);

sz = size(lghs_positions_ground_truth);
N = sz(1);

R_vec = Get_Distances_Among_LGHS(lghs_positions_ground_truth);
R_vec = Apply_Uniform_Measurement_Noise(R_vec, distance_accuracy);

side_num = 60;

figure;
scatter3(estimated_tag_position(1), estimated_tag_position(2),  estimated_tag_position(3), "red", "v","LineWidth", 3.0, "MarkerEdgeAlpha", 0.4);
hold on;
scatter3(tag_position_ground_truth(1), tag_position_ground_truth(2), tag_position_ground_truth(3), "green","*", "LineWidth", 3.0)
scatter3(lghs_positions_ground_truth(:, 1), lghs_positions_ground_truth(:, 2), lghs_positions_ground_truth(:, 3), "blue", ".");

for i=1:N
    [x, y, z] = sphere();
    x = x*R_vec(i) + lghs_positions_ground_truth(i, 1);
    y = y*R_vec(i) + lghs_positions_ground_truth(i, 2);
    z = z*R_vec(i) + lghs_positions_ground_truth(i, 3);
    surf(x, y, z, "FaceAlpha", 0.1, "EdgeColor", "none", "FaceColor", "yellow");
end

legend(["Calculated position", "Ground truth position", "Lighthouses", "Distances to lighthouses"])

title('3D visualization');
subtitle(sprintf("Distance measurement accuracy: %0.2fm \n Position measurement accuracy: %0.2fm", distance_accuracy, accuracy));
xlabel('x');
ylabel('y');
zlabel("z");
axis equal; % Ensures the circle looks round, not elliptical
