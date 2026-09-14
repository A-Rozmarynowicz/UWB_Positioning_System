Data_U0U1_expected = [Data_U0U1_bias(:, 1), Data_U0U1_bias(:, 2) + polyval(interpolation_p_params, U0_actual_distances)'];
Data_U0U2_expected = [Data_U0U2_bias(:, 1), Data_U0U2_bias(:, 2) + polyval(interpolation_p_params, U0_actual_distances)'];
Data_U0U3_expected = [Data_U0U3_bias(:, 1), Data_U0U3_bias(:, 2) + polyval(interpolation_p_params, U0_actual_distances)'];
Data_U1U2_expected = [Data_U1U2_bias(:, 1), Data_U1U2_bias(:, 2) + polyval(interpolation_p_params, U1_actual_distances)'];
Data_U1U3_expected = [Data_U1U3_bias(:, 1), Data_U1U3_bias(:, 2) + polyval(interpolation_p_params, U1_actual_distances)'];
Data_U2U3_expected = [Data_U2U3_bias(:, 1), Data_U2U3_bias(:, 2) + polyval(interpolation_p_params, U2_actual_distances)'];


