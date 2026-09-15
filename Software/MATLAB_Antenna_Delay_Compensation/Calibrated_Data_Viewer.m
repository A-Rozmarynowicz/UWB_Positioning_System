rootDir = 'PostCalib_Data/Measured_Distances/';

P1 = readtable(fullfile(rootDir, 'P1_Measured_Data.csv'));
P2 = readtable(fullfile(rootDir, 'P2_Measured_Data.csv'));
P3 = readtable(fullfile(rootDir, 'P3_Measured_Data.csv'));

P1_matrix = table2array(P1);
P2_matrix = table2array(P2);
P3_matrix = table2array(P3);

size(P1_matrix)