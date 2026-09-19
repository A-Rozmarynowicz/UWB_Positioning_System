u = [



]

assert(length(u) == 100);
folder = "PostCalib_Data_v2";

writematrix(u, fullfile(folder, "U2U3_v5_p2.csv"));
