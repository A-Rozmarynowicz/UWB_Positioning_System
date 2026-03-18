clear;
number_of_iterations = 1000;
most_lighthouses = 20;

D = 3;
least_lighthouses = D+1;

N_vec = linspace(least_lighthouses, most_lighthouses, most_lighthouses-D);
N = size(N_vec);
N = N(2);
distance_accuracy = 0.1;
minimal_axis_offset = 0.5;
max_distance = 5.0;

worst_accuracies = zeros(N, 1);
average_accuracies = zeros(N, 1);
std_deviations = zeros(N, 1);
accuracies = zeros(number_of_iterations, 1);

for n=1:N
    for k=1:number_of_iterations
        accuracies(k) = Random_Accuracy_Simulation(N_vec(n), D, distance_accuracy, max_distance, minimal_axis_offset);
    end
    worst_accuracies(n) = max(accuracies);
    average_accuracies(n) = sum(accuracies)/number_of_iterations;
    std_deviations(n) = std(accuracies);
end

figure;
subplot(2, 1, 2);
scatter(N_vec, worst_accuracies, "o", "filled");
xticks(N_vec);
xlim([least_lighthouses-0.5, most_lighthouses+0.5]);
subtitle("Worst accuracy");

info_str = sprintf("Distance measurement accuracy: %0.2fm", distance_accuracy);

xl = xlim;
yl = ylim;
text(0.98*xl(2), 0.9*yl(2), info_str, ...
    'HorizontalAlignment', 'right', ...
    'VerticalAlignment', 'top');

ylabel("Accuracy [m]");


subplot(2, 1, 1);
scatter(N_vec, average_accuracies, 'o', "filled");
title("Accuracy vs. number of lighthouses")
hold on;
errorbar(N_vec, std_deviations, average_accuracies, 'LineStyle', 'none', 'Color', 'k', 'CapSize', 10);

xticks(N_vec);
xlim([least_lighthouses-0.5, most_lighthouses+0.5]);
subtitle("Average accuracy");
legend("Average accuracy", "Standard deviation")

ylabel("Accuracy [m]");
xlabel("Number of lighthouses")