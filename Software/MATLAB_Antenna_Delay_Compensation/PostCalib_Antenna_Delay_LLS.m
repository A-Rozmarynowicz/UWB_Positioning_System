est_idx = 6;
c = 299792458.0;
tau = 15.65e-12;

linear_params = [0.9493, 0.1058];

A_binary = [
    1, 1, 0, 0;
    1, 0, 1, 0;
    1, 0, 0, 1;
    0, 1, 1, 0;
    0, 1, 0, 1;
    0, 0, 1, 1;
];

E = 0.5*(P1_errors(est_idx, :) + P2_errors(est_idx, :))*(-1/c);
% E = (P1_errors(est_idx, :))*(-1/c);

delta_t_2 = (A_binary\E')*(linear_params(1));

delta_t_ticks_2 = round(delta_t_2/tau);

display(delta_t_ticks_2);

%% Expected results v2

P1_average_new = ((P1_average - linear_params(2))/(linear_params(1))) - (A_binary*delta_t_2*c)';
P1_average_new = polyval(linear_params, P1_average_new);
P1_errors_new = P1_actual_distances - P1_average_new;

P2_average_new = ((P2_average - linear_params(2))/(linear_params(1))) - (A_binary*delta_t_2*c)';
P2_average_new = polyval(linear_params, P2_average_new);
P2_errors_new = P2_actual_distances - P2_average_new;

figure;
plot(P1_actual_distances_average, P1_errors_new);
title("P1");
grid("on");

figure;
plot(P2_actual_distances_average, P2_errors_new);
title("P2");
grid("on");
