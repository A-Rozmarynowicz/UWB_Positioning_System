est_idx = 6; % Na odległości 2m, czyli indeks 6
c = 299792458.0;
tau = 15.65e-12;

A_binary = [
    1, 1, 0, 0;
    1, 0, 1, 0;
    1, 0, 0, 1;
    0, 1, 1, 0;
    0, 1, 0, 1;
    0, 0, 1, 1;
];

E_time = (actual_distances(est_idx, :) - U_distances(est_idx, :))*(-1/c);

delta_t = A_binary\E_time';

delta_t_ticks = round(delta_t/tau);

display(delta_t_ticks);

