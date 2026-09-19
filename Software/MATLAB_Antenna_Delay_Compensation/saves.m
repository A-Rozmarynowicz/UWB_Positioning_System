u = [
4.572,
4.053,
3.538,
3.029,
2.523,
2.019,
1.517,
1.014,
0.511,
0.100,


]

% assert(length(u) == 100);
folder = "PostCalib_Data_v2";

writematrix(u, fullfile(folder, "U2_distances.csv"));
