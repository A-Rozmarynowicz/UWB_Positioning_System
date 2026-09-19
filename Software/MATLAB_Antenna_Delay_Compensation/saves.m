u = [


]

assert(length(u) == 100);
folder = "PostCalib_Data_v2";

writematrix(u, fullfile(folder, "U1U2_v10_p1.csv"));
