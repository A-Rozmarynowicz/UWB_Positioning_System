U_distances_bias = (U_distances - (A_binary*delta_t*c)');

E_bias = actual_distances - U_distances_bias;

E_bias_total = sum(E_bias, 2) / number_of_experiments;
actual_distances_avg = (U0_actual_distances + U1_actual_distances + U2_actual_distances)/3;

interpolation_p_params = polyfit(actual_distances_avg, E_bias_total, 1);
error_compensation_line = polyval(interpolation_p_params, actual_distances_avg);

plot(actual_distances, E_bias, '*')
hold on;
plot(actual_distances_avg, error_compensation_line)

quality = sum(abs(E_bias_total - error_compensation_line));

display(interpolation_p_params);