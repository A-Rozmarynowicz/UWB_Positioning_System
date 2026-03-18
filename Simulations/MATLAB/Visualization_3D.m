P_star = [0, 1, 0];

P_vec = [
    [0, 0, 0]; ...
    [1, 0, 0]; ...
    [1, 1, 0]; ...
    [0, 1, 1];
    ]; % Lighthouses' positions

distance_accuracy = 0.1;

sz = size(P_vec);
N = sz(1);

Noise_vec = -distance_accuracy/2 + rand(N, 1)*distance_accuracy;
R_vec = sqrt(sum( (ones(N,1) * P_star - P_vec).^2, 2)) + Noise_vec;

P = Solver(P_vec, R_vec);

accuracy = norm(P - P_star);
disp(accuracy);
side_num = 60;

figure;
scatter3(P(1), P(2),  P(3), "red", "v","LineWidth", 3.0, "MarkerEdgeAlpha", 0.4);
hold on;
scatter3(P_star(1), P_star(2), P_star(3), "green","*", "LineWidth", 3.0)
scatter3(P_vec(:, 1), P_vec(:, 2), P_vec(:, 3), "blue", ".");

for i=1:N
    [x, y, z] = sphere();
    x = x*R_vec(i) + P_vec(i, 1);
    y = y*R_vec(i) + P_vec(i, 2);
    z = z*R_vec(i) + P_vec(i, 3);
    surf(x, y, z, "FaceAlpha", 0.1, "EdgeColor", "none", "FaceColor", "yellow");
end

legend(["Calculated position", "Ground truth position", "Lighthouses", "Distances to lighthouses"])

title('3D visualization');
subtitle(sprintf("Distance measurement accuracy: %0.2fm \n Position measurement accuracy: %0.2fm", distance_accuracy, accuracy));
xlabel('x');
ylabel('y');
zlabel("z");
axis equal; % Ensures the circle looks round, not elliptical
