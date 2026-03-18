clear;
number_of_iterations = 1000;

n_lighthouses = 4;
dimensions = 3;

distance_accuracy = 0.1; % Accuracy of a single distance measurement
minimal_axis_offset = 0.5; % Minimal distance of a lighthouse from other lighthouses
max_distance = 5.0; % Max distance of a lighthouse from the origin

accuracies = zeros(number_of_iterations, 1);

for k=1:number_of_iterations
    accuracies(k) = Random_Accuracy_Simulation(n_lighthouses, dimensions, distance_accuracy, max_distance, minimal_axis_offset);
end

worst_accuracy = max(accuracies);
average_accuracy = mean(accuracies);
std_accuracy_deviation = std(accuracies);
mode_accuracy = mode(accuracies);

edges = [0, 0:distance_accuracy:20*distance_accuracy, max(worst_accuracy, 20*distance_accuracy)];
h = histogram(accuracies, edges);
xlim([-distance_accuracy, max(min(20, worst_accuracy), 1.0)]);

title("Histogram of simulated accuracies of position measurements");

info_str = sprintf("Number of lighthouses: %d\n Dimensions: %d\n Number of experiments: %d", n_lighthouses, dimensions, number_of_iterations);

xl = xlim;
yl = ylim;
text(0.98*xl(2), 0.98*yl(2), info_str, ...
    'HorizontalAlignment', 'right', ...
    'VerticalAlignment', 'top');

xlabel("Accuracy");
ylabel("Number of occurrences");