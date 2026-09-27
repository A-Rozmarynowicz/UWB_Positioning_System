plot(P1_errors)

P_average_measured_distances = 0.5*(P1_average + P2_average);
Drone_actual_distances_average = 0.5*(P1_actual_distances + P2_actual_distances);

interpolation_p_params_U0 = polyfit(P_average_measured_distances(:, 4), Drone_actual_distances_average, 1);
error_compensation_line_U0 = polyval(interpolation_p_params_U0, Drone_actual_distances_average);

compens_U0_p1 = polyval(interpolation_p_params_U0, P1_average(:, 4));
plot(P1_actual_distances, P1_actual_distances-compens_U0_p1);
% hold on;
% plot(P1_actual_distances, P1_actual_distances)

