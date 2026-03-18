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
accuracies = zeros(number_of_iterations, 1);

for n=1:N
    for k=1:number_of_iterations
        accuracies(k) = Random_Accuracy_Simulation(N_vec(n), D, distance_accuracy, max_distance, minimal_axis_offset);
    end
    worst_accuracies(n) = max(accuracies);
    average_accuracies(n) = sum(accuracies)/number_of_iterations;
end

figure;
sgtitle("Dokładność w zależności od ilości latarni");
subplot(2, 1, 1);
stairs(N_vec, worst_accuracies, "LineWidth", 1.4);
xticks(N_vec);
subtitle("Najgorsza dokładność");

info_str = sprintf("Dokładność pomiaru odległości %0.2fm", distance_accuracy);

xl = xlim;
yl = ylim;
text(0.98*xl(2), 0.9*yl(2), info_str, ...
    'HorizontalAlignment', 'right', ...
    'VerticalAlignment', 'top');

ylabel("Dokładność [m]");

hold on;


subplot(2, 1, 2);
stairs(N_vec, average_accuracies, "LineWidth", 1.4);
xticks(N_vec);
subtitle("Średnia dokładność");

ylabel("Dokładność [m]");

xlabel("Liczba latarni")