U_expected = U_distances_bias + polyval(interpolation_p_params, actual_distances);

plot(actual_distances , actual_distances - U_expected);
grid("on")
legend('U0U1','U0U2','U0U3','U1U2','U1U3','U2U3');