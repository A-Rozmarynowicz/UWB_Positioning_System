d = [

4.571,
4.051,
3.535,
3.030,
2.521,
2.018,
1.517,
1.016,
0.509,
0.100,




]

% assert(length(d) == 100);
folder = "DronPrecalib_Data";
writematrix(d, fullfile(folder, "D0_Raw_Distances.csv"));
