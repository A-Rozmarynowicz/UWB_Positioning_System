%% Data loading

rootDir = 'DronPostcalib_Data/';

P1 = readtable(fullfile(rootDir, 'Measured_Distances/P1_Measured_Distances.csv'));
P2 = readtable(fullfile(rootDir, 'Measured_Distances/P2_Measured_Distances.csv'));

P1_measured_distances = table2array(P1);
P2_measured_distances = table2array(P2);

columns_ranges = containers.Map( ...
    {'U0', 'U1', 'U2', 'U3'}, ...
    {1:10, 11:20, 21:30, 31:40});

columns_singular = dictionary( ...
    ["U0", "U1", "U2", "U3"], ...
    [1, 2, 3, 4]);

P1_actual_distances = readmatrix(fullfile(rootDir, "Actual_Distances/P1_Actual_Distances"));
P2_actual_distances = readmatrix(fullfile(rootDir, "Actual_Distances/P2_Actual_Distances"));

P1_actual_distances_average = mean(P1_actual_distances, 2);
P2_actual_distances_average = mean(P2_actual_distances, 2);

columns_actual = dictionary( ...
    ["D0"], ...
    [1]);

%% Statistics

P1_average = reshape(mean(P1_measured_distances, 1), 10, 4);
P2_average = reshape(mean(P2_measured_distances, 1), 10, 4);

P1_std = reshape(std(P1_measured_distances, 0, 1), 10, 4);
P2_std = reshape(std(P2_measured_distances, 0, 1), 10, 4);

P1_errors = P1_actual_distances - P1_average;
P2_errors = P2_actual_distances - P2_average;

%% Errorbars
figure;
experiment = "U0";
errorbar(P2_actual_distances_average, P2_errors(:, columns_singular(experiment)), P1_std(:, columns_singular(experiment)), ...
    'o-', 'LineWidth', 1.5, 'CapSize', 8, "LineStyle", "none");

%% Plot
figure;
plot(P1_actual_distances_average, 0.5*(P1_errors+P2_errors), 'o-', 'LineWidth', 1.5);
legend(["U0", "U1", "U2", "U3"])
% hold on;
% scatter(P1_actual_distances_average, P2_std);

