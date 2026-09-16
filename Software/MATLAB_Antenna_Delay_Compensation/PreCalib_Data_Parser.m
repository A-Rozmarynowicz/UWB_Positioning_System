DWM_to_wall_offset = 0.025;
number_of_distances_measured = 10;
number_of_experiments = 6;

U0_actual_distances = [4.557, 4.035, 3.519, 3.014, 2.508, 2.001, 1.499, 1.000, 0.497, 0.100] + 2*DWM_to_wall_offset;
U1_actual_distances = [4.556, 4.036, 3.520, 3.015, 2.508, 2.001, 1.500, 1.000, 0.498, 0.100] + 2*DWM_to_wall_offset;
U2_actual_distances = [4.555, 4.037, 3.519, 3.015, 2.507, 2.001, 1.501, 1.000, 0.493, 0.100] + 2*DWM_to_wall_offset;

U0U1 = [5.877, 5.380, 4.775, 4.271, 3.738, 3.214, 2.689, 2.190, 1.656, 1.213];
U0U2 = [5.628, 5.268, 4.647, 4.173, 3.628, 3.113, 2.591, 2.090, 1.539, 1.120];
U0U3 = [5.886, 5.429, 4.787, 4.320, 3.758, 3.242, 2.709, 2.197, 1.675, 1.230];
U1U2 = [5.869, 5.255, 4.658, 4.127, 3.612, 3.088, 2.551, 2.060, 1.518, 1.087];
U1U3 = [6.066, 5.428, 4.853, 4.308, 3.782, 3.260, 2.724, 2.205, 1.666, 1.221];
U2U3 = [5.761, 5.284, 4.686, 4.175, 3.626, 3.101, 2.569, 2.047, 1.512, 1.092];

U_distances = [U0U1; U0U2; U0U3; U1U2; U1U3; U2U3]';

actual_distances = [U0_actual_distances; U0_actual_distances; U0_actual_distances; ...
                    U1_actual_distances; U1_actual_distances; U2_actual_distances]';


E = actual_distances - U_distances;
%% Plots

plot(E);
grid on;
legend('U0U1','U0U2','U0U3','U1U2','U1U3','U2U3');
xlabel('Measurement');
ylabel('Error');

%% Saves
colNames = {'U0U1','U0U2','U0U3','U1U2','U1U3','U2U3'};
T_U = array2table(U_distances, 'VariableNames', colNames);
writetable(T_U, 'PreCalib_Data/U_distances.csv', 'WriteRowNames', true);

A_U = array2table(actual_distances, 'VariableNames', colNames);
writetable(A_U, 'PreCalib_Data/actual_distances.csv', 'WriteRowNames', true);
