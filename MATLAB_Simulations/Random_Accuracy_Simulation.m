function accuracy = Random_Accuracy_Simulation(N, D, distance_accuracy, max_distance, minimal_axis_offset)

    P_star = rand(1, D)*max_distance - max_distance/2;
    P_vec = zeros(N, D);
    
    for i=1:D
        P_vec(i+1, 1:i) = rand(1, i)*max_distance - max_distance/2;
        if (P_vec(i+1, i))^2 < minimal_axis_offset
            P_vec(i+1, i) = sign(P_vec(i+1, i)) * minimal_axis_offset;
        end
    end
    
    if N > 4
        P_vec(5:N, :) = rand(N-4, 3)*max_distance - max_distance/2;
    end
    
    Noise_vec = -distance_accuracy/2 + rand(N, 1)*distance_accuracy;
    R_vec = sqrt(sum( (ones(N,1) * P_star - P_vec).^2, 2)) + Noise_vec;
    
    P = Solver(P_vec, R_vec);
    
    accuracy = norm(P - P_star);
end