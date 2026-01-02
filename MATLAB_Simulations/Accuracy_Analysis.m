clear;
number_of_iterations = 1000;

N = 4;
D = 3;
distance_accuracy = 0.1;
minimal_axis_offset = 0.5;
max_distance = 5.0;

accuracies = zeros(number_of_iterations, 1);

for k=1:number_of_iterations
    accuracies(k) = Random_Accuracy_Simulation(N, D, distance_accuracy, max_distance, minimal_axis_offset);
    
end

worst_accuracy = max(accuracies);

edges = [0, 0:distance_accuracy:20*distance_accuracy, max(worst_accuracy, 20*distance_accuracy)];
h = histogram(accuracies, edges);
xlim([-distance_accuracy, max(min(20, worst_accuracy), 1.0)]);

title("Histogram uzyskanych dokładności pomiaru pozycji");
subtitle(sprintf("Dokładność pomiaru odległości: %0.2fm\n Najgorsza dokładność: %0.2fm\n Średnia dokładność: %0.2fm", ...
    distance_accuracy, worst_accuracy , sum(accuracies)/number_of_iterations));

info_str = sprintf("Liczba latarni: %d\n Wymiary: %d\n Liczba eksperymentów: %d", N, D, number_of_iterations);

xl = xlim;
yl = ylim;
text(0.98*xl(2), 0.98*yl(2), info_str, ...
    'HorizontalAlignment', 'right', ...
    'VerticalAlignment', 'top');

xlabel("Dokładność");
ylabel("Liczba wystąpień");