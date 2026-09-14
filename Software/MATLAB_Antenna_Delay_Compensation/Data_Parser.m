DWM_to_wall_offset = 0.025;
number_of_distances_measured = 10;

U0_offset_distances = [4.557, 4.035, 3.519, 3.014, 2.508, 2.001, 1.499, 1.000, 0.497, 0.100];
U0_actual_distances = U0_offset_distances + DWM_to_wall_offset*2;

U1_offset_distances = [4.556, 4.036, 3.520, 3.015, 2.508, 2.001, 1.500, 1.000, 0.498, 0.100];
U1_actual_distances = U1_offset_distances + DWM_to_wall_offset*2;

U2_offset_distances = [4.555, 4.037, 3.519, 3.015, 2.507, 2.001, 1.501, 1.000, 0.493, 0.100];
U2_actual_distances = U2_offset_distances + DWM_to_wall_offset*2;

scatter(linspace(0, number_of_distances_measured, number_of_distances_measured), U0_actual_distances, '*');
hold on
scatter(linspace(0, number_of_distances_measured, number_of_distances_measured), U1_actual_distances, '+');
scatter(linspace(0, number_of_distances_measured, number_of_distances_measured), U2_actual_distances);
hold off

% U0U1 = [
%     4.557, 5.877;
%     4.035, 5.380;
% 
% ];
% 
% scatter(U0U1(:, 1), U0U1(1, :))