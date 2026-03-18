P_star = [0, 1];

P_vec = [
    [0, 0]; ...
    [1, 0]; ...
    [1, 1]; ...
    ]; % Lighthouses' positions

distance_accuracy = 0.1;

sz = size(P_vec);
N = sz(1);

Noise_vec = -distance_accuracy/2 + rand(N, 1)*distance_accuracy;
R_vec = sqrt(sum( (ones(N,1) * P_star - P_vec).^2, 2)) + Noise_vec;

P = Solver(P_vec, R_vec);

accuracy = norm(P - P_star);

side_num = 60;
Circle_vec = zeros(2*N, side_num);

for i=1:N
    Circ = Circle(P_vec(i, :), R_vec(i), side_num);
    Circle_vec(2*i-1, :) = Circ(1, :);
    Circle_vec(2*i, :) = Circ(2, :);
end

figure;
scatter(P(1), P(2), "red", "v","LineWidth", 3.0, "MarkerEdgeAlpha", 0.4);
hold on;
scatter(P_star(1), P_star(2), "green","*", "LineWidth", 3.0)

for i=1:N
    C = polyshape(Circle_vec(2*i-1, :), Circle_vec(2*i, :));
    plot(C, "EdgeColor", "blue" ,"FaceColor", 'none');
end

scatter(P_vec(:, 1), P_vec(:, 2), "blue", "*");

legend(["Calculated position", "Ground truth position", "Distances to lighthouses"])

title('2D visualization');
subtitle(sprintf("Distance measurement accuracy: %0.2fm \n Position measurement accuracy: %0.2fm", ...
            distance_accuracy, accuracy));
xlabel('x');
ylabel('y');
axis equal;

function Circ = Circle(p, R, side_num)
    theta = linspace(0, 2*pi-0.01, side_num);
    x = p(1) + R * cos(theta);
    y = p(2) + R * sin(theta);
    Circ = [x; y];
end