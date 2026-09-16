%% Data loading

rootDir = 'PostCalib_Data/';

P1 = readtable(fullfile(rootDir, 'Measured_Distances/P1_Measured_Distances.csv'));
P2 = readtable(fullfile(rootDir, 'Measured_Distances/P2_Measured_Distances.csv'));
P3 = readtable(fullfile(rootDir, 'Measured_Distances/P3_Measured_Distances.csv'));

P1_measured_distances = table2array(P1);
P2_measured_distances = table2array(P2);
P3_measured_distances = table2array(P3);

columns_measured = dictionary( ...
    ["U0U1", "U0U2", "U0U3", "U1U2", "U1U3", "U2U3"], ...
    [1, 2, 3, 4, 5, 6]);

P1_actual_distances = readmatrix(fullfile(rootDir, "Actual_Distances/P1_Actual_Distances"));
P2_actual_distances = readmatrix(fullfile(rootDir, "Actual_Distances/P2_Actual_Distances"));
P3_actual_distances = readmatrix(fullfile(rootDir, "Actual_Distances/P3_Actual_Distances"));

columns_actual = dictionary( ...
    ["U0", "U1", "U2"], ...
    [1, 2, 3]);

%% Statistics

P1_Average = mean(P1_measured_distances, 1);
P2_Average = mean(P2_measured_distances, 1);
P3_Average = mean(P3_measured_distances, 1);

P1_Std = std(P1_measured_distances, 0, 1);
P2_Std = std(P2_measured_distances, 0, 1);
P3_Std = std(P3_measured_distances, 0, 1);

plot(P1_Average)