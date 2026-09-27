P_average_measured_distances = mean(0.5*(P1_average + P2_average), 2);
Drone_actual_distances_average = 0.5*(P1_actual_distances + P2_actual_distances);

interpolation_p_params_drone = polyfit(P_average_measured_distances(1:8), Drone_actual_distances_average(1:8), 1);
error_compensation_line = polyval(interpolation_p_params_drone, Drone_actual_distances_average);

figure;
compens_p1 = polyval(interpolation_p_params_drone, P1_average);
plot(P1_actual_distances, P1_actual_distances-compens_p1);

figure;
compens_p2 = polyval(interpolation_p_params_drone, P2_average);
plot(P2_actual_distances, P2_actual_distances-compens_p2);

display(interpolation_p_params_drone);